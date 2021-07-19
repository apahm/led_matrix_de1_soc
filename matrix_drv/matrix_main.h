#ifndef _ETN_H
#define _ETN_H

#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>

#include "matrix_dma.h"

#define DRV_NAME "matrix"

#ifndef DRV_VERSION
#define DRV_VERSION "0.0.1"
#endif

#define TX_BUF_SIZE (8 * 1024)


struct fpga_dev {
	struct platform_device *pdev;

	struct miscdevice ctrl_dev;
	struct miscdevice data_dev;

    wait_queue_head_t data_queue;
    ktime_t start;
    int write_done;
    int irq;

	struct fpga_rx_buff buff;

    void __iomem *H2F;  
};

extern const struct file_operations matrix_ctrl_dev_fops;
extern const struct file_operations matrix_data_dev_fops;

#define   LWH2F_ADDR     0xFF200000
#define   LWH2F_LEN      0x4088


#endif