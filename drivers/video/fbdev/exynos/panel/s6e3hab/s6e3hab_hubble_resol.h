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

#include <dt-bindings/display/panel-display.h>
#include "../panel.h"
#include "s6e3hab.h"
#include "s6e3hab_dimming.h"

struct panel_vrr s6e3hab_hubble_preliminary_panel_vrr[] = {
	[S6E3HAB_VRR_60NS] = {
		.fps = 60,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_52NS] = {
		.fps = 52,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_48NS] = {
		.fps = 48,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
};

struct panel_vrr s6e3hab_hubble_default_panel_vrr[] = {
	[S6E3HAB_VRR_60NS] = {
		.fps = 60,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_52NS] = {
		.fps = 52,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_48NS] = {
		.fps = 48,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_120HS] = {
		.fps = 120,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_120HS_AID_4_CYCLE] = {
		.fps = 120,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_112HS] = {
		.fps = 112,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_110HS] = {
		.fps = 110,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_104HS] = {
		.fps = 104,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_100HS] = {
		.fps = 100,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_96HS] = {
		.fps = 96,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_70HS] = {
		.fps = 70,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_60HS] = {
		.fps = 60,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
};

struct panel_vrr s6e3hab_hubble_rev03_panel_vrr[] = {
	[S6E3HAB_VRR_60NS] = {
		.fps = 60,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_52NS] = {
		.fps = 52,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_48NS] = {
		.fps = 48,
		.base_fps = 60,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_NORMAL_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_120HS] = {
		.fps = 120,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_120HS_AID_4_CYCLE] = {
		.fps = 120,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_112HS] = {
		.fps = 112,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_110HS] = {
		.fps = 110,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_104HS] = {
		.fps = 104,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_100HS] = {
		.fps = 100,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_96HS] = {
		.fps = 96,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
	[S6E3HAB_VRR_70HS] = {
		.fps = 70,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_4_CYCLE,
	},
	[S6E3HAB_VRR_60HS] = {
		.fps = 60,
		.base_fps = 120,
		.base_vactive = 3200,
		.base_vfp = 16,
		.base_vbp = 16,
		.te_sel = true,
		.te_v_st = 3201,
		.te_v_ed = 9,
		.mode = VRR_HS_MODE,
		.aid_cycle = VRR_AID_2_CYCLE,
	},
};

static struct panel_vrr *s6e3hab_hubble_preliminary_vrrtbl[] = {
	&s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_60NS],
	&s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_52NS],
	&s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_48NS],
};

static struct panel_vrr *s6e3hab_hubble_wqhd_vrrtbl[] = {
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60NS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_52NS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_48NS],
};

static struct panel_vrr *s6e3hab_hubble_default_vrrtbl[] = {
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60NS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_52NS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_48NS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS_AID_4_CYCLE],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_112HS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_110HS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_104HS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_100HS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_96HS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_70HS],
	&s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60HS],
};

static struct panel_vrr *s6e3hab_hubble_rev03_wqhd_vrrtbl[] = {
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60NS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_52NS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_48NS],
};

static struct panel_vrr *s6e3hab_hubble_rev03_vrrtbl[] = {
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60NS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_52NS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_48NS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS_AID_4_CYCLE],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_112HS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_110HS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_104HS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_100HS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_96HS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_70HS],
	&s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60HS],
};

#ifdef CONFIG_PANEL_VRR_BRIDGE
#define S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE (11)
#define S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE (S6E3HAB_HUBBLE_TARGET_LUMINANCE)
#define S6E3HAB_HUBBLE_BRR_MIN_LUMINANCE (98)
#define S6E3HAB_HUBBLE_BRR_MAX_LUMINANCE (S6E3HAB_HUBBLE_TARGET_LUMINANCE)
#define S6E3HAB_HUBBLE_REV03_BRR_MIN_LUMINANCE (98)
#define S6E3HAB_HUBBLE_REV03_BRR_MAX_LUMINANCE (S6E3HAB_HUBBLE_TARGET_LUMINANCE)

struct vrr_bridge_step s6e3hab_hubble_vrr_60_to_48_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60NS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_52NS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_48NS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_48_to_60_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_48NS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_52NS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60NS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_120_to_96_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_112HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_104HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_96HS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_96_to_120_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_96HS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_104HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_112HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_120_to_60_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_110HS], .frame_delay = 8, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_100HS], .frame_delay = 8, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_70HS], .frame_delay = 8, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60HS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_vrr_60_to_120_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60HS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_70HS], .frame_delay = 5, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_100HS], .frame_delay = 5, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_110HS], .frame_delay = 5, },
	{ .vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_60_to_48_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60NS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_52NS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_48NS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_48_to_60_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_48NS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_52NS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60NS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_120_to_96_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_112HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_104HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_96HS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_96_to_120_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_96HS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_104HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_112HS], .frame_delay = 4, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_120_to_60_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 0, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS_AID_4_CYCLE], .frame_delay = 1, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_110HS], .frame_delay = 8, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_100HS], .frame_delay = 8, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_70HS], .frame_delay = 8, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60HS], .frame_delay = 1, },
};

struct vrr_bridge_step s6e3hab_hubble_rev03_vrr_60_to_120_bridge_step[] = {
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60HS], .frame_delay = 5, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_70HS], .frame_delay = 5, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_100HS], .frame_delay = 5, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_110HS], .frame_delay = 5, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS_AID_4_CYCLE], .frame_delay = 1, },
	{ .vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS], .frame_delay = 1, },
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
		.step = s6e3hab_hubble_rev03_vrr_120_to_96_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_rev03_vrr_120_to_96_bridge_step),
	}, {
		.origin_fps = 96,
		.origin_mode = VRR_HS_MODE,
		.origin_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.target_fps = 120,
		.target_mode = VRR_HS_MODE,
		.target_aid_cycle = S6E3HAB_AID_2_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_rev03_vrr_96_to_120_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_rev03_vrr_96_to_120_bridge_step),
	}, {
		.origin_fps = 60,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 48,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_rev03_vrr_60_to_48_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_rev03_vrr_60_to_48_bridge_step),
	}, {
		.origin_fps = 48,
		.origin_mode = VRR_NORMAL_MODE,
		.origin_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.target_fps = 60,
		.target_mode = VRR_NORMAL_MODE,
		.target_aid_cycle = S6E3HAB_AID_4_CYCLE,
		.min_actual_brt = S6E3HAB_HUBBLE_ARR_MIN_LUMINANCE,
		.max_actual_brt = S6E3HAB_HUBBLE_ARR_MAX_LUMINANCE,
		.step = s6e3hab_hubble_rev03_vrr_48_to_60_bridge_step,
		.nr_step = ARRAY_SIZE(s6e3hab_hubble_rev03_vrr_48_to_60_bridge_step),
	}
};
#endif /* CONFIG_PANEL_VRR_BRIDGE */

static struct panel_resol s6e3hab_hubble_preliminary_resol[] = {
	[S6E3HAB_RESOL_1440x3200] = {
		.w = 1440,
		.h = 3200,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 720,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_preliminary_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_preliminary_vrrtbl),
	},
	[S6E3HAB_RESOL_1080x2400] = {
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
	[S6E3HAB_RESOL_720x1600] = {
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
	[S6E3HAB_RESOL_1440x3200] = {
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
	[S6E3HAB_RESOL_1080x2400] = {
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
	[S6E3HAB_RESOL_720x1600] = {
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

static struct panel_resol s6e3hab_hubble_rev03_resol[] = {
	[S6E3HAB_RESOL_1440x3200] = {
		.w = 1440,
		.h = 3200,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 720,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_rev03_wqhd_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_rev03_wqhd_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_wqhd_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_wqhd_bridge_rr),
#endif
	},
	[S6E3HAB_RESOL_1080x2400] = {
		.w = 1080,
		.h = 2400,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 540,
				.slice_h = 40,
			},
		},
		.available_vrr = s6e3hab_hubble_rev03_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_rev03_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_rev03_default_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_rev03_default_bridge_rr),
#endif
	},
	[S6E3HAB_RESOL_720x1600] = {
		.w = 720,
		.h = 1600,
		.comp_type = PN_COMP_TYPE_DSC,
		.comp_param = {
			.dsc = {
				.slice_w = 360,
				.slice_h = 80,
			},
		},
		.available_vrr = s6e3hab_hubble_rev03_vrrtbl,
		.nr_available_vrr = ARRAY_SIZE(s6e3hab_hubble_rev03_vrrtbl),
#ifdef CONFIG_PANEL_VRR_BRIDGE
		.bridge_rr = s6e3hab_hubble_rev03_default_bridge_rr,
		.nr_bridge_rr = ARRAY_SIZE(s6e3hab_hubble_rev03_default_bridge_rr),
#endif
	},
};

#if defined(CONFIG_PANEL_DISPLAY_MODE)
static struct common_panel_display_mode s6e3hab_hubble_preliminary_display_mode[MAX_S6E3HAB_DISPLAY_MODE] = {
	/* WQHD */
	[S6E3HAB_DISPLAY_MODE_1440x3200_60NS] = {
		.name = PANEL_DISPLAY_MODE_1440x3200_60NS,
		.resol = &s6e3hab_hubble_preliminary_resol[S6E3HAB_RESOL_1440x3200],
		.vrr = &s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_1440x3200_48NS] = {
		.name = PANEL_DISPLAY_MODE_1440x3200_48NS,
		.resol = &s6e3hab_hubble_preliminary_resol[S6E3HAB_RESOL_1440x3200],
		.vrr = &s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_48NS],
	},

	/* FHD */
	[S6E3HAB_DISPLAY_MODE_1080x2400_60NS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_60NS,
		.resol = &s6e3hab_hubble_preliminary_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_48NS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_48NS,
		.resol = &s6e3hab_hubble_preliminary_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_48NS],
	},

	/* HD */
	[S6E3HAB_DISPLAY_MODE_720x1600_60NS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_60NS,
		.resol = &s6e3hab_hubble_preliminary_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_48NS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_48NS,
		.resol = &s6e3hab_hubble_preliminary_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_preliminary_panel_vrr[S6E3HAB_VRR_48NS],
	},
};

static struct common_panel_display_mode s6e3hab_hubble_display_mode[MAX_S6E3HAB_DISPLAY_MODE] = {
	/* WQHD */
	[S6E3HAB_DISPLAY_MODE_1440x3200_60NS] = {
		.name = PANEL_DISPLAY_MODE_1440x3200_60NS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_1440x3200],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_1440x3200_48NS] = {
		.name = PANEL_DISPLAY_MODE_1440x3200_48NS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_1440x3200],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_48NS],
	},

	/* FHD */
	[S6E3HAB_DISPLAY_MODE_1080x2400_120HS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_120HS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_96HS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_96HS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_96HS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_60HS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_60HS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60HS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_60NS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_60NS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_48NS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_48NS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_48NS],
	},

	/* HD */
	[S6E3HAB_DISPLAY_MODE_720x1600_120HS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_120HS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_120HS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_96HS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_96HS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_96HS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_60HS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_60HS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60HS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_60NS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_60NS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_48NS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_48NS,
		.resol = &s6e3hab_hubble_default_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_default_panel_vrr[S6E3HAB_VRR_48NS],
	},
};

static struct common_panel_display_mode s6e3hab_hubble_rev03_display_mode[MAX_S6E3HAB_DISPLAY_MODE] = {
	/* WQHD */
	[S6E3HAB_DISPLAY_MODE_1440x3200_60NS] = {
		.name = PANEL_DISPLAY_MODE_1440x3200_60NS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_1440x3200],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_1440x3200_48NS] = {
		.name = PANEL_DISPLAY_MODE_1440x3200_48NS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_1440x3200],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_48NS],
	},

	/* FHD */
	[S6E3HAB_DISPLAY_MODE_1080x2400_120HS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_120HS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_96HS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_96HS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_96HS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_60HS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_60HS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60HS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_60NS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_60NS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_1080x2400_48NS] = {
		.name = PANEL_DISPLAY_MODE_1080x2400_48NS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_1080x2400],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_48NS],
	},

	/* HD */
	[S6E3HAB_DISPLAY_MODE_720x1600_120HS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_120HS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_120HS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_96HS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_96HS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_96HS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_60HS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_60HS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60HS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_60NS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_60NS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_60NS],
	},
	[S6E3HAB_DISPLAY_MODE_720x1600_48NS] = {
		.name = PANEL_DISPLAY_MODE_720x1600_48NS,
		.resol = &s6e3hab_hubble_rev03_resol[S6E3HAB_RESOL_720x1600],
		.vrr = &s6e3hab_hubble_rev03_panel_vrr[S6E3HAB_VRR_48NS],
	},
};

static struct common_panel_display_mode *s6e3hab_hubble_preliminary_display_mode_array[MAX_S6E3HAB_DISPLAY_MODE] = {
	[S6E3HAB_DISPLAY_MODE_1440x3200_60NS] = &s6e3hab_hubble_preliminary_display_mode[S6E3HAB_DISPLAY_MODE_1440x3200_60NS],
	[S6E3HAB_DISPLAY_MODE_1440x3200_48NS] = &s6e3hab_hubble_preliminary_display_mode[S6E3HAB_DISPLAY_MODE_1440x3200_48NS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_60NS] = &s6e3hab_hubble_preliminary_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_60NS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_48NS] = &s6e3hab_hubble_preliminary_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_48NS],
	[S6E3HAB_DISPLAY_MODE_720x1600_60NS] = &s6e3hab_hubble_preliminary_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_60NS],
	[S6E3HAB_DISPLAY_MODE_720x1600_48NS] = &s6e3hab_hubble_preliminary_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_48NS],
};

static struct common_panel_display_mode *s6e3hab_hubble_display_mode_array[MAX_S6E3HAB_DISPLAY_MODE] = {
	[S6E3HAB_DISPLAY_MODE_1440x3200_60NS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_1440x3200_60NS],
	[S6E3HAB_DISPLAY_MODE_1440x3200_48NS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_1440x3200_48NS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_120HS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_120HS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_96HS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_96HS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_60HS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_60HS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_60NS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_60NS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_48NS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_48NS],
	[S6E3HAB_DISPLAY_MODE_720x1600_120HS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_120HS],
	[S6E3HAB_DISPLAY_MODE_720x1600_96HS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_96HS],
	[S6E3HAB_DISPLAY_MODE_720x1600_60HS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_60HS],
	[S6E3HAB_DISPLAY_MODE_720x1600_60NS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_60NS],
	[S6E3HAB_DISPLAY_MODE_720x1600_48NS] = &s6e3hab_hubble_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_48NS],
};

static struct common_panel_display_mode *s6e3hab_hubble_rev03_display_mode_array[MAX_S6E3HAB_DISPLAY_MODE] = {
	[S6E3HAB_DISPLAY_MODE_1440x3200_60NS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_1440x3200_60NS],
	[S6E3HAB_DISPLAY_MODE_1440x3200_48NS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_1440x3200_48NS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_120HS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_120HS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_96HS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_96HS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_60HS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_60HS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_60NS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_60NS],
	[S6E3HAB_DISPLAY_MODE_1080x2400_48NS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_1080x2400_48NS],
	[S6E3HAB_DISPLAY_MODE_720x1600_120HS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_120HS],
	[S6E3HAB_DISPLAY_MODE_720x1600_96HS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_96HS],
	[S6E3HAB_DISPLAY_MODE_720x1600_60HS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_60HS],
	[S6E3HAB_DISPLAY_MODE_720x1600_60NS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_60NS],
	[S6E3HAB_DISPLAY_MODE_720x1600_48NS] = &s6e3hab_hubble_rev03_display_mode[S6E3HAB_DISPLAY_MODE_720x1600_48NS],
};

static struct common_panel_display_modes s6e3hab_hubble_preliminary_display_modes = {
	.num_modes = ARRAY_SIZE(s6e3hab_hubble_preliminary_display_mode),
	.modes = (struct common_panel_display_mode **)&s6e3hab_hubble_preliminary_display_mode_array,
};

static struct common_panel_display_modes s6e3hab_hubble_display_modes = {
	.num_modes = ARRAY_SIZE(s6e3hab_hubble_display_mode),
	.modes = (struct common_panel_display_mode **)&s6e3hab_hubble_display_mode_array,
};

static struct common_panel_display_modes s6e3hab_hubble_rev03_display_modes = {
	.num_modes = ARRAY_SIZE(s6e3hab_hubble_rev03_display_mode),
	.modes = (struct common_panel_display_mode **)&s6e3hab_hubble_rev03_display_mode_array,
};
#endif /* CONFIG_PANEL_DISPLAY_MODE */
#endif /* __S6E3HAB_HUBBLE_RESOL_H__ */
