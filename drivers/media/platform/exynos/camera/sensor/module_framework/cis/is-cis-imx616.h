/*
 * Samsung Exynos5 SoC series Sensor driver
 *
 *
 * Copyright (c) 2018 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef IS_CIS_IMX616_H
#define IS_CIS_IMX616_H

#include "is-cis.h"
#define DEBUG	/* Don't forget to turn me off later */

#define EXT_CLK_Mhz (26)

#define SENSOR_IMX616_MAX_WIDTH          (6528 + 0)
#define SENSOR_IMX616_MAX_HEIGHT         (4896 + 0)

#define USE_GROUP_PARAM_HOLD                      (1)
#define TOTAL_NUM_OF_IVTPX_CHANNEL                (4)

/* INTEGRATION TIME Value:
 * INE_INTEG_TIME is a fixed value (0x0200: 16bit - read value is 0x134c)
 */
#define SENSOR_IMX616_FINE_INTEG_TIME_VALUE			(4940)
#define SENSOR_IMX616_COARSE_INTEG_TIME_MIN_VALUE		(16)
#define SENSOR_IMX616_COARSE_INTEG_TIME_MAX_MARGIN_VALUE	(48)

/* For short name
 * : difficult to comply with kernel coding rule because of too long name
 */
#define REG(name)	SENSOR_IMX616_##name##_ADDR
#define VAL(name)	SENSOR_IMX616_##name##_VALUE

/* Register Address
 * : address name format: SENSOR_IMX616_XX...XX_ADDR
 */
#define SENSOR_IMX616_OTP_PAGE_SETUP_ADDR		(0x0A02)
#define SENSOR_IMX616_OTP_READ_TRANSFER_MODE_ADDR	(0x0A00)
#define SENSOR_IMX616_OTP_STATUS_REGISTER_ADDR		(0x0A01)
#define SENSOR_IMX616_OTP_CHIP_REVISION_ADDR		(0x0018)

#define SENSOR_IMX616_FRAME_LENGTH_LINE_ADDR		(0x0340)
#define SENSOR_IMX616_LINE_LENGTH_PCK_ADDR		(0x0342)
#define SENSOR_IMX616_FINE_INTEG_TIME_ADDR		(0x0200)
#define SENSOR_IMX616_COARSE_INTEG_TIME_ADDR		(0x0202)
#define SENSOR_IMX616_AGAIN_ADDR			(0x0204)
#define SENSOR_IMX616_DGAIN_ADDR			(0x020E)

#define SENSOR_IMX616_ABS_GAIN_GR_SET_ADDR		(0x0B8E)
#define SENSOR_IMX616_ABS_GAIN_R_SET_ADDR		(0x0B90)
#define SENSOR_IMX616_ABS_GAIN_B_SET_ADDR		(0x0B92)
#define SENSOR_IMX616_ABS_GAIN_GB_SET_ADDR		(0x0B94)

/* Extra register for 3hdr */
#define SENSOR_IMX616_MID_COARSE_INTEG_TIME_ADDR	(0x3FE0)
#define SENSOR_IMX616_ST_COARSE_INTEG_TIME_ADDR		(0x0224)
#define SENSOR_IMX616_MID_DGAIN_ADDR			(0x3FE4)
#define SENSOR_IMX616_ST_DGAIN_ADDR			(0x0218)

/* Constant Value
 * : value name format: SENSOR_IMX616_XX...XX_VALUE
 */
/* Register Value */
#define SENSOR_IMX616_MIN_AGAIN_VALUE			(112)
#define SENSOR_IMX616_MAX_AGAIN_VALUE			(1008)
#define SENSOR_IMX616_MIN_DGAIN_VALUE			(0x0100)
#define SENSOR_IMX616_MAX_DGAIN_VALUE			(0x0FFF)

/* Extra Value for 3hdr */
#define SENSOR_IMX616_QBCHDR_MIN_AGAIN_VALUE		(0)
#define SENSOR_IMX616_QBCHDR_MAX_AGAIN_VALUE		(448)
#define SENSOR_IMX616_QBCHDR_MIN_DGAIN_VALUE		(0x0100)
#define SENSOR_IMX616_QBCHDR_MAX_DGAIN_VALUE		(0x0FFF)

/* Related EEPROM CAL */
#define SENSOR_IMX616_QUAD_SENS_CAL_BASE_FRONT		(0x1700)
#define SENSOR_IMX616_QUAD_SENS_CAL_SIZE		(1560)
#define SENSOR_IMX616_QUAD_SENS_REG_ADDR		(0xC500)

#define SENSOR_IMX616_QSC_DUMP_NAME               "/data/vendor/camera/IMX616_QSC_DUMP.bin"

/* Related Function Option */
#define SENSOR_IMX616_SENSOR_CAL_FOR_REMOSAIC		(1)
#define SENSOR_IMX616_CAL_DEBUG				(0)
#define SENSOR_IMX616_DEBUG_INFO			(0)


 /*
  * [Mode Information]
  *
  * Reference File : IMX616-AAJH5_SAM-DPHY_26MHz_RegisterSetting_ver6.00-8.20_b2_190610.xlsx
  *
  * -. Global Setting -
  *
  * -. 2x2 BIN For Single Still Preview / Capture -
  *    [ 0 ] REG_H : 2x2 Binning 3264x2448 30fps	: Single Still Preview (4:3)	,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *    [ 1 ] REG_I : 2x2 Binning 3264x1836 30fps	: Single Still Preview (16:9)	 ,	MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *    [ 2 ] REG_J : 2x2 Binning 3264x1504 30fps	: Single Still Preview (19.5:9)    ,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *    [ 3 ] REG_N : 2x2 Binning 2448x2448 30fps	: Single Still Preview (1:1)	,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *
  * -. 68¨¬2x2 BIN For Single Still Preview / Capture -
  *    [ 4 ] REG_K : 2x2 Binning 2640x1980 30fps	: Single Still Preview (4:3)	,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *    [ 5 ] REG_L : 2x2 Binning 2640x1448 30fps	: Single Still Preview (16:9)	,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *    [ 6 ] REG_M : 2x2 Binning 2640x1216 30fps	: Single Still Preview (19.5:9)    ,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *    [ 7 ] REG_O : 2x2 Binning 1984x1984 30fps	: Single Still Preview (1:1)	,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *
  * -. 2x2 BIN H2V2 For FastAE
  *    [ 8 ] REG_R : 2x2 Binning 1632x1224 120fps	  : FAST AE (4:3)	 ,	MIPI lane: 4, MIPI data rate(Mbps/lane): 2054
  *
  * -. FULL Remosaic For Single Still Remosaic Capture -
  *    [ 9 ] REG_F	: Full Remosaic 6528x4896 24fps 	  : Single Still Remosaic Capture (4:3) , MIPI lane: 4, MIPI data rate(Mbps/lane): 2218
  *
  * -. 68¨¬FULL Remosaic For Single Still Remosaic Capture -
  *    [ 10 ] REG_G	: Full Remosaic 5264x3948 24fps 	  : Single Still Remosaic Capture (4:3) , MIPI lane: 4, MIPI data rate(Mbps/lane): 2218
  *
  * -. QBC HDR
  *    [ 11 ] REG_S : QBC HDR 3264x2448 24fps		: Single Still Preview (4:3)	,  MIPI lane: 4, MIPI data rate(Mbps/lane): 2218
  */


enum sensor_imx616_mode_enum {
	IMX616_MODE_2X2BIN_3264x2448_30FPS = 0,		/* 0 */
	IMX616_MODE_2X2BIN_3264x1836_30FPS,
	IMX616_MODE_2X2BIN_3264x1504_30FPS,
	IMX616_MODE_2X2BIN_2448x2448_30FPS,
	IMX616_MODE_2X2BIN_2640x1980_30FPS,
	IMX616_MODE_2X2BIN_2640x1488_30FPS,
	IMX616_MODE_2X2BIN_2640x1216_30FPS,
	IMX616_MODE_2X2BIN_1984x1984_30FPS,
	IMX616_MODE_H2V2_1632x1224_120FPS,		/* 8 */
	/* FULL Remosaic */
	IMX616_MODE_REMOSAIC_START,
	IMX616_MODE_REMOSAIC_6528x4896_24FPS = IMX616_MODE_REMOSAIC_START,	/* 9 */
	IMX616_MODE_REMOSAIC_5264x3948_24FPS ,
	IMX616_MODE_REMOSAIC_END = IMX616_MODE_REMOSAIC_5264x3948_24FPS,
	/* QBC 3HDR */
	IMX616_MODE_QBCHDR_START ,
	IMX616_MODE_QBCHDR_3264x2448_24FPS = IMX616_MODE_QBCHDR_START,	/* 11 */
	IMX616_MODE_QBCHDR_END = IMX616_MODE_QBCHDR_3264x2448_24FPS,
	IMX616_MODE_END
};

/* IS_REMOSAIC(u32 mode): check if mode is remosaic */
#define IS_REMOSAIC(mode) ({						\
	typecheck(u32, mode) && (m >= IMX616_MODE_REMOSAIC_START) &&	\
	(m <= IMX616_MODE_REMOSAIC_END);				\
})

/* IS_REMOSAIC_MODE(struct is_cis *cis) */
#define IS_REMOSAIC_MODE(cis) ({					\
	u32 m;								\
	typecheck(struct is_cis *, cis);				\
	m = cis->cis_data->sens_config_index_cur;			\
	(m >= IMX616_MODE_REMOSAIC_START) && (m <= IMX616_MODE_REMOSAIC_END); \
})

/* IS_3DHDR(struct is_cis *cis, u32 mode): check if mode is 3dhdr */
#define IS_3DHDR(cis, mode) ({						\
	typecheck(u32, mode);						\
	typecheck(struct is_cis *, cis);				\
	(cis->use_3hdr) && (mode >= IMX616_MODE_QBCHDR_START) &&	\
	(mode <= IMX616_MODE_QBCHDR_END);				\
})

/* IS_3DHDR_MODE(struct is_cis *cis) */
#define IS_3DHDR_MODE(cis) ({						\
	u32 m;								\
	typecheck(struct is_cis *, cis);				\
	m = cis->cis_data->sens_config_index_cur;			\
	(cis->use_3hdr) && (m >= IMX616_MODE_QBCHDR_START) &&		\
	(m <= IMX616_MODE_QBCHDR_END);					\
})

#ifdef DEBUG
#define ASSERT(x, format...)						\
	do {								\
		if (!(x)) {						\
			err("[ASSERT FAILURE] "format);			\
			BUG();						\
		}							\
	} while (0)
#else
#define ASSERT(x, format...) do { } while (0)
#endif

#define CHECK_GOTO(conditon, label)		\
	do {					\
		if (unlikely(conditon))		\
			goto label;		\
	} while (0)

#define CHECK_RET(conditon, ret)		\
	do {					\
		if (unlikely(conditon))		\
			return ret;		\
	} while (0)

#define CHECK_ERR_GOTO(conditon, label, fmt, args...)	\
	do {						\
		if (unlikely(conditon)) {		\
			err(fmt, ##args);		\
			goto label;			\
		}					\
	} while (0)

#define CHECK_ERR_RET(conditon, ret,  fmt, args...)	\
	do {						\
		if (unlikely(conditon)) {		\
			err(fmt, ##args);		\
			return ret;			\
		}					\
	} while (0)


#endif

