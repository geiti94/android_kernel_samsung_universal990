/*
 * linux/drivers/video/fbdev/exynos/mafpc/mafpc_drv.c
 *
 * Source file for AOD Driver
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
#include "mafpc_drv.h"


static int mafpc_open(struct inode *inode, struct file *file)
{
	int ret = 0;

	struct miscdevice *miscdev = file->private_data;
	struct mafpc_device *mafpc = container_of(miscdev, struct mafpc_device, miscdev); 
 
	file->private_data = mafpc;

	return ret;
}



static ssize_t mafpc_write(struct file *file, const char __user *buf,
		  size_t count, loff_t *ppos)
{	
	int write_size;
	char temp[44];
	bool scale_factor = false;
	struct mafpc_device *mafpc = file->private_data;

	write_size = MAFPC_HEADER_SIZE + MAFPC_CTRL_CMD_SIZE + 
		mafpc->img_size;

	if (count == write_size) {
		panel_info("[mAFPC:INFO]:%s Write size: %d, without scale factor\n",
			__func__, count);
		scale_factor = false;
	} else if (count == write_size + mafpc->scale_size) {
		panel_info("[mAFPC:INFO]:%s Write size: %d, with scale factor\n",
			__func__, count);
		scale_factor = true;
	} else {
		panel_err("[mAFPC:ERR]:%s: undefined write size : %d:%d\n",
			__func__, count);
		goto err_write;
	}

	if (copy_from_user(temp, buf, MAFPC_HEADER_SIZE + MAFPC_CTRL_CMD_SIZE)) {
		panel_err("[mAFPC:ERR]:%s: failed to get user's header\n", __func__);
		goto err_write;
	}

	if (temp[0] != MAFPC_HEADER) {
		panel_err("[mAFPC:ERR]%s: wrong header : %c\n", __func__);
		goto err_write;
	}

	panel_info("[mAFPC:Info]:%s:header : %c\n", __func__, temp[0]);
	
	memcpy(mafpc->ctrl_cmd, temp + MAFPC_HEADER_SIZE, MAFPC_CTRL_CMD_SIZE);
	
	print_hex_dump(KERN_ERR, "", DUMP_PREFIX_ADDRESS, 32, 4,
			mafpc->ctrl_cmd, MAFPC_CTRL_CMD_SIZE, false);

	if (mafpc->img_buf == NULL) {
		panel_err("[mAFPC:ERR]:%s: mafpc img buf is null\n", __func__);
		goto err_write;
	}

	panel_info("[mAFPC:Info]:%s:img size : %d\n", __func__, mafpc->img_size);

	if (copy_from_user(mafpc->img_buf,
			buf + MAFPC_HEADER_SIZE + MAFPC_CTRL_CMD_SIZE, mafpc->img_size)) {
		panel_err("[mAFPC:ERR]%s: failed to get comp img\n", __func__);
		goto err_write;
	}
	mafpc->written |= MAFPC_UPDATED_FROM_SVC;

	if (scale_factor == false)
		goto err_write;

	if (mafpc->scale_buf == NULL) {
		panel_err("[mAFPC:ERR]:%s: mafpc img buf is null\n", __func__);
		goto err_write;
	}

	panel_info("[mAFPC:Info]:%s:img size : %d\n", __func__, mafpc->scale_size);

	if (copy_from_user(mafpc->scale_buf,
			buf + MAFPC_HEADER_SIZE + MAFPC_CTRL_CMD_SIZE + mafpc->img_size,
			mafpc->scale_size)) {
		panel_err("[mAFPC:ERR]%s: failed to get comp img\n", __func__);
		goto err_write;
	}

	print_hex_dump(KERN_ERR, "", DUMP_PREFIX_ADDRESS, 32, 4,
			mafpc->scale_buf, mafpc->scale_size, false);

err_write:
	return count;
}

static int mafpc_instant_on(struct mafpc_device *mafpc)
{
	int ret = 0;
	struct panel_device *panel = mafpc->panel;

	if (panel == NULL) {
		panel_err("mAFPC:ERR:%s:panel is null\n", __func__);
		return -EINVAL;
	}
	
	mutex_lock(&mafpc->mafpc_lock);

	if (!IS_PANEL_ACTIVE(panel)) {
		panel_err("[mAFPC:ERR]:%s:panel is not active\n", __func__);
		goto err;
	}

	if (panel->state.cur_state == PANEL_STATE_ALPM) {
		panel_err("[mAFPC:ERR]:%s gct not supported on LPM\n", __func__);
		goto err;
	}

	ret = panel_do_seqtbl_by_index(panel, PANEL_MAFPC_IMG_SEQ);
	if (unlikely(ret < 0)) {
		panel_err("mAFPC:ERR:%s, failed to write init seqtbl\n", __func__);
		goto err;
	}
	mafpc->written |= MAFPC_UPDATED_TO_DEV;

	ret = panel_do_seqtbl_by_index(panel, PANEL_MAFPC_ON_SEQ);
	if (unlikely(ret < 0)) {
		panel_err("mAFPC:ERR:%s, failed to write init seqtbl\n", __func__);
	}

err:
	mutex_unlock(&mafpc->mafpc_lock);
	return ret;

}


static int mafpc_instant_off(struct mafpc_device *mafpc)
{
	int ret = 0;
	struct panel_device *panel = mafpc->panel;

	mutex_lock(&mafpc->mafpc_lock);

	if (!IS_PANEL_ACTIVE(panel)) {
		panel_err("[mAFPC:ERR]:%s:panel is not active\n", __func__);
		goto err;
	}

	if (panel->state.cur_state == PANEL_STATE_ALPM) {
		panel_err("[mAFPC:ERR]:%s gct not supported on LPM\n", __func__);
		goto err;
	}

	ret = panel_do_seqtbl_by_index(panel, PANEL_MAFPC_OFF_SEQ);
	if (unlikely(ret < 0)) {
		panel_err("mAFPC:ERR:%s, failed to write init seqtbl\n", __func__);
	}

err:
	mutex_unlock(&mafpc->mafpc_lock);
	return ret;
}


static long mafpc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	struct mafpc_device *mafpc = file->private_data;

	switch(cmd) {
		case IOCTL_MAFPC_ON:
			panel_info("[mAFPC:INFO]:%s:mAFPC on\n", __func__);
			mafpc->enable = true;
			break;
		case IOCTL_MAFPC_ON_INSTANT:
			panel_info("[mAFPC:INFO]:%s:mAFPC on instantly On\n", __func__);
			mafpc->enable = true;
			ret = mafpc_instant_on(mafpc);
			if (ret)
				panel_info("[mAFPC:ERR]:%s: failed to instant on\n", __func__);
			break;
		case IOCTL_MAFPC_OFF:
			panel_info("[mAFPC:INFO]:%s:mAFPC off\n", __func__);
			mafpc->enable = false;
			break;
		case IOCTL_MAFPC_OFF_INSTANT:
			panel_info("[mAFPC:INFO]:%s:mAFPC off instantly\n", __func__);
			mafpc->enable = false;
			ret = mafpc_instant_off(mafpc);
			if (ret)
				panel_info("[mAFPC:ERR]:%s: failed to instant off\n", __func__);
			break;
		default:
			panel_info("[mAFPC:ERR]:%s:Invalid Command\n", __func__);
			break;
	}

	return ret;
}


static int mafpc_release(struct inode *inode, struct file *file)
{
	int ret = 0;

	panel_info(
"[mAFPC:Info]:%s was called\n", __func__);
	
	return ret;
}

static const struct file_operations mafpc_drv_fops = {
	.owner = THIS_MODULE,
	.open = mafpc_open,
	.write = mafpc_write,
	.unlocked_ioctl = mafpc_ioctl,
	.release = mafpc_release,
};


static int transmit_mafpc_data(struct mafpc_device *mafpc)
{
	int ret = 0;
	s64 time_diff;
	ktime_t timestamp;
	struct panel_device *panel = mafpc->panel;

	timestamp = ktime_get();
	decon_systrace(get_decon_drvdata(0), 'C', "mafpc", 1);
#if 0
	ret = panel_do_seqtbl_by_index(panel, PANEL_MAFPC_IMG_SEQ);
	if (unlikely(ret < 0)) {
		panel_err("PANEL:ERR:%s, failed to write init seqtbl\n", __func__);
	}
#endif
#if 0
	ret = panel_do_seqtbl_by_index(panel, PANEL_MAFPC_ON_SEQ);
	if (unlikely(ret < 0)) {
		panel_err("PANEL:ERR:%s, failed to write init seqtbl\n", __func__);
	}
#endif	
	decon_systrace(get_decon_drvdata(0), 'C', "mafpc", 0);

	time_diff = ktime_to_us(ktime_sub(ktime_get(), timestamp));
	panel->mafpc_write_time = time_diff;
	panel_info("[mAFPC:INFO]:%s time for mAFPC : %llu \n", __func__, time_diff);

	return ret;
}


static int mafpc_thread(void *data)
{
	int ret;
	struct mafpc_device *mafpc = data;

	while (!kthread_should_stop()) {	
		ret = wait_event_interruptible(mafpc->wq_wait, mafpc->req_update);
		mutex_lock(&mafpc->mafpc_lock);
		panel_info("mAFPC:INFO:%s:was called\n", __func__);
		transmit_mafpc_data(mafpc);
		mafpc->req_update = false;
		mutex_unlock(&mafpc->mafpc_lock);
	}
	return 0;
}


static int mafpc_create_thread(struct mafpc_device *mafpc)
{
	init_waitqueue_head(&mafpc->wq_wait);

	mafpc->thread = kthread_run(mafpc_thread, mafpc, "mafpc-thread");
	if (IS_ERR_OR_NULL(mafpc->thread)) {
		panel_err("mAFPC:ERR:%s: failed to create mafpc thread\n");
		return PTR_ERR(mafpc->thread);
	}

	return 0;
}

static int get_comp_img_buf(struct mafpc_device *mafpc)
{
	int ret = 0;

	struct seqinfo *img_seqtbl = NULL;
	struct pktinfo *img_pktinfo = NULL;
	struct panel_device *panel = mafpc->panel;

	img_seqtbl = find_panel_seqtbl(&panel->panel_data, "mafpc-img-seq");
	if (img_seqtbl == NULL) {
		panel_err("[mAFPC:ERR]:%s failed to find mafpc-img seqtbl\n", __func__);
		ret = -EINVAL;
		goto err_get_buf;
	}

	img_pktinfo = find_packet_suffix(img_seqtbl, "mafpc_default_img");
	if (img_pktinfo == NULL) {
		panel_err("[mAFPC:ERR]:%s failed to find mafpc-img pktinfo\n", __func__);
		ret = -EINVAL;
		goto err_get_buf;
	}

	mafpc->img_buf = img_pktinfo->data;
	mafpc->img_size = img_pktinfo->dlen;

	panel_info("[mAFPC:INFO]:%s comp img size : %d\n", __func__, mafpc->img_size);

	return ret;

err_get_buf:
	return ret;
}

static int get_scale_factor_buf(struct mafpc_device *mafpc)
{
	int ret = 0;

	struct seqinfo *scale_seqtbl = NULL;
	struct pktinfo *scale_pktinfo = NULL;
	struct panel_device *panel = mafpc->panel;

	scale_seqtbl = find_panel_seqtbl(&panel->panel_data, "mafpc-scale-seq");
	if (scale_seqtbl == NULL) {
		panel_err("[mAFPC:ERR]:%s failed to find mafpc-img seqtbl\n", __func__);
		ret = -EINVAL;
		goto err_get_buf;
	}

	scale_pktinfo = find_packet_suffix(scale_seqtbl, "mafpc_scale_factor");
	if (scale_pktinfo == NULL) {
		panel_err("[mAFPC:ERR]:%s failed to find mafpc-img pktinfo\n", __func__);
		ret = -EINVAL;
		goto err_get_buf;
	}

	mafpc->scale_buf = scale_pktinfo->data;
	mafpc->scale_size = scale_pktinfo->dlen;

	panel_info("[mAFPC:INFO]:%s scale factor size : %d\n", __func__, mafpc->scale_size);

	return ret;

err_get_buf:
	return ret;
}



static int mafpc_v4l2_probe(struct mafpc_device *mafpc, void *arg)
{
	int ret = 0;
	
	struct panel_device *panel = (struct panel_device *)arg;

	mafpc->panel = panel;

	ret = get_comp_img_buf(mafpc);
	if (ret) {
		panel_err("[mAFPC:ERR]:%s failed to get comp img buf info\n", __func__);
		goto err_v4l2_probe; 
	}

	ret = get_scale_factor_buf(mafpc);
	if (ret) {
		panel_err("[mAFPC:ERR]:%s failed to get scale factor buf info\n", __func__);
		goto err_v4l2_probe; 
	}

	mafpc_create_thread(mafpc);

	return ret;

err_v4l2_probe:
	return ret;
}


static int mafpc_v4l2_update_req(struct mafpc_device *mafpc)
{
	int ret = 0;

	return ret;

	if (mafpc->thread) {
		mafpc->req_update = true;
		wake_up_interruptible_all(&mafpc->wq_wait);
	}
	return ret;
}


static int mafpc_v4l2_write_complte(struct mafpc_device *mafpc)
{
	int ret = 0;
	
	if (mafpc->req_update == true) {
		mutex_lock(&mafpc->mafpc_lock);
		mutex_unlock(&mafpc->mafpc_lock);
	}

	return ret;
}

static long mafpc_core_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	int ret = 0;
	struct mafpc_device *mafpc = container_of(sd, struct mafpc_device, sd);

	switch(cmd) {
		case V4L2_IOCTL_MAFPC_PROBE:
			panel_info("[PANEL:INFO]:%s : V4L2_IOCTL_MAFPC_PROBE\n", __func__);
			ret = mafpc_v4l2_probe(mafpc, arg);
			break;
		case V4L2_IOCTL_MAFPC_UDPATE_REQ:
			panel_info("[PANEL:INFO]:%s : V4L2_IOCTL_MAFPC_UDPATE_REQ\n", __func__);
			ret = mafpc_v4l2_update_req(mafpc);
			break;
		case V4L2_IOCTL_MAFPC_WAIT_COMP:
			panel_info("[PANEL:INFO]%s: V4L2_IOCTL_MAFPC_WAIT_COMP\n", __func__);
			ret = mafpc_v4l2_write_complte(mafpc);
			break;
		case V4L2_IOCTL_MAFPC_GET_INFO:
			v4l2_set_subdev_hostdata(sd, mafpc);
			break;
		case V4L2_IOCTL_MAFPC_PANEL_INIT:
			panel_info("[PANEL:INFO]%s: V4L2_IOCTL_MAFPC_GET_INIT\n", __func__);
			mafpc->written |= MAFPC_UPDATED_TO_DEV;
			break;
		case V4L2_IOCTL_MAFPC_PANEL_EXIT:
			panel_info("[PANEL:INFO]%s: V4L2_IOCTL_MAFPC_GET_EXIT\n", __func__);
			mafpc->written &= ~(MAFPC_UPDATED_TO_DEV);
			break;
		default:
			panel_err("[mAFPC:ERR]:%s: invalid cmd\n", __func__);
	}

	return ret;
}

static const struct v4l2_subdev_core_ops mafpc_v4l2_sd_core_ops = {
	.ioctl = mafpc_core_ioctl,
};

static const struct v4l2_subdev_ops mafpc_subdev_ops = {
	.core = &mafpc_v4l2_sd_core_ops,
};


static void mafpc_init_v4l2_subdev(struct mafpc_device *mafpc)
{
	struct v4l2_subdev *sd = &mafpc->sd;

	v4l2_subdev_init(sd, &mafpc_subdev_ops);
	sd->owner = THIS_MODULE;
	sd->grp_id = 0;
	snprintf(sd->name, sizeof(sd->name), "%s.%d", MAFPC_V4L2_DEV_NAME, mafpc->id);
	v4l2_set_subdevdata(sd, mafpc);
}

static int mfac_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct device *dev = &pdev->dev;
	struct mafpc_device *mafpc = NULL;

	mafpc = devm_kzalloc(dev, sizeof(struct mafpc_device), GFP_KERNEL);
	if (!mafpc) {
		panel_err("failed to allocate mafpc device.\n");
		ret = -ENOMEM;
		goto probe_err;
	}
	platform_set_drvdata(pdev, mafpc);

	mafpc->dev = dev;
	
	mafpc->miscdev.minor = MISC_DYNAMIC_MINOR;
	mafpc->miscdev.fops = &mafpc_drv_fops;
	mafpc->miscdev.name = MAFPC_DEV_NAME;

	mutex_init(&mafpc->mafpc_lock);

	ret = misc_register(&mafpc->miscdev);
	if (ret) {
		panel_err("PANEL:ERR:%s:failed to register mafpc drv\n", __func__);
		goto probe_err;
	}

	mafpc->id = of_alias_get_id(dev->of_node, "mafpc");

	mafpc_init_v4l2_subdev(mafpc);

	mafpc->factory_crc[0] = MAFPC_VALID_CRC_1;
	mafpc->factory_crc[1] = MAFPC_VALID_CRC_2;

	panel_info("[mAFPC:INFO]:%s: mAFPC proved: %d:\n", __func__, mafpc->id);

probe_err:
	return ret;
}


static const struct of_device_id mafpc_drv_of_match_table[] = {
	{ .compatible = "samsung,panel-mafpc", },
};
MODULE_DEVICE_TABLE(of, mafpc_drv_of_match_table);

static struct platform_driver mafpc_driver = {
	.probe = mfac_probe,
	.driver = {
		.name = MAFPC_DEV_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(mafpc_drv_of_match_table),
	}
};

static int __init mafpc_drv_init(void)
{
	return platform_driver_register(&mafpc_driver);
}

static void __exit mafpc_drv_exit(void)
{
	platform_driver_unregister(&mafpc_driver);
}

module_init(mafpc_drv_init);
module_exit(mafpc_drv_exit);

MODULE_AUTHOR("<minwoo7945.kim@samsung.com>");
MODULE_LICENSE("GPL");
