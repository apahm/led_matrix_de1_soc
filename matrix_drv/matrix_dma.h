#ifndef _ETN_DMA_H
#define _ETN_DMA_H

#include <linux/platform_device.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>


struct fpga_rx_buff {
	void *addr;
	dma_addr_t dma_addr;
    uint32_t size;
};

struct fpga_dev;

int fpga_add_rx_buffer(struct fpga_dev *fpga, uint32_t size);
irqreturn_t fpga_isr(int irq, void *dev_id);

#endif