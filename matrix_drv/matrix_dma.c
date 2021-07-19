#include "matrix_main.h"
#include "matrix_dma.h"
#include "matrix_regs.h"

int fpga_add_rx_buffer(struct fpga_dev *fpga, uint32_t size)
{
    void *addr;
    dma_addr_t dma_addr;

    addr = dmam_alloc_coherent(&fpga->pdev->dev, size, &dma_addr, GFP_KERNEL);

	if (unlikely(addr == NULL)) {
		printk("Failed to allocate RX buffer\n");
		return -ENOMEM;
	}

    printk( KERN_DEBUG "Add RX buff, addr=0x%p, dma_addr=0x%p, size=%d\n", 
                            addr, (void *)dma_addr, size);

	fpga->buff.addr = addr;
    fpga->buff.dma_addr = dma_addr;
    fpga->buff.size = size;

	if (dma_mapping_error(&fpga->pdev->dev, fpga->buff.dma_addr)) {
		printk("Failed to map RX buffer\n");
		fpga->buff.addr = NULL;
		fpga->buff.dma_addr = 0;
		return -ENOMEM;
	}

    dma_addr = dma_addr / 8;
    size = size / 8;

    
    //*(uint64_t *)addr = 0x100020004000800;
    //printk("addr = 0x%p, value = 0x%llx\n",addr, *(uint64_t *)addr);
    


    //Write DMA address to FPGA
    printk( KERN_DEBUG "Write fpga dma_addr: register 0x4, dma_addr=0x%x\n",dma_addr);
    fpga_write_reg(fpga, 0x4, dma_addr);

    // Write size of buffer to FPGA
    printk( KERN_DEBUG "Write size of buffer to fpga. Register 0x8, value %d\n",size * 8);
    fpga_write_reg(fpga, 0x8, size);

    // Write signal start to FPGA
    //printk( KERN_DEBUG "Write fpga start. Register: 0x0, value: 0x1; register: 0x0, value: 0x0\n");
    //fpga_write_reg(fpga, 0x0, 0x1);
    //fpga_write_reg(fpga, 0x0, 0x0);


    printk( KERN_DEBUG "Write matrix reset. Register 0x10, value = 1;\n");
    fpga_write_reg(fpga, 0x10, 0x1);

    printk( KERN_DEBUG "Write memory mux. Register 0xC, value = 0;\n");
    fpga_write_reg(fpga, 0xC, 0x0);
    
	return 0;
}


irqreturn_t fpga_isr(int irq, void *dev_id)
{
	struct fpga_dev *fpga = dev_id;

    printk( KERN_DEBUG "Get interrupt\n" );

    fpga->write_done = 1;

    wake_up_interruptible(&fpga->data_queue);
        
	return IRQ_HANDLED;
}