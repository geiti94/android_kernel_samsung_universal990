/* drivers/video/exynos/decon/panels/common_mipi_lcd.c
 *
 * Samsung SoC MIPI LCD driver.
 *
 * Copyright (c) 2017 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/mutex.h>
#include <video/mipi_display.h>
#include <linux/platform_device.h>

#include "../disp_err.h"
#include "../decon.h"
#include "../dsim.h"
#include "../../panel/panel.h"
#include "../../panel/panel_drv.h"
#include "exynos_panel_drv.h"
#include "exynos_panel.h"

static DEFINE_MUTEX(cmd_lock);
struct panel_state *panel_state;
struct panel_mres *mres;

static int panel_drv_ioctl(struct exynos_panel_device *panel, u32 cmd, void *arg)
{
	int ret;

	if (unlikely(!panel || !panel->panel_drv_sd))
		return -EINVAL;

	ret = v4l2_subdev_call(panel->panel_drv_sd, core, ioctl, cmd, arg);

	return ret;
}

static int panel_drv_notify(struct v4l2_subdev *sd,
		unsigned int notification, void *arg)
{
	struct v4l2_event *ev = (struct v4l2_event *)arg;
	int ret;

	if (notification != V4L2_DEVICE_NOTIFY_EVENT) {
		decon_dbg("%s unknown event\n", __func__);
		return -EINVAL;
	}

	switch (ev->type) {
	case V4L2_EVENT_DECON_FRAME_DONE:
		ret = v4l2_subdev_call(sd, core, ioctl,
				PANEL_IOC_EVT_FRAME_DONE, &ev->timestamp);
		if (ret) {
			pr_err("%s failed to notify FRAME_DONE\n", __func__);
			return ret;
		}
		break;
	case V4L2_EVENT_DECON_VSYNC:
		ret = v4l2_subdev_call(sd, core, ioctl,
				PANEL_IOC_EVT_VSYNC, &ev->timestamp);
		if (ret) {
			pr_err("%s failed to notify VSYNC\n", __func__);
			return ret;
		}
		break;
	default:
		pr_warn("%s unknown event type %d\n", __func__, ev->type);
		break;
	}

	pr_debug("%s event type %d timestamp %ld %ld nsec\n",
			__func__, ev->type, ev->timestamp.tv_sec,
			ev->timestamp.tv_nsec);

	return 0;
}

static int common_panel_set_error_cb(struct exynos_panel_device *panel, void *arg)
{
	int ret;

	v4l2_set_subdev_hostdata(panel->panel_drv_sd, arg);
	ret = panel_drv_ioctl(panel, PANEL_IOC_REG_RESET_CB, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to set panel error callback\n", __func__);
		return ret;
	}

	return 0;
}

static int panel_drv_probe(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_DSIM_PROBE, (void *)&panel->id);
	if (ret) {
		pr_err("ERR:%s:failed to panel dsim probe\n", __func__);
		return ret;
	}

	return ret;
}

static int panel_drv_get_state(struct exynos_panel_device *panel)
{
	int ret = 0;

	ret = panel_drv_ioctl(panel, PANEL_IOC_GET_PANEL_STATE, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to get panel state", __func__);
		return ret;
	}

	panel_state = (struct panel_state *)
		v4l2_get_subdev_hostdata(panel->panel_drv_sd);
	if (IS_ERR_OR_NULL(panel_state)) {
		pr_err("ERR:%s:failed to get lcd information\n", __func__);
		return -EINVAL;
	}

	return ret;
}

static int panel_drv_get_mres(struct exynos_panel_device *panel)
{
	int ret = 0;

	ret = panel_drv_ioctl(panel, PANEL_IOC_GET_MRES, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to get panel mres", __func__);
		return ret;
	}

	mres = (struct panel_mres *)
		v4l2_get_subdev_hostdata(panel->panel_drv_sd);
	if (IS_ERR_OR_NULL(mres)) {
		pr_err("ERR:%s:failed to get lcd information\n", __func__);
		return -EINVAL;
	}

	return ret;
}

static int common_panel_vrr_changed(struct exynos_panel_device *panel, void *arg)
{
	struct exynos_panel_info *info;
	struct vrr_config_data *vrr_info = arg;
#if defined(CONFIG_DECON_BTS_VRR_ASYNC)
	struct decon_device *decon = get_decon_drvdata(0);
#endif

	if (!panel || !arg)
		return -EINVAL;

	info = &panel->lcd_info;
	vrr_info = arg;

	/*
	 * decon->lcd_info->fps : panel's current fps setting
	 * decon->lcd_info->req_vrr_fps : decon requested fps
	 * decon->bts.next_fps : next_fps will be applied after 1-VSYNC and FrameStart
	 * decon->bts.next_fps_vsync_count : timeline of next_fps will be applied.
	 */
	info->fps = vrr_info->fps;
	info->vrr_mode = vrr_info->mode;

#if defined(CONFIG_DECON_BTS_VRR_ASYNC)
	if (decon && info->req_vrr_fps == vrr_info->fps &&
			vrr_info->fps < decon->bts.next_fps) {
		DPU_DEBUG_BTS("\tupdate next_fps(%d->%d) next_fps_vsync_count(%llu)\n",
				decon->bts.next_fps, info->fps, decon->bts.next_fps_vsync_count);
		decon->bts.next_fps = info->fps;
		decon->bts.next_fps_vsync_count = decon->vsync.count + 1;
	}
#endif

	pr_info("%s vrr(fps:%d mode:%d) req_vrr(fps:%d mode:%d)\n",
			__func__, info->fps, info->vrr_mode,
			info->req_vrr_fps, info->req_vrr_mode);

	return 0;
}

static int panel_drv_set_vrr_cb(struct exynos_panel_device *panel)
{
	int ret;
	struct disp_cb_info vrr_cb_info = {
		.cb = (disp_cb *)common_panel_vrr_changed,
		.data = panel,
	};

	v4l2_set_subdev_hostdata(panel->panel_drv_sd, &vrr_cb_info);
	ret = panel_drv_ioctl(panel, PANEL_IOC_REG_VRR_CB, NULL);
	if (ret < 0) {
		pr_err("ERR:%s:failed to set panel error callback\n", __func__);
		return ret;
	}

	return 0;
}

#define DSIM_TX_FLOW_CONTROL
//#define DEBUG_DSI_CMD
#ifdef DEBUG_DSI_CMD
static void print_cmd(u8 cmd_id, const u8 *cmd, int size)
{
	char data[128];
	int i, len = 0;

	len = snprintf(data, ARRAY_SIZE(data) - len,
			"(%02X) ", cmd_id);
	for (i = 0; i < min((int)size, 32); i++)
		len += snprintf(data + len, ARRAY_SIZE(data) - len,
				"%02X ", cmd[i]);
	pr_info("%s\n", data);
}

static void print_dsim_cmd(const struct exynos_dsim_cmd *cmd_set, int size)
{
	int i;

	for (i = 0; i < size; i++)
		print_cmd(cmd_set[i].type,
				cmd_set[i].data_buf,
				cmd_set[i].data_len);
}
#endif

static int mipi_write(u32 id, u8 cmd_id, const u8 *cmd, u8 offset, int size, u32 option)
{
	int ret, retry = 3;
	unsigned long d0;
	u32 type, d1;
	bool block = (option & DSIM_OPTION_WAIT_TX_DONE);
	struct dsim_device *dsim = get_dsim_drvdata(id);

	if (!cmd) {
		pr_err("%s cmd is null\n", __func__);
		return -EINVAL;
	}

	if (cmd_id == MIPI_DSI_WR_DSC_CMD) {
		type = MIPI_DSI_DSC_PRA;
		d0 = (unsigned long)cmd[0];
		d1 = 0;
	} else if (cmd_id == MIPI_DSI_WR_PPS_CMD) {
		type = MIPI_DSI_DSC_PPS;
		d0 = (unsigned long)cmd;
		d1 = size;
	} else if (cmd_id == MIPI_DSI_WR_GEN_CMD) {
		if (size == 1) {
			type = MIPI_DSI_DCS_SHORT_WRITE;
			d0 = (unsigned long)cmd[0];
			d1 = 0;
		} else {
			type = MIPI_DSI_DCS_LONG_WRITE;
			d0 = (unsigned long)cmd;
			d1 = size;
		}
	} else {
		pr_info("%s invalid cmd_id %d\n", __func__, cmd_id);
		return -EINVAL;
	}

	mutex_lock(&cmd_lock);
	while (--retry >= 0) {
		if (offset > 0) {
			if (option & DSIM_OPTION_POINT_GPARA) {
				u8 gpara[3] = { 0xB0, offset, cmd[0] };
#ifdef DEBUG_DSI_CMD
				print_cmd(MIPI_DSI_DCS_LONG_WRITE, gpara, ARRAY_SIZE(gpara));
#endif
				if (dsim_write_data(dsim, MIPI_DSI_DCS_LONG_WRITE,
							(unsigned long)gpara, ARRAY_SIZE(gpara), false)) {
					pr_err("%s failed to write gpara %d (retry %d)\n",
							__func__, offset, retry);
					continue;
				}
			} else {
#ifdef DEBUG_DSI_CMD
				u8 gpara[2] = { 0xB0, offset };
				print_cmd(MIPI_DSI_DCS_SHORT_WRITE_PARAM, gpara, ARRAY_SIZE(gpara));
#endif
				if (dsim_write_data(dsim,
							MIPI_DSI_DCS_SHORT_WRITE_PARAM, 0xB0, offset, false)) {
					pr_err("%s failed to write gpara %d (retry %d)\n",
							__func__, offset, retry);
					continue;
				}
			}
		}
#ifdef DEBUG_DSI_CMD
		print_cmd(type, cmd, size);
#endif
		if (dsim_write_data(dsim, type, d0, d1, block)) {
			pr_err("%s failed to write cmd %02X size %d(retry %d)\n",
					__func__, cmd[0], size, retry);
			continue;
		}

		break;
	}

	if (retry < 0) {
		pr_err("%s failed: exceed retry count (cmd %02X)\n",
				__func__, cmd[0]);
		ret = -EIO;
		goto error;
	}

	pr_debug("%s cmd_id %d, addr %02X offset %d size %d\n",
			__func__, cmd_id, cmd[0], offset, size);
	ret = size;

error:
	mutex_unlock(&cmd_lock);
	return ret;
}

#define MAX_DSIM_PH_SIZE (32)
#define MAX_DSIM_PL_SIZE (DSIM_PL_FIFO_THRESHOLD)
#define MAX_CMD_SET_SIZE (1024)
static struct exynos_dsim_cmd cmd_set[MAX_CMD_SET_SIZE];
static int mipi_write_table(u32 id, const struct cmd_set *cmd, int size, u32 option)
{
	int ret, total_size = 0;
	struct dsim_device *dsim = get_dsim_drvdata(id);
	int i, from = 0, sz_pl = 0;
	s64 elapsed_usec;
	struct timespec cur_ts, last_ts, delta_ts;

	if (!cmd) {
		pr_err("%s cmd is null\n", __func__);
		return -EINVAL;
	}

	if (size <= 0) {
		pr_err("%s invalid cmd size %d\n", __func__, size);
		return -EINVAL;
	}

	if (size > MAX_CMD_SET_SIZE) {
		pr_err("%s exceeded MAX_CMD_SET_SIZE(%d) %d\n",
				__func__, MAX_CMD_SET_SIZE, size);
		return -EINVAL;
	}

	ktime_get_ts(&last_ts);
	mutex_lock(&cmd_lock);
	for (i = 0; i < size; i++) {
		if (cmd[i].buf == NULL) {
			pr_err("%s cmd[%d].buf is null\n", __func__, i);
			continue;
		}

		if (cmd[i].cmd_id == MIPI_DSI_WR_DSC_CMD) {
			cmd_set[i].type = MIPI_DSI_DSC_PRA;
			cmd_set[i].data_buf = cmd[i].buf;
			cmd_set[i].data_len = 1;
		} else if (cmd[i].cmd_id == MIPI_DSI_WR_PPS_CMD) {
			cmd_set[i].type = MIPI_DSI_DSC_PPS;
			cmd_set[i].data_buf = cmd[i].buf;
			cmd_set[i].data_len = cmd[i].size;
		} else if (cmd[i].cmd_id == MIPI_DSI_WR_GEN_CMD) {
			if (cmd[i].size == 1) {
				cmd_set[i].type = MIPI_DSI_DCS_SHORT_WRITE;
				cmd_set[i].data_buf = cmd[i].buf;
				cmd_set[i].data_len = 1;
			} else {
				cmd_set[i].type = MIPI_DSI_DCS_LONG_WRITE;
				cmd_set[i].data_buf = cmd[i].buf;
				cmd_set[i].data_len = cmd[i].size;
			}
		} else {
			pr_info("%s invalid cmd_id %d\n",
					__func__, cmd[i].cmd_id);
			ret = -EINVAL;
			goto error;
		}

#if defined(DSIM_TX_FLOW_CONTROL)
		if ((i - from >= MAX_DSIM_PH_SIZE) ||
			(sz_pl + ALIGN(cmd_set[i].data_len, 4) >= MAX_DSIM_PL_SIZE)) {
			if (dsim_write_cmd_set(dsim, &cmd_set[from], i - from, false)) {
				pr_err("%s failed to write cmd_set\n", __func__);
				ret = -EIO;
				goto error;
			}
			pr_debug("%s cmd_set:%d pl:%d\n", __func__, i - from, sz_pl);
#ifdef DEBUG_DSI_CMD
			print_dsim_cmd(&cmd_set[from], i - from);
#endif
			from = i;
			sz_pl = 0;
		}
#endif
		sz_pl += ALIGN(cmd_set[i].data_len, 4);
		total_size += cmd_set[i].data_len;
	}

	if (dsim_write_cmd_set(dsim, &cmd_set[from], i - from, false)) {
		pr_err("%s failed to write cmd_set\n", __func__);
		ret = -EIO;
		goto error;
	}

	ktime_get_ts(&cur_ts);
	delta_ts = timespec_sub(cur_ts, last_ts);
	elapsed_usec = timespec_to_ns(&delta_ts) / 1000;
	pr_debug("%s done (cmd_set:%d size:%d elapsed %2lld.%03lld msec)\n",
			__func__, size, total_size,
			elapsed_usec / 1000, elapsed_usec % 1000);
#ifdef DEBUG_DSI_CMD
	print_dsim_cmd(&cmd_set[from], i - from);
#endif

	ret = total_size;

error:
	mutex_unlock(&cmd_lock);

	return ret;
}

static int mipi_sr_write(u32 id, u8 cmd_id, const u8 *cmd, u8 offset, int size, u32 option)
{
	int ret = 0;
	struct dsim_device *dsim = get_dsim_drvdata(id);
	s64 elapsed_usec;
	struct timespec cur_ts, last_ts, delta_ts;

	ktime_get_ts(&last_ts);

	mutex_lock(&cmd_lock);
	ret = dsim_sr_write_data(dsim, cmd, size);
	mutex_unlock(&cmd_lock);

	ktime_get_ts(&cur_ts);
	delta_ts = timespec_sub(cur_ts, last_ts);
	elapsed_usec = timespec_to_ns(&delta_ts) / 1000;
	pr_debug("%s done (size:%d elapsed %2lld.%03lld msec)\n",
			__func__, size, elapsed_usec / 1000, elapsed_usec % 1000);

	return ret;
}

static int mipi_read(u32 id, u8 addr, u8 offset, u8 *buf, int size, u32 option)
{
	int ret, retry = 3;
	struct dsim_device *dsim = get_dsim_drvdata(id);

	if (!buf) {
		pr_err("%s buf is null\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&cmd_lock);
	while (--retry >= 0) {
		if (offset > 0) {
			if (option & DSIM_OPTION_POINT_GPARA) {
				u8 gpara[3] = { 0xB0, offset, addr };
				if (dsim_write_data(dsim, MIPI_DSI_DCS_LONG_WRITE,
							(unsigned long)gpara, ARRAY_SIZE(gpara), false)) {
					pr_err("%s failed to write gpara %d (retry %d)\n",
							__func__, offset, retry);
					continue;
				}
			} else {
				if (dsim_write_data(dsim,
							MIPI_DSI_DCS_SHORT_WRITE_PARAM, 0xB0, offset, false)) {
					pr_err("%s failed to write gpara %d (retry %d)\n",
							__func__, offset, retry);
					continue;
				}
			}
		}

		ret = dsim_read_data(dsim, MIPI_DSI_DCS_READ,
				(u32)addr, size, buf);
		if (ret != size) {
			pr_err("%s, failed to read addr %02X ofs %d size %d (ret %d, retry %d)\n",
					__func__, addr, offset, size, ret, retry);
			continue;
		}
		break;
	}

	if (retry < 0) {
		pr_err("%s failed: exceed retry count (addr %02X)\n",
				__func__, addr);
		ret = -EIO;
		goto error;
	}

	pr_debug("%s addr %02X ofs %d size %d, buf %02X done\n",
			__func__, addr, offset, size, buf[0]);

	ret = size;

error:
	mutex_unlock(&cmd_lock);
	return ret;
}

enum dsim_state get_dsim_state(u32 id)
{
	struct dsim_device *dsim = get_dsim_drvdata(id);

	if (dsim == NULL) {
		pr_err("ERR:%s:dsim is NULL\n", __func__);
		return -ENODEV;
	}
	return dsim->state;
}

static struct exynos_panel_info *get_lcd_info(u32 id)
{
	return &get_panel_drvdata(id)->lcd_info;
}

static int wait_for_vsync(u32 id, u32 timeout)
{
	struct decon_device *decon = get_decon_drvdata(0);
	int ret;

	if (!decon)
		return -EINVAL;

	decon_hiber_block_exit(decon);
	ret = decon_wait_for_vsync(decon, timeout);
	decon_hiber_unblock(decon);

	return ret;
}

static int panel_drv_put_ops(struct exynos_panel_device *panel)
{
	int ret = 0;
	struct mipi_drv_ops mipi_ops;

	mipi_ops.read = mipi_read;
	mipi_ops.write = mipi_write;
	mipi_ops.write_table = mipi_write_table;
	mipi_ops.sr_write = mipi_sr_write;
	mipi_ops.get_state = get_dsim_state;
	mipi_ops.parse_dt = parse_lcd_info;
	mipi_ops.get_lcd_info = get_lcd_info;
	mipi_ops.wait_for_vsync = wait_for_vsync;

	v4l2_set_subdev_hostdata(panel->panel_drv_sd, &mipi_ops);

	ret = panel_drv_ioctl(panel, PANEL_IOC_DSIM_PUT_MIPI_OPS, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to set mipi ops\n", __func__);
		return ret;
	}

	return ret;
}

static int panel_drv_init(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_put_ops(panel);
	if (ret) {
		pr_err("ERR:%s:failed to put ops\n", __func__);
		goto do_exit;
	}

	ret = panel_drv_probe(panel);
	if (ret) {
		pr_err("ERR:%s:failed to probe panel", __func__);
		goto do_exit;
	}

	ret = panel_drv_get_state(panel);
	if (ret) {
		pr_err("ERR:%s:failed to get panel state\n", __func__);
		goto do_exit;
	}

	ret = panel_drv_get_mres(panel);
	if (ret) {
		pr_err("ERR:%s:failed to get panel mres\n", __func__);
		goto do_exit;
	}

	ret = panel_drv_set_vrr_cb(panel);
	if (ret) {
		pr_err("ERR:%s:failed to set vrr callback\n", __func__);
		goto do_exit;
	}

	return ret;

do_exit:
	return ret;
}

static int common_panel_connected(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_get_state(panel);
	if (ret) {
		pr_err("ERR:%s:failed to get panel state\n", __func__);
		return ret;
	}

	ret = !(panel_state->connect_panel == PANEL_DISCONNECT);
	pr_info("%s panel %s\n", __func__,
			ret ? "connected" : "disconnected");

	return ret;
}

static int common_panel_init(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_init(panel);
	if (ret) {
		pr_err("ERR:%s:failed to init common panel\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_probe(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_PANEL_PROBE, &panel->id);
	if (ret) {
		pr_err("ERR:%s:failed to probe panel\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_displayon(struct exynos_panel_device *panel)
{
	int ret;
	int disp_on = 1;

	ret = panel_drv_ioctl(panel, PANEL_IOC_DISP_ON, (void *)&disp_on);
	if (ret) {
		pr_err("ERR:%s:failed to display on\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_suspend(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_SLEEP_IN, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to sleep in\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_resume(struct exynos_panel_device *panel)
{
	return 0;
}

static int common_panel_dump(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_PANEL_DUMP, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to dump panel\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_setarea(struct exynos_panel_device *panel, u32 l, u32 r, u32 t, u32 b)
{
	int ret = 0;
	char column[5];
	char page[5];
	int retry;
	struct dsim_device *dsim = get_dsim_drvdata(panel->id);

	column[0] = MIPI_DCS_SET_COLUMN_ADDRESS;
	column[1] = (l >> 8) & 0xff;
	column[2] = l & 0xff;
	column[3] = (r >> 8) & 0xff;
	column[4] = r & 0xff;

	page[0] = MIPI_DCS_SET_PAGE_ADDRESS;
	page[1] = (t >> 8) & 0xff;
	page[2] = t & 0xff;
	page[3] = (b >> 8) & 0xff;
	page[4] = b & 0xff;

	mutex_lock(&cmd_lock);
	retry = 2;

	while (dsim_write_data(dsim, MIPI_DSI_DCS_LONG_WRITE,
				(unsigned long)column, ARRAY_SIZE(column), false) != 0) {
		pr_err("failed to write COLUMN_ADDRESS\n");
		if (--retry <= 0) {
			pr_err("COLUMN_ADDRESS is failed: exceed retry count\n");
			ret = -EINVAL;
			goto error;
		}
	}

	retry = 2;
	while (dsim_write_data(dsim, MIPI_DSI_DCS_LONG_WRITE,
				(unsigned long)page, ARRAY_SIZE(page), true) != 0) {
		pr_err("failed to write PAGE_ADDRESS\n");
		if (--retry <= 0) {
			pr_err("PAGE_ADDRESS is failed: exceed retry count\n");
			ret = -EINVAL;
			goto error;
		}
	}

	pr_debug("RECT [l:%d r:%d t:%d b:%d w:%d h:%d]\n",
			l, r, t, b, r - l + 1, b - t + 1);

error:
	mutex_unlock(&cmd_lock);
	return ret;
}

static int common_panel_power(struct exynos_panel_device *panel, int on)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_SET_POWER, (void *)&on);
	if (ret) {
		pr_err("ERR:%s:failed to panel %s\n",
				__func__, on ? "on" : "off");
		return ret;
	}
	pr_debug("%s power %s\n", __func__, on ? "on" : "off");

	return 0;
}

static int common_panel_poweron(struct exynos_panel_device *panel)
{
	return common_panel_power(panel, 1);
}

static int common_panel_poweroff(struct exynos_panel_device *panel)
{
	return common_panel_power(panel, 0);
}

static int common_panel_sleepin(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_SLEEP_IN, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to sleep in\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_sleepout(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_SLEEP_OUT, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to sleep out\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_notify(struct exynos_panel_device *panel, void *data)
{
	int ret;

	ret = panel_drv_notify(panel->panel_drv_sd,
			V4L2_DEVICE_NOTIFY_EVENT, data);
	if (ret) {
		pr_err("ERR:%s:failed to notify\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_read_state(struct exynos_panel_device *panel)
{
	return true;
}

#ifdef CONFIG_EXYNOS_DOZE
static int common_panel_doze(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_DOZE, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to sleep out\n", __func__);
		return ret;
	}

	return 0;
}

static int common_panel_doze_suspend(struct exynos_panel_device *panel)
{
	int ret;

	ret = panel_drv_ioctl(panel, PANEL_IOC_DOZE_SUSPEND, NULL);
	if (ret) {
		pr_err("ERR:%s:failed to sleep out\n", __func__);
		return ret;
	}

	return 0;
}
#endif

static int common_panel_mres(struct exynos_panel_device *panel, u32 mode_idx)
{
	struct exynos_panel_info *info;
	struct exynos_display_mode *mode;
	struct exynos_display_mode_info *mode_info;
	int i, ret;

	info = &panel->lcd_info;
	mode_info = &panel->lcd_info.display_mode[mode_idx];
	mode = &panel->lcd_info.display_mode[mode_idx].mode;

	if (mres->nr_resol == 0 || mres->resol == NULL) {
		pr_err("%s:panel doesn't support multi-resolution\n",
				__func__);
		return -EINVAL;
	}

	for (i = 0; i < mres->nr_resol; i++) {
		if ((mres->resol[i].w == mode->width) &&
			(mres->resol[i].h == mode->height))
			break;
	}

	if (i == mres->nr_resol) {
		pr_err("%s:unsupported resolution(%dx%d)\n",
				__func__, mode->width, mode->height);
		return -EINVAL;
	}

	ret = panel_drv_ioctl(panel, PANEL_IOC_SET_MRES, &i);
	if (ret) {
		pr_err("ERR:%s:failed to set multi-resolution\n", __func__);
		goto mres_exit;
	}

	info->cur_mode_idx = mode_idx;
	info->xres = mode->width;
	info->yres = mode->height;
	info->dsc.en = mode_info->dsc_en;
	info->dsc.slice_num = info->xres / mode_info->dsc_width;
	info->dsc.slice_h = mode_info->dsc_height;
	info->dsc.enc_sw = mode_info->dsc_enc_sw;
	info->dsc.dec_sw = mode_info->dsc_dec_sw;

	pr_info("%s update resolution resol(%dx%d) dsc(en:%d slice(%d):%dx%d)\n",
			__func__, info->xres, info->yres, info->dsc.en,
			info->dsc.slice_num,  info->dsc.dec_sw, info->dsc.slice_h);

mres_exit:
	return ret;
}

static int common_panel_fps(struct exynos_panel_device *panel, struct vrr_config_data *vrr_info)
{
	int ret, old_fps;
	struct exynos_panel_info *info = &panel->lcd_info;
#if defined(CONFIG_DECON_BTS_VRR_ASYNC)
	struct decon_device *decon = get_decon_drvdata(0);
#endif

	old_fps = info->fps;
	info->req_vrr_fps = vrr_info->fps;
	info->req_vrr_mode = vrr_info->mode;

#if defined(CONFIG_DECON_BTS_VRR_ASYNC)
	/*
	 * lcd_info's fps is used in bts calculation.
	 * To prevent underrun, update fps first
	 * if target fps is bigger than previous fps.
	 */
	if (decon && info->req_vrr_fps > decon->bts.next_fps) {
		DPU_DEBUG_BTS("\tupdate next_fps(%d->%d)\n",
				info->req_vrr_fps, decon->bts.next_fps);
		decon->bts.next_fps = info->req_vrr_fps;
		decon->bts.next_fps_vsync_count = 0;
	}
#endif
	panel_info("[VRR:INFO]:%s request vrr(fps:%d mode:%d)\n",
			__func__, info->req_vrr_fps, info->req_vrr_mode);
	ret = panel_drv_ioctl(panel, PANEL_IOC_SET_VRR_INFO, vrr_info);
	if (ret) {
		pr_err("ERR:%s:failed to set fps\n", __func__);
		return ret;
	}

	return 0;
}

struct exynos_panel_ops common_panel_ops = {
	.init		= common_panel_init,
	.probe		= common_panel_probe,
	.suspend	= common_panel_suspend,
	.resume		= common_panel_resume,
	.dump		= common_panel_dump,
	.connected	= common_panel_connected,
	.setarea	= common_panel_setarea,
	.poweron	= common_panel_poweron,
	.poweroff	= common_panel_poweroff,
	.sleepin	= common_panel_sleepin,
	.sleepout	= common_panel_sleepout,
	.displayon	= common_panel_displayon,
	.notify		= common_panel_notify,
	.read_state	= common_panel_read_state,
	.set_error_cb	= common_panel_set_error_cb,
#ifdef CONFIG_EXYNOS_DOZE
	.doze		= common_panel_doze,
	.doze_suspend	= common_panel_doze_suspend,
#endif
	.mres = common_panel_mres,
	.set_vrefresh = common_panel_fps,
};
