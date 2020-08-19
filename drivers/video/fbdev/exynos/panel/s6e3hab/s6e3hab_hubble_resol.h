/*
 * linux/drivers/video/fbdev/exynos/panel/s6e3hab/s6e3hab_hubble_resol.h
 *
 * Header file for Panel Driver
 *
 * Copyright (c) 2019 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __S6E3HAB_HUBBLE_RESOL_H__
#define __S6E3HAB_HUBBLE_RESOL_H__

#include "../panel.h"
#include "s6e3hab.h"
#include "s6e3hab_dimming.h"

#ifdef CONFIG_PANEL_VRR_BRIDGE
#define S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE (11)
#define S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE (S6E3HAB_HUBBLE_TARGET_LUMINANCE)
#define S6E3HAB_HUBBLE_BRR_MIN_LUMINANCE (98)
#define S6E3HAB_HUBBLE_BRR_MAX_LUMINANCE (S6E3HAB_HUBBLE_TARGET_LUMINANCE)
#define S6E3HAB_HUBBLE_REV03_BRR_MIN_LUMINANCE (98)
#define S6E3HAB_HUBBLE_REV03_BRR_MAX_LUMINANCE (S6E3HAB_HUBBLE_TARGET_LUMINANCE)

struct vrr_bridge_step s6e3hab_hubble_vrr_60_to_48_bridge_step[] = {
	{ .fps = 52, .frame_delay = 4, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 48, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_48_to_60_bridge_step[] = {
	{ .fps = 52, .frame_delay = 4, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 60, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_120_to_96_bridge_step[] = {
	{ .fps = 112, .frame_delay = 4, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 104, .frame_delay = 4, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 96, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_96_to_120_bridge_step[] = {
	{ .fps = 104, .frame_delay = 4, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 112, .frame_delay = 4, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 120, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_120_to_60_bridge_step[] = {
	{ .fps = 110, .frame_delay = 8, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 100, .frame_delay = 8, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 70, .frame_delay = 8, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 60, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_60_to_120_bridge_step[] = {
	{ .fps = 70, .frame_delay = 5, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 100, .frame_delay = 5, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 110, .frame_delay = 5, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
	{ .fps = 120, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_120_to_60_bridge_step[] = {
	{ .fps = 120, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 110, .frame_delay = 8, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 100, .frame_delay = 8, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 70, .frame_delay = 8, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 60, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_60_to_120_bridge_step[] = {
	{ .fps = 70, .frame_delay = 5, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 100, .frame_delay = 5, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 110, .frame_delay = 5, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 120, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_4_CYCLE, },
	{ .fps = 120, .frame_delay = 1, .aid_cycle = S6E3HAB_AID_2_CYCLE, },
};

static struct panel_vrr_bridge s6e3hab_hubble_wqhd_bridge_rr[] = {
	{
		.origin_fps = 60,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 48,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_60_to_48_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_60_to_48_bridge_step),
	}, {
		.origin_fps = 48,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 60,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_48_to_60_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_48_to_60_bridge_step),
	}
};

static struct panel_vrr_bridge s6e3hab_hubble_preliminary_bridge_rr[] = {
	{
		.origin_fps = 60,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 48,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_60_to_48_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_60_to_48_bridge_step),
	}, {
		.origin_fps = 48,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 60,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_48_to_60_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_48_to_60_bridge_step),
	}
};

static struct panel_vrr_bridge s6e3hab_hubble_default_bridge_rr[] = {
	{
		.origin_fps = 120,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 60,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_BRR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_BRR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_120_to_60_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_120_to_60_bridge_step),
	}, {
		.origin_fps = 60,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 120,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_BRR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_BRR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_60_to_120_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_60_to_120_bridge_step),
	}, {
		.origin_fps = 120,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 96,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_120_to_96_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_120_to_96_bridge_step),
	}, {
		.origin_fps = 96,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 120,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_96_to_120_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_96_to_120_bridge_step),
	}, {
		.origin_fps = 60,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 48,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_60_to_48_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_60_to_48_bridge_step),
	}, {
		.origin_fps = 48,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 60,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_48_to_60_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_48_to_60_bridge_step),
	}
};

static struct panel_vrr_bridge s6e3hab_hubble_rev03_default_bridge_rr[] = {
	{
		.origin_fps = 120,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 60,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_REV03_BRR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_REV03_BRR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_rev03_vrr_120_to_60_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_rev03_vrr_120_to_60_bridge_step),
	}, {
		.origin_fps = 60,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 120,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_REV03_BRR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_REV03_BRR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_rev03_vrr_60_to_120_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_rev03_vrr_60_to_120_bridge_step),
	}, {
		.origin_fps = 120,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 96,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_120_to_96_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_120_to_96_bridge_step),
	}, {
		.origin_fps = 96,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 120,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_96_to_120_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_96_to_120_bridge_step),
	}, {
		.origin_fps = 60,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 48,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_60_to_48_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_60_to_48_bridge_step),
	}, {
		.origin_fps = 48,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 60,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_vrr_48_to_60_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_vrr_48_to_60_bridge_step),
	}
};
#endif

static struct panel_vrr *s6e3hab_hubble_wqhd_vrrtbl[] = {
	&S6E3HAB_VRR[S6E3HAB_VRR_60_NORMAL],
};

static struct panel_vrr *s6e3hab_hubble_preliminary_vrrtbl[] = {
	&S6E3HAB_VRR[S6E3HAB_VRR_60_NORMAL],
};

static struct panel_vrr *s6e3hab_hubble_default_vrrtbl[] = {
	&S6E3HAB_VRR[S6E3HAB_VRR_60_NORMAL],
	&S6E3HAB_VRR[S6E3HAB_VRR_60_HS],
	&S6E3HAB_VRR[S6E3HAB_VRR_120_HS],
};

static struct panel_resol s6e3hab_hubble_preliminary_resol[] = {
	{
		.w = 1440,
		.h = 3200,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 720,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_wqhd_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_wqhd_vrrtbl),
	},
	{
		.w = 1080,
		.h = 2400,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 540,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_preliminary_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_preliminary_vrrtbl),
	},
	{
		.w = 720,
		.h = 1600,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 360,
				.slice_h = 80,
			},
		},
		.available_vrr = s6e3hab_hubble_preliminary_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_preliminary_vrrtbl),
	},
};

static struct panel_resol s6e3hab_hubble_default_resol[] = {
	{
		.w = 1440,
		.h = 3200,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 720,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_wqhd_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_wqhd_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_wqhd_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_wqhd_bridge_rr),
#endif
	},
	{
		.w = 1080,
		.h = 2400,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 540,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_default_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_default_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_default_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_default_bridge_rr),
#endif
	},
	{
		.w = 720,
		.h = 1600,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 360,
				.slice_h = 80,
			},
		},
		.available_vrr = s6e3hab_hubble_default_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_default_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_default_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_default_bridge_rr),
#endif
	},
};

static struct panel_resol s6e3hab_hubble_default_rev03_resol[] = {
	{
		.w = 1440,
		.h = 3200,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 720,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_wqhd_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_wqhd_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_wqhd_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_wqhd_bridge_rr),
#endif
	},
	{
		.w = 1080,
		.h = 2400,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 540,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_default_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_default_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_rev03_default_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_rev03_default_bridge_rr),
#endif
	},
	{
		.w = 720,
		.h = 1600,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 360,
				.slice_h = 80,
			},
		},
		.available_vrr = s6e3hab_hubble_default_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_default_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_rev03_default_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_rev03_default_bridge_rr),
#endif
	},
};
#endif /* __S6E3HAB_HUBBLE_RESOL_H__ */
