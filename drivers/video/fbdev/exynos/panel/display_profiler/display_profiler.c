/*
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>

#include "../panel_drv.h"
#include "display_profiler.h"

static int profiler_do_seqtbl_by_index_nolock(struct profiler_device *profiler, int index)
{
	int ret;
	struct seqinfo *tbl;
	struct panel_info *panel_data;
	struct panel_device *panel = to_panel_device(profiler);
	struct timespec cur_ts, last_ts, delta_ts;
	s64 elapsed_usec;

	if (panel == NULL) {
		panel_err("ERR:PANEL:%s:panel is null\n", __func__);
		return -EINVAL;
	}

	if (!IS_PANEL_ACTIVE(panel))
		return 0;

	panel_data = &panel->panel_data;
	tbl = panel->profiler.seqtbl;
	ktime_get_ts(&cur_ts);

#if 0
	ktime_get_ts(&last_ts);
#endif

	if (unlikely(index < 0 || index >= MAX_PROFILER_SEQ)) {
		panel_err("%s, invalid paramter (panel %p, index %d)\n",
				__func__, panel, index);
		ret = -EINVAL;
		goto do_exit;
	}

#if 0
	delta_ts = timespec_sub(last_ts, cur_ts);
	elapsed_usec = timespec_to_ns(&delta_ts) / 1000;
	if (elapsed_usec > 34000)
		pr_debug("seq:%s warn:elapsed %lld.%03lld msec to acquire lock\n",
				tbl[index].name, elapsed_usec / 1000, elapsed_usec % 1000);
#endif
	ret = panel_do_seqtbl(panel, &tbl[index]);
	if (unlikely(ret < 0)) {
		panel_err("%s, failed to excute seqtbl %s\n",
				__func__, tbl[index].name);
		ret = -EIO;
		goto do_exit;
	}

do_exit:
	ktime_get_ts(&last_ts);
	delta_ts = timespec_sub(last_ts, cur_ts);
	elapsed_usec = timespec_to_ns(&delta_ts) / 1000;
	pr_debug("seq:%s done (elapsed %2lld.%03lld msec)\n",
			tbl[index].name, elapsed_usec / 1000, elapsed_usec % 1000);

	return 0;
}

int profiler_do_seqtbl_by_index(struct profiler_device *profiler, int index)
{
	int ret = 0;
	struct panel_device *panel = to_panel_device(profiler);

	if (panel == NULL) {
		panel_err("ERR:PANEL:%s:panel is null\n", __func__);
		return -EINVAL;
	}

//	panel_dbg("%s : %d\n", __func__, index);

	mutex_lock(&panel->op_lock);
	ret = profiler_do_seqtbl_by_index_nolock(profiler, index);
	mutex_unlock(&panel->op_lock);

	return ret;
}


#define PROFILER_SYSTRACE_BUF_SIZE	40

extern int decon_systrace_enable;

void profiler_systrace_write(int pid, char id, char *str, int value)
{
	char buf[PROFILER_SYSTRACE_BUF_SIZE] = {0, };

	if (!decon_systrace_enable)
		return;

	 switch(id) {
		case 'B':
			snprintf(buf, PROFILER_SYSTRACE_BUF_SIZE, "B|%d|%s", pid, str);
			break;
		case 'E':
			strcpy(buf, "E");
			break;
		case 'C':
			snprintf(buf, PROFILER_SYSTRACE_BUF_SIZE,
				"C|%d|%s|%d", pid, str, 1);
			break;
		default:
			panel_err("PANEL:ERR:%s:wrong argument : %c\n", __func__, id);
			return;
	}
	panel_info("%s\n", buf);
	trace_printk(buf);

}

#if 0

static int update_profile_win(struct profiler_device *profiler, void *arg)
{
	int ret = 0;

	int width, height;
	struct panel_device *panel;
	int cmd_idx = PROFILE_DISABLE_WIN_SEQ;
	struct decon_rect *up_region = (struct decon_rect *)arg;

	panel = container_of(profiler, struct panel_device, profiler);

	memcpy((struct decon_rect *)&profiler->win_rect, up_region, sizeof(struct decon_rect));

	width = profiler->win_rect.right - profiler->win_rect.left;
	height = profiler->win_rect.bottom - profiler->win_rect.top;

	panel_info("PROFILE_WIN_UPDATE region : %d:%d, %d:%d\n",
			profiler->win_rect.left, profiler->win_rect.top,
			profiler->win_rect.right, profiler->win_rect.bottom);

	if ((width == panel->panel_data.props.xres - 1) &&
		(height == panel->panel_data.props.yres - 1)) {
		cmd_idx = PROFILE_DISABLE_WIN_SEQ;
		panel_info("PROFILE_WIN_UPDATE full region : disable\n");
	} else {
		cmd_idx = PROFILE_WIN_UPDATE_SEQ;
	}

	ret = profiler_do_seqtbl_by_index(profiler, cmd_idx);

	return ret;
}
#endif

static int update_profile_hiber(struct profiler_device *profiler, bool enter_exit, s64 time_us)
{
	int ret = 0;
	struct profiler_hiber *hiber_info;

	hiber_info = &profiler->hiber_info;

	if (hiber_info->hiber_status == enter_exit) {
		panel_err("[DISP_PROFILER] %s:status already %s\n", __func__, enter_exit ? "ENTER" : "EXIT");
		return ret;
	}

	if (enter_exit) {
		hiber_info->hiber_enter_cnt++;
		hiber_info->hiber_enter_time = time_us;
	}
	else {
		hiber_info->hiber_exit_cnt++;
		hiber_info->hiber_exit_time = time_us;
	}

	profiler_info(profiler, hiber_debug, "[DISP_PROFILER] %s: status %s -> %s\n", __func__,
		hiber_info->hiber_status ? "ENTER" : "EXIT",
		enter_exit ? "ENTER" : "EXIT");

	hiber_info->hiber_status = enter_exit;

	return ret;
}

static int update_profile_te(struct profiler_device *profiler, s64 time_us)
{
	int ret = 0;
	struct profiler_te *te_info;
	te_info = &profiler->te_info;
	
	spin_lock(&te_info->slock);
	if (time_us == 0) {
		te_info->last_time = 0;
		spin_unlock(&te_info->slock);
		profiler_info(profiler, te_debug, "[DISP_PROFILER] %s:reset\n", __func__);
		return ret;
	}	
	if (te_info->last_time == time_us) {
		spin_unlock(&te_info->slock);
		profiler_info(profiler, te_debug, "[DISP_PROFILER] %s:skipped\n", __func__);
		return ret;
	}

	if (te_info->last_time == 0) {
		te_info->last_time = time_us;
		spin_unlock(&te_info->slock);
		profiler_info(profiler, te_debug, "[DISP_PROFILER] %s:last time: %lld\n", __func__, te_info->last_time);
		return ret;
	}
	
	te_info->last_diff = time_us - te_info->last_time;
	te_info->last_time = time_us;
	spin_unlock(&te_info->slock);

	profiler_info(profiler, te_debug, "[DISP_PROFILER] %s:last time: %lld, diff: %lld\n", __func__, te_info->last_time, te_info->last_diff);
	te_info->times[te_info->idx++] = te_info->last_diff;
	te_info->idx = te_info->idx % MAX_TE_CNT;

	return ret;
}

static int update_profile_win_config(struct profiler_device *profiler)
{
	int ret = 0;

	s64 diff;
	ktime_t timestamp;

	timestamp = ktime_get();

	if (profiler->fps.frame_cnt < FPS_MAX)
		profiler->fps.frame_cnt++;
	else
		profiler->fps.frame_cnt = 0;

	if (ktime_to_us(profiler->fps.win_config_time) != 0) {
		diff = ktime_to_us(ktime_sub(timestamp, profiler->fps.win_config_time));
		profiler->fps.instant_fps = (int)(1000000 / diff);

		if (profiler->fps.instant_fps >= 59)
			profiler->fps.color = FPS_COLOR_RED;
		else
			profiler->fps.color = FPS_COLOR_GREEN;

		if (profiler->conf->systrace)
			decon_systrace(get_decon_drvdata(0), 'C', "fps_inst", (int)profiler->fps.instant_fps);

//		ret = profiler_do_seqtbl_by_index(profiler, PROFILE_SET_COLOR_SEQ);
	}
	profiler->fps.win_config_time = timestamp;

	return ret;
}

struct win_config_backup {
	int state;
	struct decon_frame src;
	struct decon_frame dst;
};


#if 0

static int update_profiler_circle(struct profiler_device *profiler, unsigned int color)
{
	int ret = 0;

	if (profiler->circle_color != color) {
		profiler->circle_color = color;
		ret = profiler_do_seqtbl_by_index(profiler, PROFILER_SET_CIRCLR_SEQ);
	}

	return ret;
}
#endif

static long profiler_v4l2_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	int ret = 0;
//	unsigned int color;
	struct panel_device *panel;
	struct profiler_device *profiler = container_of(sd, struct profiler_device, sd);
	
	if (profiler->conf == NULL) {
		return (long)ret;
	}

	panel = container_of(profiler, struct panel_device, profiler);

	switch(cmd) {
		case PROFILE_REG_DECON:
			panel_info("PROFILE_REG_DECON was called\n");
			break;

		case PROFILE_WIN_UPDATE:
#if 0
			if (profiler->win_rect.disp_en)
				ret = update_profile_win(profiler, arg);
#endif
			break;

		case PROFILE_WIN_CONFIG:
			if (prof_en(profiler, fps))
				ret = update_profile_win_config(profiler);
			break;
		case PROFILE_TE:
			if (prof_en(profiler, te))
				update_profile_te(profiler, (s64)arg);
			break;
		case PROFILE_HIBER_ENTER:
			if (prof_en(profiler, te))
				update_profile_te(profiler, 0);
			if (prof_en(profiler, hiber))
				update_profile_hiber(profiler, true, (s64)arg);
			break;
		case PROFILE_HIBER_EXIT:
			if (prof_en(profiler, te))
				update_profile_te(profiler, 0);
			if (prof_en(profiler, hiber))
				update_profile_hiber(profiler, false, (s64)arg);
			break;
		case PROFILER_SET_PID:
			profiler->systrace.pid = *(int *)arg;
			break;

		case PROFILER_COLOR_CIRCLE:
#if 0
			color = *(int *)arg;
			ret = update_profiler_circle(profiler, color);
#endif
			break;
	}

	return (long)ret;
}

static const struct v4l2_subdev_core_ops profiler_v4l2_core_ops = {
	.ioctl = profiler_v4l2_ioctl,
};

static const struct v4l2_subdev_ops profiler_subdev_ops = {
	.core = &profiler_v4l2_core_ops,
};

static void profiler_init_v4l2_subdev(struct panel_device *panel)
{
	struct v4l2_subdev *sd;
	struct profiler_device *profiler = &panel->profiler;

	sd = &profiler->sd;

	v4l2_subdev_init(sd, &profiler_subdev_ops);
	sd->owner = THIS_MODULE;
	sd->grp_id = 0;

	snprintf(sd->name, sizeof(sd->name), "%s.%d", "panel-profiler", 0);

	v4l2_set_subdevdata(sd, profiler);
}


void profile_fps(struct profiler_device *profiler)
{
	s64 time_diff;
	unsigned int gap, c_frame_cnt;
	ktime_t c_time, p_time;
	struct profiler_fps *fps;
 
	fps = &profiler->fps;

	c_frame_cnt = fps->frame_cnt;
	c_time = ktime_get();

	if (c_frame_cnt >= fps->prev_frame_cnt)
		gap = c_frame_cnt - fps->prev_frame_cnt;
	else
		gap = (FPS_MAX - fps->prev_frame_cnt) + c_frame_cnt;

	p_time = fps->slot[fps->slot_cnt].timestamp;
	fps->slot[fps->slot_cnt].timestamp = c_time;

	fps->total_frame -= fps->slot[fps->slot_cnt].frame_cnt;
	fps->total_frame += gap;
	fps->slot[fps->slot_cnt].frame_cnt = gap;

	time_diff = ktime_to_us(ktime_sub(c_time, p_time));
	//panel_info("%s : diff : %llu : slot_cnt %d\n", __func__, time_diff, fps->slot_cnt);
 
	/*To Do.. after lcd off->on, must clear fps->slot data to zero and comp_fps, instan_fps set to 60Hz (default)*/
	if (ktime_to_us(p_time) != 0) {
		time_diff = ktime_to_us(ktime_sub(c_time, p_time));

		fps->average_fps = fps->total_frame;
		fps->comp_fps = (unsigned int)(((1000000000 / time_diff) * fps->total_frame) + 500) / 1000;

		profiler_info(profiler, fps_debug, "[DISP_PROFILER] avg fps : %d\n", fps->comp_fps);

		time_diff = ktime_to_us(ktime_sub(c_time, profiler->fps.win_config_time));
		if (time_diff >= 100000) {
			fps->instant_fps = fps->average_fps;
			if (profiler->conf->systrace)
				decon_systrace(get_decon_drvdata(0), 'C', "fps_inst", (int)fps->instant_fps);
		}
		if (profiler->conf->systrace)
			decon_systrace(get_decon_drvdata(0), 'C', "fps_aver", (int)fps->comp_fps);
	}

	fps->prev_frame_cnt = c_frame_cnt;
	fps->slot_cnt = (fps->slot_cnt + 1) % MAX_SLOT_CNT;
}

static int profiler_mprint_update(struct profiler_device *profiler)
{
	int ret = 0;
	struct panel_device *panel = to_panel_device(profiler);
	struct timespec cur_ts, last_ts, delta_ts;
	s64 elapsed_usec = 0;

	struct pktinfo PKTINFO(self_mprint_data) = {
        .name = "self_mprint_data",
        .type = DSI_PKT_TYPE_WR_SR,
        .data = profiler->mask_props.data,
        .offset = 0,
        .dlen = profiler->mask_props.data_size,
        .pktui = NULL,
        .nr_pktui = 0,
        .option = 0,
    };

    void *self_mprint_data_cmdtbl[] = {
        &PKTINFO(self_mprint_data),
    };
	
	struct seqinfo self_mprint_data_seq = SEQINFO_INIT("self_mprint_data_seq", self_mprint_data_cmdtbl);

	if (!IS_PANEL_ACTIVE(panel))
		return -EIO;

	panel_wake_lock(panel);
	ret = profiler_do_seqtbl_by_index(profiler, DISABLE_PROFILE_FPS_MASK_SEQ);
/*
	if (profiler->mask_config->debug)
		profiler_info(profiler, mprint_debug, "[DISP_PROFILER] disable fps mask ret %d\n", ret);
*/

	ret = profiler_do_seqtbl_by_index_nolock(profiler, WAIT_PROFILE_FPS_MASK_SEQ);
/*
	if (profiler->mask_config->debug)
		profiler_info(profiler, mprint_debug, "[DISP_PROFILER] wait fps mask ret %d\n", ret);
*/
	mutex_lock(&panel->op_lock);
	ret = profiler_do_seqtbl_by_index_nolock(profiler, MEM_SELECT_PROFILE_FPS_MASK_SEQ);

	//send mask data
	ktime_get_ts(&cur_ts);
	ret = panel_do_seqtbl(panel, &self_mprint_data_seq);
	if (unlikely(ret < 0)) {
		pr_err("[DISP_PROFILER] %s, failed to excute self_mprint_data_cmdtbl(%d)\n", __func__, profiler->mask_props.data_size);
		ret = -EIO;
		goto do_exit;
	}

//	if (profiler->mask_config->debug) {
	if (prof_en(profiler, timediff)) {
		ktime_get_ts(&last_ts);
		delta_ts = timespec_sub(last_ts, cur_ts);
		elapsed_usec = timespec_to_ns(&delta_ts) / 1000;
	}
	profiler_info(profiler, timediff_en, "[DISP_PROFILER] write mask image, elapsed = %lldus\n", elapsed_usec);
	profiler_info(profiler, mprint_debug, "[DISP_PROFILER] write mask image, size = %d\n", profiler->mask_props.data_size);
	
	ret = profiler_do_seqtbl_by_index_nolock(profiler, ENABLE_PROFILE_FPS_MASK_SEQ);
do_exit: 
	mutex_unlock(&panel->op_lock);
	panel_wake_unlock(panel);

//	if (profiler->mask_config->debug)
	if (prof_dbg(profiler, mprint))
		profiler_info(profiler, mprint_debug, "[DISP_PROFILER] enable fps mask ret %d\n", ret);

	return ret;
}

#define PROFILER_TEXT_OUTPUT_LEN 32
static int profiler_thread(void *data)
{
	int ret;
	struct profiler_device *profiler = data;
	//struct profiler_fps *fps = &profiler->fps;
	struct mprint_props *mask_props;
	struct profiler_te *te;
	struct profiler_hiber *hiber;
	char text_old[PROFILER_TEXT_OUTPUT_LEN] = {0, };
	char text[PROFILER_TEXT_OUTPUT_LEN] = {0, };
	int len = 0;
	int cycle_time = 0;
	struct timespec cur_ts, last_ts, delta_ts;
	s64 elapsed_usec;

	if (profiler->conf == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler config is null\n", __func__);
		return -EINVAL;
	}

	mask_props = &profiler->mask_props;
	te = &profiler->te_info;
	hiber = &profiler->hiber_info;

	while(!kthread_should_stop()) {
		cycle_time = profiler->conf->cycle_time > 5 ? profiler->conf->cycle_time : CYCLE_TIME_DEFAULT;
		schedule_timeout_interruptible(cycle_time);

		if (!prof_en(profiler, profiler)) {
			schedule_timeout_interruptible(msecs_to_jiffies(cycle_time * 10));
			continue;
		}
		
		len = 0;
		if (prof_disp(profiler, hiber)) {
			len += snprintf(text + len, ARRAY_SIZE(text) - len, "%c ",
				hiber->hiber_status ? 'H' : ' ');
		}
		
		if (prof_disp(profiler, fps)) {
			profile_fps(profiler);
			len += snprintf(text + len, ARRAY_SIZE(text) - len, "%3d ", profiler->fps.comp_fps);
		}

		if (prof_disp(profiler, te)) {
			if (te->last_diff > 0) {
				len += snprintf(text + len, ARRAY_SIZE(text) - len, "%3d.%02d ",
					te->last_diff / 1000, (te->last_diff % 1000) / 10);
			}
		}
		
		if (prof_en(profiler, mprint) && len > 0 && strncmp(text_old, text, len) != 0) {
			if (prof_en(profiler, timediff))
				ktime_get_ts(&cur_ts);
			
			ret = char_to_mask_img(mask_props, text);

			if (prof_en(profiler, timediff))
				ktime_get_ts(&last_ts);

			if (ret < 0) {
				panel_err("[DISP_PROFILER] : err on mask img gen '%s'\n", text);
				continue;
			}
			if (prof_en(profiler, timediff)) {
				delta_ts = timespec_sub(last_ts, cur_ts);
				elapsed_usec = timespec_to_ns(&delta_ts) / 1000;
			}		
			profiler_info(profiler, mprint_debug, "[DISP_PROFILER] generated img by '%s', size %d, cyc %d\n",
				text, mask_props->data_size, cycle_time);

			profiler_info(profiler, timediff_en, "[DISP_PROFILER] generated elapsed = %lldus, '%s'\n", elapsed_usec, text);
			
			profiler_mprint_update(profiler);
			memcpy(text_old, text, ARRAY_SIZE(text));
		}
		
	}
	return 0;
}

static ssize_t prop_config_mprint_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct profiler_device *profiler;
	struct panel_device *panel = dev_get_drvdata(dev);
	int *data;
	int i, len = 0;
	
	profiler = &panel->profiler;
	if (profiler == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler is null\n", __func__);
		return -EINVAL;
	}
	
	if (profiler->mask_config == NULL) {
		panel_err("[DISP_PROFILER] %s:mask config is null\n", __func__);
		return -EINVAL;
	}

	data = (int *) profiler->mask_config;
	for (i=0; i<sizeof(struct mprint_config) / sizeof(int); i++) {
		len += snprintf(buf + len, PAGE_SIZE - len, "%12s",
			(i < ARRAY_SIZE(mprint_config_names)) ? mprint_config_names[i] : "(null)");
	}
	len += snprintf(buf + len, PAGE_SIZE - len, "\n");

	for (i=0; i<sizeof(struct mprint_config) / sizeof(int); i++) {
		len += snprintf(buf + len, PAGE_SIZE - len, "%12d", *(data + i));
	}
	len += snprintf(buf + len, PAGE_SIZE - len, "\n");

	return strlen(buf);
}

static ssize_t prop_config_mprint_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	struct profiler_device *profiler;
	struct panel_device *panel = dev_get_drvdata(dev);
	int *data;
	int val;
	int i, len = 0, read, ret;

	profiler = &panel->profiler;
	if (profiler == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler is null\n", __func__);
		return -EINVAL;
	}

	if (profiler->mask_config == NULL) {
		panel_err("[DISP_PROFILER] %s:mask config is null\n", __func__);
		return -EINVAL;
	}

	data = (int *) profiler->mask_config;
	for (i=0; i<sizeof(struct mprint_config) / sizeof(int); i++) {
		ret = sscanf(buf + len, "%d%n", &val, &read);
		if (ret < 1)
			break;
		*(data+i) = val;
		len += read;
		panel_info("[DISP_PROFILER] %s:config[%d] set to %d\n", __func__, i, val);
	}

	return size;
}

static ssize_t prop_partial_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct profiler_device *profiler;
	struct panel_device *panel = dev_get_drvdata(dev);

	profiler = &panel->profiler;
	if (profiler == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler is null\n", __func__);
		return -EINVAL;
	}

//	snprintf(buf, PAGE_SIZE, "%u\n", profiler->win_rect.disp_en);

	return strlen(buf);
}


static ssize_t prop_partial_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	int value, rc;
	struct profiler_device *profiler;
	struct panel_device *panel = dev_get_drvdata(dev);

	profiler = &panel->profiler;
	if (profiler == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler is null\n", __func__);
		return -EINVAL;
	}

	rc = kstrtouint(buf, 0, &value);
	if (rc < 0)
		return rc;

	return size;
}

static ssize_t prop_config_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct profiler_device *profiler;
	struct panel_device *panel = dev_get_drvdata(dev);
	int *data;
	int i, len = 0, count;
	
	profiler = &panel->profiler;
	if (profiler == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler is null\n", __func__);
		return -EINVAL;
	}

	if (profiler->conf == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler config is null\n", __func__);
		return -EINVAL;
	}

	count = sizeof(struct profiler_config) / sizeof(int);

	if (count != ARRAY_SIZE(profiler_config_names)) {
		len += snprintf(buf + len, PAGE_SIZE - len,
			"CONFIG SIZE MISMATCHED!! configurations are may be wrong(%d, %d)\n",
			count, ARRAY_SIZE(profiler_config_names));
	}

	if (count > ARRAY_SIZE(profiler_config_names))
		count = ARRAY_SIZE(profiler_config_names);

	data = (int *) profiler->conf;

	for (i=0; i<count; i++) {
		len += snprintf(buf + len, PAGE_SIZE - len, "%s=%d%s",
			(i < ARRAY_SIZE(profiler_config_names)) ? profiler_config_names[i] : "(null)",
			*(data+i),
			(i < count - 1) ? "," : "\n");
	}
	
	return strlen(buf);
}

static ssize_t prop_config_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	struct profiler_device *profiler;
	struct panel_device *panel = dev_get_drvdata(dev);
	char str[1024] = { 0, };
	char *strbuf, *tok, *field, *value;
	int *data;
	int val;
	int i, ret;

	profiler = &panel->profiler;
	if (profiler == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler is null\n", __func__);
		return -EINVAL;
	}

	if (profiler->conf == NULL) {
		panel_err("[DISP_PROFILER] %s:profiler config is null\n", __func__);
		return -EINVAL;
	}

	data = (int *) profiler->conf;
	
	memcpy(str, buf, size < 1024 ? size : 1024);
	strbuf = str;

	while ((tok = strsep(&strbuf, ",")) != NULL) {
		field = strsep(&tok, "=");
		if (field == NULL) {
			panel_err("[DISP_PROFILER] %s, invalid field\n", __func__);
			return -EINVAL;
		}
		field = strim(field);
		if (strlen(field) < 1) {
			panel_err("[DISP_PROFILER] %s, invalid field\n", __func__);
			return -EINVAL;
		}
		value = strsep(&tok, "=");
		if (value == NULL) {
			panel_err("[DISP_PROFILER] %s, invalid value with field %s\n", __func__, field);
			return -EINVAL;
		}
		profiler_info(profiler, profiler_debug, "[DISP_PROFILER] %s: field %s with value %s\n", __func__, field, value);
		ret = kstrtouint(strim(value), 0, &val);
		if (ret < 0) {
			panel_err("[DISP_PROFILER] %s, invalid value %s, ret %d\n", __func__, value, ret);
			return ret;
		}
		for (i=0; i<ARRAY_SIZE(profiler_config_names); i++) {
			if (!strncmp(field, profiler_config_names[i], strlen(profiler_config_names[i])))
				break;
		}
		if (i < ARRAY_SIZE(profiler_config_names)) {
			*(data + i) = val;
			panel_info("[DISP_PROFILER] %s: config set %s->%d\n",
				__func__, profiler_config_names[i], val);
		}
	}

	return size;
}

struct device_attribute profiler_attrs[] = {
	__PANEL_ATTR_RW(prop_partial, 0660),
	__PANEL_ATTR_RW(prop_config, 0660),
	__PANEL_ATTR_RW(prop_config_mprint, 0660),
};

int profiler_probe(struct panel_device *panel, struct profiler_tune *tune)
{
	int i;
	int ret = 0;
	struct lcd_device *lcd;
	struct profiler_device *profiler;

	if (!panel) {
		panel_err("%s:panel is not exist\n", __func__);
		return -EINVAL;
	}

	if (!tune) {
		panel_err("%s:tune is null\n", __func__);
		return -EINVAL;
	}

	lcd = panel->lcd;
	if (unlikely(!lcd)) {
		panel_err("%s: lcd device not exist\n", __func__);
		return -ENODEV;
	}

	if (tune->conf == NULL) {
		panel_err("%s:profiler config is null\n", __func__);
		return -EINVAL;
	}

	profiler = &panel->profiler;
	profiler_init_v4l2_subdev(panel);

	profiler->seqtbl = tune->seqtbl;
	profiler->nr_seqtbl = tune->nr_seqtbl;
	profiler->maptbl = tune->maptbl;
	profiler->nr_maptbl = tune->nr_maptbl;

	for (i = 0; i < profiler->nr_maptbl; i++) {
		profiler->maptbl[i].pdata = profiler;
		maptbl_init(&profiler->maptbl[i]);
	}

	for (i = 0; i < ARRAY_SIZE(profiler_attrs); i++) {
		ret = device_create_file(&lcd->dev, &profiler_attrs[i]);
		if (ret < 0) {
			dev_err(&lcd->dev, "%s, failed to add %s sysfs entries, %d\n",
					__func__, profiler_attrs[i].attr.name, ret);
			return -ENODEV;
		}
	}

	spin_lock_init(&profiler->te_info.slock);

	profiler->conf = tune->conf;

// mask config
	profiler->mask_config = tune->mprint_config;

// mask props
	profiler->mask_props.conf = profiler->mask_config;
	profiler->mask_props.pkts_pos = 0;
	profiler->mask_props.pkts_size = 0;

	if (profiler->mask_config->max_len < 2) {
		profiler->mask_config->max_len = MASK_DATA_SIZE_DEFAULT;
	}

	profiler->mask_props.data = kmalloc(profiler->mask_config->max_len, GFP_KERNEL);
	profiler->mask_props.data_max = profiler->mask_config->max_len;
	
	profiler->mask_props.pkts_max = profiler->mask_props.data_max / 2;
	profiler->mask_props.pkts = kmalloc(sizeof(struct mprint_packet) * profiler->mask_props.pkts_max, GFP_KERNEL);
	if (!profiler->mask_props.pkts) {
		panel_err("[DISP_PROFILER] %s:failed to allocate mask packet buffer\n", __func__);
		goto err;
	}
	
	profiler->thread = kthread_run(profiler_thread, profiler, "profiler");
	if (IS_ERR_OR_NULL(profiler->thread)) {
		panel_err("[DISP_PROFILER] %s:failed to run thread\n", __func__);
		ret = PTR_ERR(profiler->thread);
		goto err;
	}
/*
	profiler->fps.disp_en = false;
	profiler->win_rect.disp_en = false;
	*/
	profiler->initialized = true;

err:
	return ret;
}

