/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Window update file for Samsung EXYNOS DPU driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <video/mipi_display.h>

#include "./panels/exynos_panel_drv.h"
#include "decon.h"
#include "dpp.h"
#include "dsim.h"
#if defined(CONFIG_EXYNOS_DECON_DQE)
#include "dqe.h"
#endif

static void win_update_adjust_region(struct decon_device *decon,
		struct decon_win_config *win_config,
		struct decon_reg_data *regs)
{
	int i;
	int div_w, div_h;
	struct decon_rect r1, r2;
	struct decon_win_config *update_config = &win_config[DECON_WIN_UPDATE_IDX];
	struct decon_win_config *config;
	struct decon_frame adj_region;

	regs->need_update = false;
	DPU_FULL_RECT(&regs->up_region, decon->lcd_info);

	if (!decon->win_up.enabled)
		return;

	if (update_config->state != DECON_WIN_STATE_UPDATE)
		return;

	if ((update_config->dst.x < 0) || (update_config->dst.y < 0)) {
		update_config->state = DECON_WIN_STATE_DISABLED;
		return;
	}

	r1.left = update_config->dst.x;
	r1.top = update_config->dst.y;
	r1.right = r1.left + update_config->dst.w - 1;
	r1.bottom = r1.top + update_config->dst.h - 1;

	for (i = 0; i < decon->dt.max_win; i++) {
		config = &win_config[i];
		if (config->state != DECON_WIN_STATE_DISABLED) {
			if (config->dpp_parm.rot || is_scaling(config)) {
				update_config->state = DECON_WIN_STATE_DISABLED;
				return;
			}
		}
	}

	DPU_DEBUG_WIN("original update region[%d %d %d %d]\n",
			update_config->dst.x, update_config->dst.y,
			update_config->dst.w, update_config->dst.h);

	r2.left = (r1.left / decon->win_up.rect_w) * decon->win_up.rect_w;
	r2.top = (r1.top / decon->win_up.rect_h) * decon->win_up.rect_h;

	div_w = (r1.right + 1) / decon->win_up.rect_w;
	div_w = (div_w * decon->win_up.rect_w == r1.right + 1) ? div_w : div_w + 1;
	r2.right = div_w * decon->win_up.rect_w - 1;

	div_h = (r1.bottom + 1) / decon->win_up.rect_h;
	div_h = (div_h * decon->win_up.rect_h == r1.bottom + 1) ? div_h : div_h + 1;
	r2.bottom = div_h * decon->win_up.rect_h - 1;

	/* TODO: Now, 4 slices must be used. This will be modified */
	r2.left = 0;
	r2.right = decon->lcd_info->xres - 1;

	memcpy(&regs->up_region, &r2, sizeof(struct decon_rect));

	memset(&adj_region, 0, sizeof(struct decon_frame));
	adj_region.x = regs->up_region.left;
	adj_region.y = regs->up_region.top;
	adj_region.w = regs->up_region.right - regs->up_region.left + 1;
	adj_region.h = regs->up_region.bottom - regs->up_region.top + 1;
	DPU_EVENT_LOG_UPDATE_REGION(&decon->sd, &update_config->dst, &adj_region);

	DPU_DEBUG_WIN("adjusted update region[%d %d %d %d]\n",
			adj_region.x, adj_region.y, adj_region.w, adj_region.h);
}

static void win_update_check_limitation(struct decon_device *decon,
		struct decon_win_config *win_config,
		struct decon_reg_data *regs)
{
	struct decon_win_config *config;
	struct decon_win_rect update;
	struct decon_rect r;
	struct v4l2_subdev *sd;
	struct dpp_ch_restriction ch_res;
	struct dpp_restriction *res;
	const struct dpu_fmt *fmt_info;
	int i;
	int sz_align = 1;
	int adj_src_x = 0, adj_src_y = 0;

	for (i = 0; i < decon->dt.max_win; i++) {
		config = &win_config[i];
		if (config->state == DECON_WIN_STATE_DISABLED)
			continue;

		if (config->state == DECON_WIN_STATE_CURSOR)
			goto change_full;

		r.left = config->dst.x;
		r.top = config->dst.y;
		r.right = config->dst.w + config->dst.x - 1;
		r.bottom = config->dst.h + config->dst.y - 1;

		if (!decon_intersect(&regs->up_region, &r))
			continue;

		decon_intersection(&regs->up_region, &r, &r);

		if (!(r.right - r.left) && !(r.bottom - r.top))
			continue;

		fmt_info = dpu_find_fmt_info(config->format);
		if (!fmt_info) {
			DPU_DEBUG_WIN("Do not surpport format(%d)\n", config->format);
			goto change_full;
		}
		if (IS_YUV(fmt_info)) {
			/* check alignment for NV12/NV21 format */
			update.x = regs->up_region.left;
			update.y = regs->up_region.top;
			sz_align = 2;

			if (update.y > config->dst.y)
				adj_src_y = config->src.y + (update.y - config->dst.y);
			if (update.x > config->dst.x)
				adj_src_x = config->src.x + (update.x - config->dst.x);

			if (adj_src_x & 0x1 || adj_src_y & 0x1)
				goto change_full;
		}

		sd = decon->dpp_sd[0];
		v4l2_subdev_call(sd, core, ioctl, DPP_GET_RESTRICTION, &ch_res);
		res = &ch_res.restriction;

		if (((r.right - r.left) < (res->src_f_w.min * sz_align)) ||
				((r.bottom - r.top) < (res->src_f_h.min * sz_align))) {
			goto change_full;
		}

		/* cursor async */
		if (((r.right - r.left) > decon->lcd_info->xres) ||
			((r.bottom - r.top) > decon->lcd_info->yres)) {
			goto change_full;
		}
	}

	return;

change_full:
	DPU_DEBUG_WIN("changed full: win(%d) ch(%d) [%d %d %d %d]\n",
			i, config->channel,
			config->dst.x, config->dst.y,
			config->dst.w, config->dst.h);
	DPU_FULL_RECT(&regs->up_region, decon->lcd_info);
	return;
}

static void win_update_reconfig_coordinates(struct decon_device *decon,
		struct decon_win_config *win_config,
		struct decon_reg_data *regs)
{
	struct decon_win_config *config;
	struct decon_win_rect update;
	struct decon_frame origin_dst, origin_src;
	struct decon_rect r;
	int i;

	/* Assume that, window update doesn't support in case of scaling */
	for (i = 0; i < decon->dt.max_win; i++) {
		config = &win_config[i];

		if (config->state == DECON_WIN_STATE_DISABLED)
			continue;

		r.left = config->dst.x;
		r.top = config->dst.y;
		r.right = r.left + config->dst.w - 1;
		r.bottom = r.top + config->dst.h - 1;
		if (!decon_intersect(&regs->up_region, &r)) {
			config->state = DECON_WIN_STATE_DISABLED;
			continue;
		}

		update.x = regs->up_region.left;
		update.y = regs->up_region.top;
		update.w = regs->up_region.right - regs->up_region.left + 1;
		update.h = regs->up_region.bottom - regs->up_region.top + 1;

		memcpy(&origin_dst, &config->dst, sizeof(struct decon_frame));
		memcpy(&origin_src, &config->src, sizeof(struct decon_frame));

		/* reconfigure destination coordinates */
		if (update.x > config->dst.x)
			config->dst.w = min(update.w,
					config->dst.x + config->dst.w - update.x);
		else if (update.x + update.w < config->dst.x + config->dst.w)
			config->dst.w = min(config->dst.w,
					update.w + update.x - config->dst.x);

		if (update.y > config->dst.y)
			config->dst.h = min(update.h,
					config->dst.y + config->dst.h - update.y);
		else if (update.y + update.h < config->dst.y + config->dst.h)
			config->dst.h = min(config->dst.h,
					update.h + update.y - config->dst.y);
		config->dst.x = max(config->dst.x - update.x, 0);
		config->dst.y = max(config->dst.y - update.y, 0);

		/* reconfigure source coordinates */
		if (update.y > origin_dst.y)
			config->src.y += (update.y - origin_dst.y);
		if (update.x > origin_dst.x)
			config->src.x += (update.x - origin_dst.x);
		config->src.w = config->dst.w;
		config->src.h = config->dst.h;

		DPU_DEBUG_WIN("win(%d), ch(%d)\n", i, config->channel);
		DPU_DEBUG_WIN("src: origin[%d %d %d %d] -> change[%d %d %d %d]\n",
				origin_src.x, origin_src.y,
				origin_src.w, origin_src.h,
				config->src.x, config->src.y,
				config->src.w, config->src.h);
		DPU_DEBUG_WIN("dst: origin[%d %d %d %d] -> change[%d %d %d %d]\n",
				origin_dst.x, origin_dst.y,
				origin_dst.w, origin_dst.h,
				config->dst.x, config->dst.y,
				config->dst.w, config->dst.h);
	}
}

static int dpu_find_display_mode(struct decon_device *decon, int w, int h, int fps)
{
	struct exynos_display_mode_info *supported_mode;
	int i;

	for (i = 0; i < decon->lcd_info->display_mode_count; i++) {
		supported_mode = &decon->lcd_info->display_mode[i];
		if ((supported_mode->mode.width == w) &&
			(supported_mode->mode.height == h) &&
			(supported_mode->mode.fps == fps)) {
			break;
		}
	}

	if (i == decon->lcd_info->display_mode_count)
		return -EINVAL;

	return i;
}

static bool dpu_need_mres_config(struct decon_device *decon,
		struct decon_win_config *win_config,
		struct decon_reg_data *regs)
{
	struct decon_win_config *mres_config = &win_config[DECON_WIN_UPDATE_IDX];
	int i, mode_idx, fps, fps_table[3];

	regs->mode_update = false;

	if (!decon->mres_enabled) {
		DPU_DEBUG_MRES("multi-resolution feature is disabled\n");
		goto end;
	}

	if (decon->dt.out_type != DECON_OUT_DSI) {
		DPU_DEBUG_MRES("multi resolution only support DSI path\n");
		goto end;
	}

	if (!decon->lcd_info->mres.en) {
		DPU_DEBUG_MRES("panel doesn't support multi-resolution\n");
		goto end;
	}

	if (!(mres_config->state & DECON_WIN_STATE_MRESOL))
		goto end;

	/* requested LCD resolution */
	regs->lcd_width = mres_config->dst.f_w;
	regs->lcd_height = mres_config->dst.f_h;

	/* compare previous and requested LCD resolution */
	if ((decon->lcd_info->xres == regs->lcd_width) &&
			(decon->lcd_info->yres == regs->lcd_height)) {
		DPU_DEBUG_MRES("prev & req LCD resolution is same(%d %d)\n",
				regs->lcd_width, regs->lcd_height);
		goto end;
	}

	/* match supported and requested display mode(resolution & fps) */
	fps_table[0] = decon->lcd_info->target_fps;
	fps_table[1] = decon->lcd_info->fps;
	fps_table[2] = 60;
	for (i = 0; i < ARRAY_SIZE(fps_table); i++) {
		fps = fps_table[i];
		mode_idx = dpu_find_display_mode(decon, regs->lcd_width,
				regs->lcd_height, fps);
		if (mode_idx >= 0) {
			regs->mode_update = true;
			regs->mode_idx = mode_idx;
			break;
		}
	}

	if (mode_idx < 0) {
		DPU_ERR_MRES("%s: display mode not found(%dx%dx@%d)\n",
				__func__, regs->lcd_width, regs->lcd_height, 60);
	} else {
		DPU_DEBUG_MRES("%s: found display mode(%dx%dx@%d)\n",
				__func__, regs->lcd_width, regs->lcd_height, fps);
	}

	DPU_DEBUG_MRES("update(%d), mode idx(%d), mode(%dx%d@%d -> %dx%d@%d)\n",
			regs->mode_update, regs->mode_idx,
			decon->lcd_info->xres, decon->lcd_info->yres,
			decon->lcd_info->fps,
			regs->lcd_width, regs->lcd_height, fps);

end:
	return regs->mode_update;
}

void dpu_prepare_win_update_config(struct decon_device *decon,
		struct decon_win_config_data *win_data,
		struct decon_reg_data *regs)
{
	struct decon_win_config *win_config = win_data->config;
	bool reconfigure = false;
	struct decon_rect r;

	if (!decon->win_up.enabled)
		return;

	if (decon->dt.out_type != DECON_OUT_DSI)
		return;

	/* If LCD resolution is changed, window update is ignored */
	if (dpu_need_mres_config(decon, win_config, regs)) {
		regs->up_region.left = 0;
		regs->up_region.top = 0;
		regs->up_region.right = regs->lcd_width - 1;
		regs->up_region.bottom = regs->lcd_height - 1;
		return;
	}

	/* find adjusted update region on LCD */
	win_update_adjust_region(decon, win_config, regs);

	/* check DPP hw limitation if violated, update region is changed to full */
	win_update_check_limitation(decon, win_config, regs);

	/*
	 * If update region is changed, need_update flag is set.
	 * That means hw configuration is needed
	 */
	if (is_decon_rect_differ(&decon->win_up.prev_up_region, &regs->up_region))
		regs->need_update = true;
	else
		regs->need_update = false;

	/*
	 * If partial update region is requested, source and destination
	 * coordinates are needed to change if overlapped with update region.
	 */
	DPU_FULL_RECT(&r, decon->lcd_info);
	if (is_decon_rect_differ(&regs->up_region, &r))
		reconfigure = true;

	if (regs->need_update || reconfigure) {
		DPU_DEBUG_WIN("need_update(%d), reconfigure(%d)\n",
				regs->need_update, reconfigure);
		DPU_EVENT_LOG_WINUP_FLAGS(&decon->sd, regs->need_update, reconfigure);
	}

	/* Reconfigure source and destination coordinates, if needed. */
	if (reconfigure)
		win_update_reconfig_coordinates(decon, win_config, regs);
}

static int dpu_check_mres_condition(struct decon_device *decon,
		bool mode_update)
{
	if (!decon->mres_enabled) {
		DPU_DEBUG_MRES("multi-resolution feature is disabled\n");
		return -EPERM;
	}

	if (decon->dt.out_type != DECON_OUT_DSI) {
		DPU_DEBUG_MRES("multi resolution only support DSI path\n");
		return -EPERM;
	}

	if (!decon->lcd_info->mres.en) {
		DPU_DEBUG_MRES("panel doesn't support multi-resolution\n");
		return -EPERM;
	}

	if (!mode_update)
		return -EPERM;

	return 0;
}

static int dpu_update_display_mode(struct decon_device *decon,
		int display_mode_index)
{
	struct dsim_device *dsim = get_dsim_drvdata(0);
	struct exynos_display_mode_info *mode_info;

	if (display_mode_index >=
			decon->lcd_info->display_mode_count)
		return -EINVAL;

	if (IS_ERR_OR_NULL(dsim)) {
		DPU_ERR_MRES("%s: dsim device ptr is invalid\n", __func__);
		return -EINVAL;
	}

	dsim->panel->lcd_info.cur_mode_idx = display_mode_index;

	mode_info = dsim->panel->lcd_info.display_mode;
	dsim->panel->lcd_info.xres =
		mode_info[display_mode_index].mode.width;
	dsim->panel->lcd_info.yres =
		mode_info[display_mode_index].mode.height;

	/*
	dsim->panel->lcd_info.fps =
		mode_info[display_mode_index].mode.fps;
	*/

	dsim->panel->lcd_info.dsc.en =
		mode_info[display_mode_index].dsc_en;
	dsim->panel->lcd_info.dsc.slice_h =
		mode_info[display_mode_index].dsc_height;
	dsim->panel->lcd_info.dsc.enc_sw =
		mode_info[display_mode_index].dsc_enc_sw;
	dsim->panel->lcd_info.dsc.dec_sw =
		mode_info[display_mode_index].dsc_dec_sw;

	DPU_DEBUG_MRES("changed display_mode[%d] resol(%dx%d@%d) dsc enc/dec sw(%d %d)\n",
			display_mode_index, dsim->panel->lcd_info.xres,
			dsim->panel->lcd_info.yres, dsim->panel->lcd_info.fps,
			dsim->panel->lcd_info.dsc.enc_sw, dsim->panel->lcd_info.dsc.dec_sw);

	return 0;
}

void dpu_update_mres_lcd_info(struct decon_device *decon,
		struct decon_reg_data *regs)
{
	struct dsim_device *dsim = get_dsim_drvdata(0);

	if (dpu_check_mres_condition(decon, regs->mode_update))
		return;

	if (IS_ERR_OR_NULL(dsim)) {
		DPU_ERR_MRES("%s: dsim device ptr is invalid\n", __func__);
		return;
	}

	/* backup current LCD resolution information to previous one */
	dsim->panel->lcd_info.old_xres = dsim->panel->lcd_info.xres;
	dsim->panel->lcd_info.old_yres = dsim->panel->lcd_info.yres;
	dpu_update_display_mode(decon, regs->mode_idx);

	DPU_DEBUG_MRES("changed LCD resolution(%d %d), dsc enc/dec sw(%d %d)\n",
			decon->lcd_info->xres, decon->lcd_info->yres,
			dsim->panel->lcd_info.dsc.enc_sw,
			dsim->panel->lcd_info.dsc.dec_sw);
}

void dpu_set_mres_config(struct decon_device *decon, struct decon_reg_data *regs)
{
	struct dsim_device *dsim = get_dsim_drvdata(0);
	struct decon_param p;
	struct exynos_display_mode_info *mode_info;
	struct vrr_config_data vrr_info;
	int idx, old_xres, old_yres;

	if (dpu_check_mres_condition(decon, regs->mode_update))
		return;

	/*
	 * Before LCD resolution is changed, previous frame data must be
	 * finished to transfer.
	 */
	decon_reg_wait_idle_status_timeout(decon->id, IDLE_WAIT_TIMEOUT);

	/*
	 * set vrr if new resolution & current fps is not available.
	 */

	mode_info = dsim->panel->lcd_info.display_mode;
	idx = regs->mode_idx;

	old_xres = dsim->panel->lcd_info.old_xres;
	old_yres = dsim->panel->lcd_info.old_yres;
	if ((dpu_find_display_mode(decon, regs->lcd_width, regs->lcd_height,
					decon->lcd_info->fps) < 0) &&
		(dpu_find_display_mode(decon, old_xres, old_yres,
					mode_info[idx].mode.fps) >= 0)) {
		vrr_info.fps = mode_info[idx].mode.fps;
		vrr_info.mode = dsim->panel->lcd_info.target_vrr_mode;
		dsim_call_panel_ops(dsim, EXYNOS_PANEL_IOC_SET_VRRFRESH, &vrr_info);
		dpu_set_vrr_config(decon, &vrr_info);
		DPU_INFO_MRES("set vrr(fps:%d mode:%d) before mres(%dx%d)\n",
				vrr_info.fps, vrr_info.mode, regs->lcd_width, regs->lcd_height);
	}

	/* transfer LCD resolution change commands to panel */
	dsim_call_panel_ops(dsim, EXYNOS_PANEL_IOC_MRES, &regs->mode_idx);

	/*
	 * set vrr if current fps is different with new display mode's fps.
	 */
	if ((mode_info[idx].mode.fps != decon->lcd_info->fps) ||
		(decon->lcd_info->vrr_mode !=
		 dsim->panel->lcd_info.target_vrr_mode)) {
		if (dpu_find_display_mode(decon, regs->lcd_width,
				regs->lcd_height, mode_info[idx].mode.fps) >= 0) {
			vrr_info.fps = mode_info[idx].mode.fps;
			vrr_info.mode = dsim->panel->lcd_info.target_vrr_mode;
			dpu_set_vrr_config(decon, &vrr_info);
			DPU_INFO_MRES("set vrr(fps:%d mode:%d) after mres(%dx%d)\n",
				vrr_info.fps, vrr_info.mode, regs->lcd_width, regs->lcd_height);
		}
	}

	/* DECON and DSIM are reconfigured by changed LCD resolution */
	dsim_reg_set_mres(dsim->id, &dsim->panel->lcd_info);
	decon_to_init_param(decon, &p);
	decon_reg_set_mres(decon->id, &p);

	/* If LCD resolution is changed, initial partial size is also changed */
	dpu_init_win_update(decon);
}

void dpu_set_vrr_config(struct decon_device *decon, struct vrr_config_data *vrr_info)
{
	struct dsim_device *dsim = get_dsim_drvdata(0);
	int display_mode_index;

	if (decon->dt.out_type != DECON_OUT_DSI) {
		DPU_DEBUG_MRES("vrr only support DSI path\n");
		return;
	}

	if (IS_ERR_OR_NULL(dsim)) {
		DPU_ERR_MRES("%s: dsim device ptr is invalid\n", __func__);
		return;
	}

	display_mode_index =
		dpu_find_display_mode(decon, dsim->panel->lcd_info.xres,
				dsim->panel->lcd_info.yres, vrr_info->fps);
	if (display_mode_index < 0) {
		DPU_ERR_MRES("%s: not supported fps:%d in %dx%d\n",
				__func__, vrr_info->fps, dsim->panel->lcd_info.xres,
				dsim->panel->lcd_info.yres);
		return;
	}
	dpu_update_display_mode(decon, display_mode_index);

	/* transfer refresh change commands to panel */
	dsim_call_panel_ops(dsim, EXYNOS_PANEL_IOC_SET_VRRFRESH, vrr_info);
}

#if !defined(CONFIG_EXYNOS_COMMON_PANEL)
static int win_update_send_partial_command(struct dsim_device *dsim,
		struct decon_rect *rect)
{
	char column[5];
	char page[5];
	int retry;

	DPU_DEBUG_WIN("SET: [%d %d %d %d]\n", rect->left, rect->top,
			rect->right - rect->left + 1, rect->bottom - rect->top + 1);

	column[0] = MIPI_DCS_SET_COLUMN_ADDRESS;
	column[1] = (rect->left >> 8) & 0xff;
	column[2] = rect->left & 0xff;
	column[3] = (rect->right >> 8) & 0xff;
	column[4] = rect->right & 0xff;

	page[0] = MIPI_DCS_SET_PAGE_ADDRESS;
	page[1] = (rect->top >> 8) & 0xff;
	page[2] = rect->top & 0xff;
	page[3] = (rect->bottom >> 8) & 0xff;
	page[4] = rect->bottom & 0xff;

	retry = 2;
	while (dsim_write_data(dsim, MIPI_DSI_DCS_LONG_WRITE,
				(unsigned long)column, ARRAY_SIZE(column), true) != 0) {
		dsim_err("failed to write COLUMN_ADDRESS\n");
		dsim_reg_function_reset(dsim->id);
		if (--retry <= 0) {
			dsim_err("COLUMN_ADDRESS is failed: exceed retry count\n");
			return -EINVAL;
		}
	}

	retry = 2;
	while (dsim_write_data(dsim, MIPI_DSI_DCS_LONG_WRITE,
				(unsigned long)page, ARRAY_SIZE(page), true) != 0) {
		dsim_err("failed to write PAGE_ADDRESS\n");
		dsim_reg_function_reset(dsim->id);
		if (--retry <= 0) {
			dsim_err("PAGE_ADDRESS is failed: exceed retry count\n");
			return -EINVAL;
		}
	}

	return 0;
}
#else
static int win_update_send_partial_command(struct dsim_device *dsim,
		struct decon_rect *rect)
{
	DPU_DEBUG_WIN("SET: [%d %d %d %d]\n", rect->left, rect->top,
			rect->right - rect->left + 1, rect->bottom - rect->top + 1);

	dsim_call_panel_ops(dsim, EXYNOS_PANEL_IOC_SETAREA, rect);

	return 0;
}
#endif

static void win_update_find_included_slice(struct exynos_panel_info *lcd,
		struct decon_rect *rect, bool in_slice[])
{
	int slice_left, slice_right, slice_width;
	int i;

	slice_left = 0;
	slice_right = 0;
	slice_width = lcd->dsc.dec_sw;

	for (i = 0; i < lcd->dsc.slice_num; ++i) {
		slice_left = slice_width * i;
		slice_right = slice_left + slice_width - 1;
		in_slice[i] = false;

		if ((slice_left >= rect->left) && (slice_right <= rect->right))
			in_slice[i] = true;

		DPU_DEBUG_WIN("slice_left(%d), right(%d)\n", slice_left, slice_right);
		DPU_DEBUG_WIN("slice[%d] is %s\n", i,
				in_slice[i] ? "included" : "not included");
	}
}

static void win_update_set_partial_size(struct decon_device *decon,
		struct decon_rect *rect)
{
	struct exynos_panel_info lcd_info;
	struct dsim_device *dsim = get_dsim_drvdata(0);
	bool in_slice[MAX_DSC_SLICE_CNT];

	memcpy(&lcd_info, decon->lcd_info, sizeof(struct exynos_panel_info));
	lcd_info.xres = rect->right - rect->left + 1;
	lcd_info.yres = rect->bottom - rect->top + 1;

	lcd_info.hfp = decon->lcd_info->hfp +
		((decon->lcd_info->xres - lcd_info.xres) >> 1);
	lcd_info.vfp = decon->lcd_info->vfp + decon->lcd_info->yres - lcd_info.yres;

	dsim_reg_set_partial_update(dsim->id, &lcd_info);

	win_update_find_included_slice(decon->lcd_info, rect, in_slice);
	decon_reg_set_partial_update(decon->id, decon->dt.dsi_mode,
			decon->lcd_info, in_slice,
			lcd_info.xres, lcd_info.yres);
#if defined(CONFIG_EXYNOS_DECON_DQE)
	dqe_reg_start(decon->id, &lcd_info);
#endif
	DPU_DEBUG_WIN("SET: vfp %d vbp %d vsa %d hfp %d hbp %d hsa %d w %d h %d\n",
			lcd_info.vfp, lcd_info.vbp, lcd_info.vsa,
			lcd_info.hfp, lcd_info.hbp, lcd_info.hsa,
			lcd_info.xres, lcd_info.yres);
}

void dpu_set_win_update_config(struct decon_device *decon,
		struct decon_reg_data *regs)
{
	struct dsim_device *dsim = get_dsim_drvdata(0);
	bool in_slice[MAX_DSC_SLICE_CNT];
	bool full_partial_update = false;

	if (!decon->win_up.enabled)
		return;

	if (decon->dt.out_type != DECON_OUT_DSI)
		return;

	if (regs == NULL) {
		regs = kzalloc(sizeof(struct decon_reg_data), GFP_KERNEL);
		if (!regs) {
			decon_err("%s: reg_data allocation fail\n", __func__);
			return;
		}
		DPU_FULL_RECT(&regs->up_region, decon->lcd_info);
		regs->need_update = true;
		full_partial_update = true;
	}

	if (regs->need_update) {
		win_update_find_included_slice(decon->lcd_info,
				&regs->up_region, in_slice);

		/* TODO: Is waiting framedone irq needed in KC ? */

		/*
		 * hw configuration related to partial update must be set
		 * without DMA operation
		 */
		decon_reg_wait_idle_status_timeout(decon->id, IDLE_WAIT_TIMEOUT);
		win_update_send_partial_command(dsim, &regs->up_region);
		win_update_set_partial_size(decon, &regs->up_region);
		DPU_EVENT_LOG_APPLY_REGION(&decon->sd, &regs->up_region);
	}

	if (full_partial_update)
		kfree(regs);
}

void dpu_set_win_update_partial_size(struct decon_device *decon,
		struct decon_rect *up_region)
{
	if (!decon->win_up.enabled)
		return;

	win_update_set_partial_size(decon, up_region);
}

void dpu_init_win_update(struct decon_device *decon)
{
	struct exynos_panel_info *lcd = decon->lcd_info;

	decon->win_up.enabled = false;
	decon->cursor.xpos = lcd->xres / 2;
	decon->cursor.ypos = lcd->yres / 2;

	if (!IS_ENABLED(CONFIG_EXYNOS_WINDOW_UPDATE)) {
		decon_info("window update feature is disabled\n");
		return;
	}

	if (decon->dt.out_type != DECON_OUT_DSI) {
		decon_info("out_type(%d) doesn't support window update\n",
				decon->dt.out_type);
		return;
	}

	if (lcd->dsc.en) {
		decon->win_up.rect_w = lcd->xres / lcd->dsc.slice_num;
		decon->win_up.rect_h = lcd->dsc.slice_h;
	} else {
		decon->win_up.rect_w = MIN_WIN_BLOCK_WIDTH;
		decon->win_up.rect_h = MIN_WIN_BLOCK_HEIGHT;
	}

	DPU_FULL_RECT(&decon->win_up.prev_up_region, lcd);

	decon->win_up.hori_cnt = decon->lcd_info->xres / decon->win_up.rect_w;
	if (decon->lcd_info->xres - decon->win_up.hori_cnt * decon->win_up.rect_w) {
		decon_warn("%s: parameters is wrong. lcd w(%d), win rect w(%d)\n",
				__func__, decon->lcd_info->xres,
				decon->win_up.rect_w);
		return;
	}

	decon->win_up.verti_cnt = decon->lcd_info->yres / decon->win_up.rect_h;
	if (decon->lcd_info->yres - decon->win_up.verti_cnt * decon->win_up.rect_h) {
		decon_warn("%s: parameters is wrong. lcd h(%d), win rect h(%d)\n",
				__func__, decon->lcd_info->yres,
				decon->win_up.rect_h);
		return;
	}

	decon_info("window update is enabled: win rectangle w(%d), h(%d)\n",
			decon->win_up.rect_w, decon->win_up.rect_h);
	decon_info("horizontal count(%d), vertical count(%d)\n",
			decon->win_up.hori_cnt, decon->win_up.verti_cnt);

	decon->win_up.enabled = true;

	decon->mres_enabled = false;
	if (!IS_ENABLED(CONFIG_EXYNOS_MULTIRESOLUTION)) {
		decon_info("multi-resolution feature is disabled\n");
		return;
	}
	/* TODO: will be printed supported resolution list */
	decon_info("multi-resolution feature is enabled\n");
	decon->mres_enabled = true;
}
