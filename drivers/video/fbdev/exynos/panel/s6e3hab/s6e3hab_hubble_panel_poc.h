/*
 * linux/drivers/video/fbdev/exynos/panel/s6e3hab/s6e3hab_hubble_panel_poc.h
 *
 * Header file for POC Driver
 *
 * Copyright (c) 2016 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __S6E3HAB_HUBBLE_PANEL_POC_H__
#define __S6E3HAB_HUBBLE_PANEL_POC_H__

#include "../panel.h"
#include "../panel_poc.h"

#define HUBBLE_BDIV	(BIT_RATE_DIV_32)
#define HUBBLE_EXEC_USEC	(2)
#define HUBBLE_QD_DONE_MDELAY		(30)
#define HUBBLE_RD_DONE_UDELAY		(70)
#define HUBBLE_WR_ENABLE_01_UDELAY		(20)
#define HUBBLE_WR_ENABLE_02_MDELAY		(10)
#define HUBBLE_WR_EXEC_UDELAY		(400)
#define HUBBLE_WR_DONE_MDELAY		(1)
#ifdef CONFIG_SUPPORT_POC_FLASH
#define HUBBLE_ER_4K_DONE_MDELAY		(400)
#define HUBBLE_ER_32K_DONE_MDELAY		(800)
#define HUBBLE_ER_64K_DONE_MDELAY		(1000)
#endif

#define HUBBLE_POC_IMG_ADDR	(0x8F000)
#define HUBBLE_POC_IMG_SIZE	(115719)

#ifdef CONFIG_SUPPORT_DIM_FLASH
#define HUBBLE_POC_DIM_DATA_ADDR	(0xF0000)
#define HUBBLE_POC_DIM_DATA_SIZE (S6E3HAB_DIM_FLASH_DATA_SIZE)
#define HUBBLE_POC_DIM_CHECKSUM_ADDR	(HUBBLE_POC_DIM_DATA_ADDR + S6E3HAB_DIM_FLASH_CHECKSUM_OFS)
#define HUBBLE_POC_DIM_CHECKSUM_SIZE (S6E3HAB_DIM_FLASH_CHECKSUM_LEN)
#define HUBBLE_POC_DIM_MAGICNUM_ADDR	(HUBBLE_POC_DIM_DATA_ADDR + S6E3HAB_DIM_FLASH_MAGICNUM_OFS)
#define HUBBLE_POC_DIM_MAGICNUM_SIZE (S6E3HAB_DIM_FLASH_MAGICNUM_LEN)
#define HUBBLE_POC_DIM_TOTAL_SIZE (S6E3HAB_DIM_FLASH_TOTAL_SIZE)

#define HUBBLE_POC_MTP_DATA_ADDR	(0xF2800)
#define HUBBLE_POC_MTP_DATA_SIZE (S6E3HAB_DIM_FLASH_MTP_DATA_SIZE)
#define HUBBLE_POC_MTP_CHECKSUM_ADDR	(HUBBLE_POC_MTP_DATA_ADDR + S6E3HAB_DIM_FLASH_MTP_CHECKSUM_OFS)
#define HUBBLE_POC_MTP_CHECKSUM_SIZE (S6E3HAB_DIM_FLASH_MTP_CHECKSUM_LEN)
#define HUBBLE_POC_MTP_TOTAL_SIZE (S6E3HAB_DIM_FLASH_MTP_TOTAL_SIZE)

#define HUBBLE_POC_DIM_120HZ_DATA_ADDR	(0xF3000)
#define HUBBLE_POC_DIM_120HZ_DATA_SIZE (S6E3HAB_DIM_FLASH_120HZ_DATA_SIZE)
#define HUBBLE_POC_DIM_120HZ_CHECKSUM_ADDR	(HUBBLE_POC_DIM_120HZ_DATA_ADDR + S6E3HAB_DIM_FLASH_120HZ_CHECKSUM_OFS)
#define HUBBLE_POC_DIM_120HZ_CHECKSUM_SIZE (S6E3HAB_DIM_FLASH_120HZ_CHECKSUM_LEN)
#define HUBBLE_POC_DIM_120HZ_MAGICNUM_ADDR	(HUBBLE_POC_DIM_120HZ_DATA_ADDR + S6E3HAB_DIM_FLASH_120HZ_MAGICNUM_OFS)
#define HUBBLE_POC_DIM_120HZ_MAGICNUM_SIZE (S6E3HAB_DIM_FLASH_120HZ_MAGICNUM_LEN)
#define HUBBLE_POC_DIM_120HZ_TOTAL_SIZE (S6E3HAB_DIM_FLASH_120HZ_TOTAL_SIZE)

#define HUBBLE_POC_MTP_120HZ_DATA_ADDR	(0xF5800)
#define HUBBLE_POC_MTP_120HZ_DATA_SIZE (S6E3HAB_DIM_FLASH_120HZ_MTP_DATA_SIZE)
#define HUBBLE_POC_MTP_120HZ_CHECKSUM_ADDR	(HUBBLE_POC_MTP_120HZ_DATA_ADDR + S6E3HAB_DIM_FLASH_120HZ_MTP_CHECKSUM_OFS)
#define HUBBLE_POC_MTP_120HZ_CHECKSUM_SIZE (S6E3HAB_DIM_FLASH_120HZ_MTP_CHECKSUM_LEN)
#define HUBBLE_POC_MTP_120HZ_TOTAL_SIZE (S6E3HAB_DIM_FLASH_120HZ_MTP_TOTAL_SIZE)

#define HUBBLE_POC_DIM_60HZ_HS_DATA_ADDR	(0xF6000)
#define HUBBLE_POC_DIM_60HZ_HS_DATA_SIZE (S6E3HAB_DIM_FLASH_60HZ_HS_DATA_SIZE)
#define HUBBLE_POC_DIM_60HZ_HS_CHECKSUM_ADDR	(HUBBLE_POC_DIM_60HZ_HS_DATA_ADDR + S6E3HAB_DIM_FLASH_60HZ_HS_CHECKSUM_OFS)
#define HUBBLE_POC_DIM_60HZ_HS_CHECKSUM_SIZE (S6E3HAB_DIM_FLASH_60HZ_HS_CHECKSUM_LEN)
#define HUBBLE_POC_DIM_60HZ_HS_MAGICNUM_ADDR	(HUBBLE_POC_DIM_60HZ_HS_DATA_ADDR + S6E3HAB_DIM_FLASH_60HZ_HS_MAGICNUM_OFS)
#define HUBBLE_POC_DIM_60HZ_HS_MAGICNUM_SIZE (S6E3HAB_DIM_FLASH_60HZ_HS_MAGICNUM_LEN)
#define HUBBLE_POC_DIM_60HZ_HS_TOTAL_SIZE (S6E3HAB_DIM_FLASH_60HZ_HS_TOTAL_SIZE)

#define HUBBLE_POC_MTP_60HZ_HS_DATA_ADDR	(0xF8800)
#define HUBBLE_POC_MTP_60HZ_HS_DATA_SIZE (S6E3HAB_DIM_FLASH_60HZ_HS_MTP_DATA_SIZE)
#define HUBBLE_POC_MTP_60HZ_HS_CHECKSUM_ADDR	(HUBBLE_POC_MTP_60HZ_HS_DATA_ADDR + S6E3HAB_DIM_FLASH_60HZ_HS_MTP_CHECKSUM_OFS)
#define HUBBLE_POC_MTP_60HZ_HS_CHECKSUM_SIZE (S6E3HAB_DIM_FLASH_60HZ_HS_MTP_CHECKSUM_LEN)
#define HUBBLE_POC_MTP_60HZ_HS_TOTAL_SIZE (S6E3HAB_DIM_FLASH_60HZ_HS_MTP_TOTAL_SIZE)
#endif

#define HUBBLE_POC_MCD_ADDR	(0xB8000)
#define HUBBLE_POC_MCD_SIZE (S6E3HAB_FLASH_MCD_LEN)

#ifdef CONFIG_SUPPORT_POC_SPI
#define HUBBLE_SPI_ER_DONE_MDELAY		(35)
#define HUBBLE_SPI_STATUS_WR_DONE_MDELAY		(15)

#ifdef PANEL_POC_SPI_BUSY_WAIT
#define HUBBLE_SPI_WR_DONE_UDELAY		(50)
#else
#define HUBBLE_SPI_WR_DONE_UDELAY		(400)
#endif
#endif

/* ===================================================================================== */
/* ============================== [S6E3HAB MAPPING TABLE] ============================== */
/* ===================================================================================== */
static struct maptbl hubble_poc_maptbl[] = {
	[POC_WR_ADDR_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_wr_addr_table, init_common_table, NULL, copy_poc_wr_addr_maptbl),
	[POC_RD_ADDR_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_rd_addr_table, init_common_table, NULL, copy_poc_rd_addr_maptbl),
	[POC_WR_DATA_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_wr_data_table, init_common_table, NULL, copy_poc_wr_data_maptbl),
#ifdef CONFIG_SUPPORT_POC_FLASH
	[POC_ER_ADDR_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_er_addr_table, init_common_table, NULL, copy_poc_er_addr_maptbl),
#endif
#ifdef CONFIG_SUPPORT_POC_SPI
	[POC_SPI_READ_ADDR_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_spi_read_table, init_common_table, NULL, copy_poc_rd_addr_maptbl),
	[POC_SPI_WRITE_ADDR_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_spi_write_addr_table, init_common_table, NULL, copy_poc_wr_addr_maptbl),
	[POC_SPI_WRITE_DATA_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_spi_write_data_table, init_common_table, NULL, copy_poc_wr_data_maptbl),
	[POC_SPI_ERASE_ADDR_MAPTBL] = DEFINE_0D_MAPTBL(hubble_poc_spi_erase_addr_table, init_common_table, NULL, copy_poc_er_addr_maptbl),
#endif
};

/* ===================================================================================== */
/* ============================== [S6E3HAB COMMAND TABLE] ============================== */
/* ===================================================================================== */
static u8 HUBBLE_KEY2_ENABLE[] = { 0xF0, 0x5A, 0x5A };
static u8 HUBBLE_KEY2_DISABLE[] = { 0xF0, 0xA5, 0xA5 };
static u8 HUBBLE_POC_KEY_ENABLE[] = { 0xF1, 0xF1, 0xA2 };
static u8 HUBBLE_POC_KEY_DISABLE[] = { 0xF1, 0xA5, 0xA5 };
static u8 HUBBLE_POC_PGM_ENABLE[] = { 0xC0, 0x02 };
static u8 HUBBLE_POC_PGM_DISABLE[] = { 0xC0, 0x00 };
static u8 HUBBLE_POC_EXEC[] = { 0xC0, 0x03 };
#ifdef CONFIG_SUPPORT_POC_FLASH
static u8 HUBBLE_POC_ER_CTRL_01[] = { 0xC1, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04 };
static u8 HUBBLE_POC_ER_CTRL_02[] = { 0xC1, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04 };
static u8 HUBBLE_POC_ER_4K_STT[] = { 0xC1, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x04 };
static u8 HUBBLE_POC_ER_32K_STT[] = { 0xC1, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x04 };
static u8 HUBBLE_POC_ER_64K_STT[] = { 0xC1, 0x00, 0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x04 };
#endif
static u8 HUBBLE_POC_RD_ENABLE[] = { 0xC1, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, HUBBLE_BDIV };
static u8 HUBBLE_POC_QD_ENABLE[] = { 0xC1, 0x00, 0x00, 0x00, 0x01, 0x5E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04 };
static u8 HUBBLE_POC_RD_STT[] = { 0xC1, 0x00, 0x00, 0x00, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, HUBBLE_BDIV, 0x01 };

static u8 HUBBLE_POC_WR_ENABLE_01[] = { 0xC1, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04 };
static u8 HUBBLE_POC_WR_ENABLE_02[] = { 0xC1, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04 };
static u8 HUBBLE_POC_WR_END[] = { 0xC1, 0x00, 0x00, 0xFF, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x01 };
static u8 HUBBLE_POC_WR_EXIT[] = { 0xC1, 0x00, 0x00, 0x00, 0x01, 0x5E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04 };
static u8 HUBBLE_POC_WR_STT_DAT[] = { 0xC1, 0x00, 0x00, 0xFF, 0x32, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, //addr
	0x40, 0x04, 0x01,
	//data
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};


static DEFINE_STATIC_PACKET(hubble_level2_key_enable, DSI_PKT_TYPE_WR, HUBBLE_KEY2_ENABLE, 0);
static DEFINE_STATIC_PACKET(hubble_level2_key_disable, DSI_PKT_TYPE_WR, HUBBLE_KEY2_DISABLE, 0);
static DEFINE_STATIC_PACKET(hubble_poc_key_enable, DSI_PKT_TYPE_WR, HUBBLE_POC_KEY_ENABLE, 0);
static DEFINE_STATIC_PACKET(hubble_poc_key_disable, DSI_PKT_TYPE_WR, HUBBLE_POC_KEY_DISABLE, 0);
static DEFINE_STATIC_PACKET(hubble_poc_pgm_enable, DSI_PKT_TYPE_WR, HUBBLE_POC_PGM_ENABLE, 0);
static DEFINE_STATIC_PACKET(hubble_poc_pgm_disable, DSI_PKT_TYPE_WR, HUBBLE_POC_PGM_DISABLE, 0);
#ifdef CONFIG_SUPPORT_POC_FLASH
static DEFINE_STATIC_PACKET(hubble_poc_er_ctrl_01, DSI_PKT_TYPE_WR, HUBBLE_POC_ER_CTRL_01, 0);
static DEFINE_STATIC_PACKET(hubble_poc_er_ctrl_02, DSI_PKT_TYPE_WR, HUBBLE_POC_ER_CTRL_02, 0);
static DEFINE_PKTUI(hubble_poc_er_4k_stt, &hubble_poc_maptbl[POC_ER_ADDR_MAPTBL], 5);
static DEFINE_VARIABLE_PACKET(hubble_poc_er_4k_stt, DSI_PKT_TYPE_WR, HUBBLE_POC_ER_4K_STT, 0);
static DEFINE_PANEL_MDELAY(hubble_poc_wait_er_4k_done, HUBBLE_ER_4K_DONE_MDELAY);
static DEFINE_PKTUI(hubble_poc_er_32k_stt, &hubble_poc_maptbl[POC_ER_ADDR_MAPTBL], 5);
static DEFINE_VARIABLE_PACKET(hubble_poc_er_32k_stt, DSI_PKT_TYPE_WR, HUBBLE_POC_ER_32K_STT, 0);
static DEFINE_PANEL_MDELAY(hubble_poc_wait_er_32k_done, HUBBLE_ER_32K_DONE_MDELAY);
static DEFINE_PKTUI(hubble_poc_er_64k_stt, &hubble_poc_maptbl[POC_ER_ADDR_MAPTBL], 5);
static DEFINE_VARIABLE_PACKET(hubble_poc_er_64k_stt, DSI_PKT_TYPE_WR, HUBBLE_POC_ER_64K_STT, 0);
static DEFINE_PANEL_MDELAY(hubble_poc_wait_er_64k_done, HUBBLE_ER_64K_DONE_MDELAY);
#endif
static DEFINE_STATIC_PACKET(hubble_poc_exec, DSI_PKT_TYPE_WR, HUBBLE_POC_EXEC, 0);
static DEFINE_STATIC_PACKET(hubble_poc_rd_enable, DSI_PKT_TYPE_WR, HUBBLE_POC_RD_ENABLE, 0);
static DEFINE_STATIC_PACKET(hubble_poc_qd_enable, DSI_PKT_TYPE_WR, HUBBLE_POC_QD_ENABLE, 0);
static DEFINE_STATIC_PACKET(hubble_poc_wr_enable_01, DSI_PKT_TYPE_WR, HUBBLE_POC_WR_ENABLE_01, 0);
static DEFINE_STATIC_PACKET(hubble_poc_wr_enable_02, DSI_PKT_TYPE_WR, HUBBLE_POC_WR_ENABLE_02, 0);
static DEFINE_STATIC_PACKET(hubble_poc_wr_end, DSI_PKT_TYPE_WR, HUBBLE_POC_WR_END, 0);
static DEFINE_STATIC_PACKET(hubble_poc_wr_exit, DSI_PKT_TYPE_WR, HUBBLE_POC_WR_EXIT, 0);
static DEFINE_PKTUI(hubble_poc_rd_stt, &hubble_poc_maptbl[POC_RD_ADDR_MAPTBL], 8);
static DEFINE_VARIABLE_PACKET(hubble_poc_rd_stt, DSI_PKT_TYPE_WR, HUBBLE_POC_RD_STT, 0);
static DECLARE_PKTUI(hubble_poc_wr_stt_dat) = {
	{ .offset = 8, .maptbl = &hubble_poc_maptbl[POC_WR_ADDR_MAPTBL] },
	{ .offset = 14, .maptbl = &hubble_poc_maptbl[POC_WR_DATA_MAPTBL] },
};
static DEFINE_VARIABLE_PACKET(hubble_poc_wr_stt_dat, DSI_PKT_TYPE_WR, HUBBLE_POC_WR_STT_DAT, 0);

static DEFINE_PANEL_UDELAY_NO_SLEEP(hubble_poc_wait_exec, HUBBLE_EXEC_USEC);
static DEFINE_PANEL_UDELAY_NO_SLEEP(hubble_poc_wait_rd_done, HUBBLE_RD_DONE_UDELAY);
static DEFINE_PANEL_UDELAY_NO_SLEEP(hubble_poc_wait_wr_exec, HUBBLE_WR_EXEC_UDELAY);
static DEFINE_PANEL_MDELAY(hubble_poc_wait_wr_done, HUBBLE_WR_DONE_MDELAY);
static DEFINE_PANEL_UDELAY_NO_SLEEP(hubble_poc_wait_wr_enable_01, HUBBLE_WR_ENABLE_01_UDELAY);
static DEFINE_PANEL_MDELAY(hubble_poc_wait_wr_enable_02, HUBBLE_WR_ENABLE_02_MDELAY);
static DEFINE_PANEL_MDELAY(hubble_poc_wait_qd_status, HUBBLE_QD_DONE_MDELAY);

#ifdef CONFIG_SUPPORT_POC_SPI
static u8 HUBBLE_POC_SPI_SET_STATUS1_INIT[] = { 0x01, 0x00 };
static u8 HUBBLE_POC_SPI_SET_STATUS2_INIT[] = { 0x31, 0x00 };
static u8 HUBBLE_POC_SPI_SET_STATUS1_EXIT[] = { 0x01, 0x5C };
static u8 HUBBLE_POC_SPI_SET_STATUS2_EXIT[] = { 0x31, 0x02 };
static DEFINE_STATIC_PACKET(hubble_poc_spi_set_status1_init, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_SET_STATUS1_INIT, 0);
static DEFINE_STATIC_PACKET(hubble_poc_spi_set_status2_init, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_SET_STATUS2_INIT, 0);
static DEFINE_STATIC_PACKET(hubble_poc_spi_set_status1_exit, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_SET_STATUS1_EXIT, 0);
static DEFINE_STATIC_PACKET(hubble_poc_spi_set_status2_exit, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_SET_STATUS2_EXIT, 0);

static u8 HUBBLE_POC_SPI_STATUS1[] = { 0x05 };
static u8 HUBBLE_POC_SPI_STATUS2[] = { 0x35 };
static u8 HUBBLE_POC_SPI_READ[] = { 0x03, 0x00, 0x00, 0x00 };
static u8 HUBBLE_POC_SPI_ERASE_4K[] = { 0x20, 0x00, 0x00, 0x00 };
static u8 HUBBLE_POC_SPI_ERASE_32K[] = { 0x52, 0x00, 0x00, 0x00 };
static u8 HUBBLE_POC_SPI_ERASE_64K[] = { 0xD8, 0x00, 0x00, 0x00 };
static u8 HUBBLE_POC_SPI_WRITE_ENABLE[] = { 0x06 };
static u8 HUBBLE_POC_SPI_WRITE[260] = { 0x02, 0x00, 0x00, 0x00, };
static DEFINE_STATIC_PACKET(hubble_poc_spi_status1, SPI_PKT_TYPE_SETPARAM, HUBBLE_POC_SPI_STATUS1, 0);
static DEFINE_STATIC_PACKET(hubble_poc_spi_status2, SPI_PKT_TYPE_SETPARAM, HUBBLE_POC_SPI_STATUS2, 0);
static DEFINE_STATIC_PACKET(hubble_poc_spi_write_enable, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_WRITE_ENABLE, 0);
static DEFINE_PKTUI(hubble_poc_spi_erase_4k, &hubble_poc_maptbl[POC_SPI_ERASE_ADDR_MAPTBL], 1);
static DEFINE_VARIABLE_PACKET(hubble_poc_spi_erase_4k, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_ERASE_4K, 0);
static DEFINE_PKTUI(hubble_poc_spi_erase_32k, &hubble_poc_maptbl[POC_SPI_ERASE_ADDR_MAPTBL], 1);
static DEFINE_VARIABLE_PACKET(hubble_poc_spi_erase_32k, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_ERASE_32K, 0);
static DEFINE_PKTUI(hubble_poc_spi_erase_64k, &hubble_poc_maptbl[POC_SPI_ERASE_ADDR_MAPTBL], 1);
static DEFINE_VARIABLE_PACKET(hubble_poc_spi_erase_64k, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_ERASE_64K, 0);

static DECLARE_PKTUI(hubble_poc_spi_write) = {
	{ .offset = 1, .maptbl = &hubble_poc_maptbl[POC_SPI_WRITE_ADDR_MAPTBL] },
	{ .offset = 4, .maptbl = &hubble_poc_maptbl[POC_SPI_WRITE_DATA_MAPTBL] },
};
static DEFINE_VARIABLE_PACKET(hubble_poc_spi_write, SPI_PKT_TYPE_WR, HUBBLE_POC_SPI_WRITE, 0);
static DEFINE_PKTUI(hubble_poc_spi_rd_addr, &hubble_poc_maptbl[POC_SPI_READ_ADDR_MAPTBL], 1);
static DEFINE_VARIABLE_PACKET(hubble_poc_spi_rd_addr, SPI_PKT_TYPE_SETPARAM, HUBBLE_POC_SPI_READ, 0);
static DEFINE_PANEL_UDELAY_NO_SLEEP(hubble_poc_spi_wait_write, HUBBLE_SPI_WR_DONE_UDELAY);
static DEFINE_PANEL_MDELAY(hubble_poc_spi_wait_erase, HUBBLE_SPI_ER_DONE_MDELAY);
static DEFINE_PANEL_MDELAY(hubble_poc_spi_wait_status, HUBBLE_SPI_STATUS_WR_DONE_MDELAY);
#endif

#ifdef CONFIG_SUPPORT_POC_FLASH
static void *hubble_poc_erase_enter_cmdtbl[] = {
	&PKTINFO(hubble_level2_key_enable),
	&PKTINFO(hubble_poc_key_enable),
	&PKTINFO(hubble_poc_pgm_enable),
	&PKTINFO(hubble_poc_er_ctrl_01),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_wr_enable_01),
	&PKTINFO(hubble_poc_er_ctrl_02),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_wr_enable_02),
};

static void *hubble_poc_erase_4k_cmdtbl[] = {
	&PKTINFO(hubble_poc_er_ctrl_01),
	&PKTINFO(hubble_poc_exec),
	&PKTINFO(hubble_poc_er_4k_stt),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_er_4k_done),
};

static void *hubble_poc_erase_32k_cmdtbl[] = {
	&PKTINFO(hubble_poc_er_ctrl_01),
	&PKTINFO(hubble_poc_exec),
	&PKTINFO(hubble_poc_er_32k_stt),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_er_32k_done),
};

static void *hubble_poc_erase_64k_cmdtbl[] = {
	&PKTINFO(hubble_poc_er_ctrl_01),
	&PKTINFO(hubble_poc_exec),
	&PKTINFO(hubble_poc_er_64k_stt),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_er_64k_done),
};

static void *hubble_poc_erase_exit_cmdtbl[] = {
	&PKTINFO(hubble_poc_pgm_disable),
	&PKTINFO(hubble_poc_key_disable),
	&PKTINFO(hubble_level2_key_disable),
};
#endif

static void *hubble_poc_wr_enter_cmdtbl[] = {
	&PKTINFO(hubble_level2_key_enable),
	&PKTINFO(hubble_poc_key_enable),
	&PKTINFO(hubble_poc_pgm_enable),
	&PKTINFO(hubble_poc_wr_enable_01),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_wr_enable_01),
	&PKTINFO(hubble_poc_wr_enable_02),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_wr_enable_02),
};

static void *hubble_poc_wr_dat_cmdtbl[] = {
	&PKTINFO(hubble_poc_wr_enable_01),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_wr_enable_01),
	&PKTINFO(hubble_poc_wr_stt_dat),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_wr_exec),
	&PKTINFO(hubble_poc_wr_end),
	&DLYINFO(hubble_poc_wait_wr_done),
};
static void *hubble_poc_wr_exit_cmdtbl[] = {
	&PKTINFO(hubble_poc_pgm_disable),
	&PKTINFO(hubble_poc_key_disable),
	&PKTINFO(hubble_level2_key_disable),
};

static void *hubble_poc_rd_enter_cmdtbl[] = {
	&PKTINFO(hubble_level2_key_enable),
	&PKTINFO(hubble_poc_key_enable),
	&PKTINFO(hubble_poc_pgm_enable),
	&PKTINFO(hubble_poc_rd_enable),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_exec),
	&PKTINFO(hubble_poc_qd_enable),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_qd_status),
};

static void *hubble_poc_rd_dat_cmdtbl[] = {
	&PKTINFO(hubble_poc_rd_stt),
	&PKTINFO(hubble_poc_exec),
	&DLYINFO(hubble_poc_wait_rd_done),
	&s6e3hab_restbl[RES_POC_DATA],
};

static void *hubble_poc_rd_exit_cmdtbl[] = {
	&PKTINFO(hubble_poc_pgm_disable),
	&PKTINFO(hubble_poc_pgm_enable),
	&PKTINFO(hubble_poc_wr_enable_01),
	&PKTINFO(hubble_poc_exec),
	&PKTINFO(hubble_poc_wr_exit),
	&PKTINFO(hubble_poc_exec),
	&PKTINFO(hubble_poc_pgm_disable),
	&PKTINFO(hubble_poc_key_disable),
	&PKTINFO(hubble_level2_key_disable),
};
#ifdef CONFIG_SUPPORT_POC_SPI
static void *hubble_poc_spi_init_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_set_status1_init),
	&DLYINFO(hubble_poc_spi_wait_status),
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_set_status2_init),
	&DLYINFO(hubble_poc_spi_wait_status),
};

static void *hubble_poc_spi_exit_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_set_status1_exit),
	&DLYINFO(hubble_poc_spi_wait_status),
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_set_status2_exit),
	&DLYINFO(hubble_poc_spi_wait_status),
};

static void *hubble_poc_spi_read_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_rd_addr),
	&s6e3hab_restbl[RES_POC_SPI_READ],
};

static void *hubble_poc_spi_erase_4k_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_erase_4k),
};

static void *hubble_poc_spi_erase_32k_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_erase_32k),
};

static void *hubble_poc_spi_erase_64k_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_erase_64k),
};

static void *hubble_poc_spi_write_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_write_enable),
	&PKTINFO(hubble_poc_spi_write),
#ifndef PANEL_POC_SPI_BUSY_WAIT
	&DLYINFO(hubble_poc_spi_wait_write),
#endif
};

static void *hubble_poc_spi_status_cmdtbl[] = {
	&PKTINFO(hubble_poc_spi_status1),
	&s6e3hab_restbl[RES_POC_SPI_STATUS1],
	&PKTINFO(hubble_poc_spi_status2),
	&s6e3hab_restbl[RES_POC_SPI_STATUS2],
};

static void *hubble_poc_spi_wait_write_cmdtbl[] = {
	&DLYINFO(hubble_poc_spi_wait_write),
};

static void *hubble_poc_spi_wait_erase_cmdtbl[] = {
	&DLYINFO(hubble_poc_spi_wait_erase),
};
#endif

static struct seqinfo hubble_poc_seqtbl[MAX_POC_SEQ] = {
#ifdef CONFIG_SUPPORT_POC_FLASH
	/* poc erase */
	[POC_ERASE_ENTER_SEQ] = SEQINFO_INIT("poc-erase-enter-seq", hubble_poc_erase_enter_cmdtbl),
	[POC_ERASE_4K_SEQ] = SEQINFO_INIT("poc-erase-4k-seq", hubble_poc_erase_4k_cmdtbl),
	[POC_ERASE_32K_SEQ] = SEQINFO_INIT("poc-erase-32k-seq", hubble_poc_erase_32k_cmdtbl),
	[POC_ERASE_64K_SEQ] = SEQINFO_INIT("poc-erase-64k-seq", hubble_poc_erase_64k_cmdtbl),
	[POC_ERASE_EXIT_SEQ] = SEQINFO_INIT("poc-erase-exit-seq", hubble_poc_erase_exit_cmdtbl),
#endif

	/* poc write */
	[POC_WRITE_ENTER_SEQ] = SEQINFO_INIT("poc-wr-enter-seq", hubble_poc_wr_enter_cmdtbl),
	[POC_WRITE_DAT_SEQ] = SEQINFO_INIT("poc-wr-dat-seq", hubble_poc_wr_dat_cmdtbl),
	[POC_WRITE_EXIT_SEQ] = SEQINFO_INIT("poc-wr-exit-seq", hubble_poc_wr_exit_cmdtbl),

	/* poc read */
	[POC_READ_ENTER_SEQ] = SEQINFO_INIT("poc-rd-enter-seq", hubble_poc_rd_enter_cmdtbl),
	[POC_READ_DAT_SEQ] = SEQINFO_INIT("poc-rd-dat-seq", hubble_poc_rd_dat_cmdtbl),
	[POC_READ_EXIT_SEQ] = SEQINFO_INIT("poc-rd-exit-seq", hubble_poc_rd_exit_cmdtbl),
#ifdef CONFIG_SUPPORT_POC_SPI
	[POC_SPI_INIT_SEQ] = SEQINFO_INIT("poc-spi-init-seq", hubble_poc_spi_init_cmdtbl),
	[POC_SPI_EXIT_SEQ] = SEQINFO_INIT("poc-spi-exit-seq", hubble_poc_spi_exit_cmdtbl),
	[POC_SPI_READ_SEQ] = SEQINFO_INIT("poc-spi-read-seq", hubble_poc_spi_read_cmdtbl),
	[POC_SPI_ERASE_4K_SEQ] = SEQINFO_INIT("poc-spi-erase-4k-seq", hubble_poc_spi_erase_4k_cmdtbl),
	[POC_SPI_ERASE_32K_SEQ] = SEQINFO_INIT("poc-spi-erase-4k-seq", hubble_poc_spi_erase_32k_cmdtbl),
	[POC_SPI_ERASE_64K_SEQ] = SEQINFO_INIT("poc-spi-erase-32k-seq", hubble_poc_spi_erase_64k_cmdtbl),
	[POC_SPI_WRITE_SEQ] = SEQINFO_INIT("poc-spi-write-seq", hubble_poc_spi_write_cmdtbl),
	[POC_SPI_STATUS_SEQ] = SEQINFO_INIT("poc-spi-status-seq", hubble_poc_spi_status_cmdtbl),
	[POC_SPI_WAIT_WRITE_SEQ] = SEQINFO_INIT("poc-spi-wait-write-seq", hubble_poc_spi_wait_write_cmdtbl),
	[POC_SPI_WAIT_ERASE_SEQ] = SEQINFO_INIT("poc-spi-wait-erase-seq", hubble_poc_spi_wait_erase_cmdtbl),
#endif
};

/* partition consists of DATA, CHECKSUM and MAGICNUM */
static struct poc_partition hubble_preliminary_poc_partition[] = {
	[POC_IMG_PARTITION] = {
		.name = "image",
		.addr = HUBBLE_POC_IMG_ADDR,
		.size = HUBBLE_POC_IMG_SIZE,
		.need_preload = false
	},
#ifdef CONFIG_SUPPORT_DIM_FLASH
	[POC_DIM_PARTITION] = {
		.name = "dimming",
		.addr = HUBBLE_POC_DIM_DATA_ADDR,
		.size = HUBBLE_POC_DIM_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_DIM_DATA_ADDR,
		.data_size = HUBBLE_POC_DIM_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_DIM_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_DIM_CHECKSUM_SIZE,
		.magicnum_addr = HUBBLE_POC_DIM_MAGICNUM_ADDR,
		.magicnum_size = HUBBLE_POC_DIM_MAGICNUM_SIZE,
		.need_preload = false,
		.magicnum = 1,
	},
	[POC_MTP_PARTITION] = {
		.name = "mtp",
		.addr = HUBBLE_POC_MTP_DATA_ADDR,
		.size = HUBBLE_POC_MTP_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_MTP_DATA_ADDR,
		.data_size = HUBBLE_POC_MTP_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_MTP_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_MTP_CHECKSUM_SIZE,
		.magicnum_addr = 0,
		.magicnum_size = 0,
		.need_preload = false,
	},
	[POC_DIM_PARTITION_1] = {
		.name = "dimming",
		.addr = HUBBLE_POC_DIM_120HZ_DATA_ADDR,
		.size = HUBBLE_POC_DIM_120HZ_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_DIM_120HZ_DATA_ADDR,
		.data_size = HUBBLE_POC_DIM_120HZ_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_DIM_120HZ_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_DIM_120HZ_CHECKSUM_SIZE,
		.magicnum_addr = HUBBLE_POC_DIM_120HZ_MAGICNUM_ADDR,
		.magicnum_size = HUBBLE_POC_DIM_120HZ_MAGICNUM_SIZE,
		.need_preload = false,
		.magicnum = 1,
	},
	[POC_MTP_PARTITION_1] = {
		.name = "mtp",
		.addr = HUBBLE_POC_MTP_120HZ_DATA_ADDR,
		.size = HUBBLE_POC_MTP_120HZ_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_MTP_120HZ_DATA_ADDR,
		.data_size = HUBBLE_POC_MTP_120HZ_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_MTP_120HZ_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_MTP_120HZ_CHECKSUM_SIZE,
		.magicnum_addr = 0,
		.magicnum_size = 0,
		.need_preload = false,
	},
#endif
	[POC_MCD_PARTITION] = {
		.name = "mcd",
		.addr = HUBBLE_POC_MCD_ADDR,
		.size = HUBBLE_POC_MCD_SIZE,
		.need_preload = false
	},
};

static struct poc_partition hubble_poc_partition[] = {
	[POC_IMG_PARTITION] = {
		.name = "image",
		.addr = HUBBLE_POC_IMG_ADDR,
		.size = HUBBLE_POC_IMG_SIZE,
		.need_preload = false
	},
#ifdef CONFIG_SUPPORT_DIM_FLASH
	[POC_DIM_PARTITION] = {
		.name = "dimming",
		.addr = HUBBLE_POC_DIM_DATA_ADDR,
		.size = HUBBLE_POC_DIM_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_DIM_DATA_ADDR,
		.data_size = HUBBLE_POC_DIM_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_DIM_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_DIM_CHECKSUM_SIZE,
		.magicnum_addr = HUBBLE_POC_DIM_MAGICNUM_ADDR,
		.magicnum_size = HUBBLE_POC_DIM_MAGICNUM_SIZE,
		.need_preload = false,
		.magicnum = 1,
	},
	[POC_MTP_PARTITION] = {
		.name = "mtp",
		.addr = HUBBLE_POC_MTP_DATA_ADDR,
		.size = HUBBLE_POC_MTP_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_MTP_DATA_ADDR,
		.data_size = HUBBLE_POC_MTP_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_MTP_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_MTP_CHECKSUM_SIZE,
		.magicnum_addr = 0,
		.magicnum_size = 0,
		.need_preload = false,
	},
	[POC_DIM_PARTITION_1] = {
		.name = "dimming",
		.addr = HUBBLE_POC_DIM_120HZ_DATA_ADDR,
		.size = HUBBLE_POC_DIM_120HZ_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_DIM_120HZ_DATA_ADDR,
		.data_size = HUBBLE_POC_DIM_120HZ_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_DIM_120HZ_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_DIM_120HZ_CHECKSUM_SIZE,
		.magicnum_addr = HUBBLE_POC_DIM_120HZ_MAGICNUM_ADDR,
		.magicnum_size = HUBBLE_POC_DIM_120HZ_MAGICNUM_SIZE,
		.need_preload = false,
		.magicnum = 1,
	},
	[POC_MTP_PARTITION_1] = {
		.name = "mtp",
		.addr = HUBBLE_POC_MTP_120HZ_DATA_ADDR,
		.size = HUBBLE_POC_MTP_120HZ_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_MTP_120HZ_DATA_ADDR,
		.data_size = HUBBLE_POC_MTP_120HZ_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_MTP_120HZ_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_MTP_120HZ_CHECKSUM_SIZE,
		.magicnum_addr = 0,
		.magicnum_size = 0,
		.need_preload = false,
	},
	[POC_DIM_PARTITION_2] = {
		.name = "dimming",
		.addr = HUBBLE_POC_DIM_60HZ_HS_DATA_ADDR,
		.size = HUBBLE_POC_DIM_60HZ_HS_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_DIM_60HZ_HS_DATA_ADDR,
		.data_size = HUBBLE_POC_DIM_60HZ_HS_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_DIM_60HZ_HS_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_DIM_60HZ_HS_CHECKSUM_SIZE,
		.magicnum_addr = HUBBLE_POC_DIM_60HZ_HS_MAGICNUM_ADDR,
		.magicnum_size = HUBBLE_POC_DIM_60HZ_HS_MAGICNUM_SIZE,
		.need_preload = false,
		.magicnum = 1,
	},
	[POC_MTP_PARTITION_2] = {
		.name = "mtp",
		.addr = HUBBLE_POC_MTP_60HZ_HS_DATA_ADDR,
		.size = HUBBLE_POC_MTP_60HZ_HS_TOTAL_SIZE,
		.data_addr = HUBBLE_POC_MTP_60HZ_HS_DATA_ADDR,
		.data_size = HUBBLE_POC_MTP_60HZ_HS_DATA_SIZE,
		.checksum_addr = HUBBLE_POC_MTP_60HZ_HS_CHECKSUM_ADDR,
		.checksum_size = HUBBLE_POC_MTP_60HZ_HS_CHECKSUM_SIZE,
		.magicnum_addr = 0,
		.magicnum_size = 0,
		.need_preload = false,
	},
#endif
	[POC_MCD_PARTITION] = {
		.name = "mcd",
		.addr = HUBBLE_POC_MCD_ADDR,
		.size = HUBBLE_POC_MCD_SIZE,
		.need_preload = false
	},
};

static struct panel_poc_data s6e3hab_hubble_preliminary_poc_data = {
	.version = 2,
	.seqtbl = hubble_poc_seqtbl,
	.nr_seqtbl = ARRAY_SIZE(hubble_poc_seqtbl),
	.maptbl = hubble_poc_maptbl,
	.nr_maptbl = ARRAY_SIZE(hubble_poc_maptbl),
	.partition = hubble_preliminary_poc_partition,
	.nr_partition = ARRAY_SIZE(hubble_preliminary_poc_partition),
	.wdata_len = 256,
#ifdef CONFIG_SUPPORT_POC_SPI
	.spi_wdata_len = 256,
	.conn_src = POC_CONN_SRC_SPI,
	.state_mask = 0x025C,
	.state_init = 0x0000,
	.state_uninit = 0x025C,
	.busy_mask = 0x0001,
#endif
};

static struct panel_poc_data s6e3hab_hubble_poc_data = {
	.version = 2,
	.seqtbl = hubble_poc_seqtbl,
	.nr_seqtbl = ARRAY_SIZE(hubble_poc_seqtbl),
	.maptbl = hubble_poc_maptbl,
	.nr_maptbl = ARRAY_SIZE(hubble_poc_maptbl),
	.partition = hubble_poc_partition,
	.nr_partition = ARRAY_SIZE(hubble_poc_partition),
	.wdata_len = 256,
#ifdef CONFIG_SUPPORT_POC_SPI
	.spi_wdata_len = 256,
	.conn_src = POC_CONN_SRC_SPI,
	.state_mask = 0x025C,
	.state_init = 0x0000,
	.state_uninit = 0x025C,
	.busy_mask = 0x0001,
#endif
};
#endif /* __S6E3HAB_HUBBLE_PANEL_POC_H__ */
