#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/of_irq.h>
#include <linux/phy.h>

#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <asm/io.h>

#include "matrix_main.h"
#include "matrix_regs.h"

static int map_hw_mem(struct fpga_dev *fpga)
{
	if (!request_mem_region(LWH2F_ADDR, LWH2F_LEN, DRV_NAME)) {
		printk("Failed to request mem region for H2F interface\n");
		goto err;
	}

	fpga->H2F = ioremap(LWH2F_ADDR, LWH2F_LEN);
	if (!fpga->H2F) {
		printk("Failed to map H2F address space\n");
		goto err_release_h2f;
	}

	return 0;

err_release_h2f:
	if (fpga->H2F) {
		iounmap(fpga->H2F);
	}
	release_mem_region(LWH2F_ADDR, LWH2F_LEN);

err:
	return -ENXIO;
}

static void unmap_hw_mem(struct fpga_dev *fpga)
{
	if (fpga->H2F) {
		iounmap(fpga->H2F);
		fpga->H2F = NULL;
		release_mem_region(LWH2F_ADDR, LWH2F_LEN);
	}
}


static const struct miscdevice matrix_ctrl_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "matrix-ctrl",
	.fops  = &matrix_ctrl_dev_fops,
};


static const struct miscdevice matrix_data_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "matrix-data",
	.fops  = &matrix_data_dev_fops,
};


int etn_register(struct fpga_dev *fpga)
{
    int err = 0;

    BUG_ON(fpga == NULL);

	printk("FPGA is ready, starting register\n");

    fpga->ctrl_dev = matrix_ctrl_dev;
    
	if ((err = misc_register(&fpga->ctrl_dev))) {
		printk("Cannot register control misc device\n");
		goto err;
	}
       

    fpga->data_dev = matrix_data_dev;

    if ((err = misc_register(&fpga->data_dev))) {
		printk("Cannot register data misc device\n");
		goto err_ctrl_dev;
	}
       
    printk( KERN_DEBUG "Register is successfully done\n");

	return 0;


/*err_data_dev:
	misc_deregister(&fpga->data_dev);
	fpga->data_dev.this_device = NULL;
*/
err_ctrl_dev:
	misc_deregister(&fpga->ctrl_dev);
	fpga->ctrl_dev.this_device = NULL;

err:
	return err;
}

void etn_unregister(struct fpga_dev *fpga)
{
	if (fpga) {

        if (fpga->ctrl_dev.this_device) {
	        misc_deregister(&fpga->ctrl_dev);
                fpga->ctrl_dev.this_device = NULL;
		}

        if (fpga->data_dev.this_device) {
	        misc_deregister(&fpga->data_dev);
                fpga->data_dev.this_device = NULL;
        }
                                
	}
}

void etn_free(struct fpga_dev *fpga)
{
	if (fpga) {
		etn_unregister(fpga);

		unmap_hw_mem(fpga);
		
		kfree(fpga);
	}
}

int etn_remove(struct platform_device *pdev)
{
	struct fpga_dev *fpga;

	fpga = platform_get_drvdata(pdev);

	etn_free(fpga);
	platform_set_drvdata(pdev, NULL);

	return 0;      
}

static u64 platform_dma_mask = DMA_BIT_MASK(24);

int etn_probe(struct platform_device *pdev)
{
    int err = 0;
    struct fpga_dev *fpga;


    fpga = kzalloc(sizeof(*fpga), GFP_KERNEL);
	if (!fpga)
		return -ENOMEM;

    if (map_hw_mem(fpga)) {
		printk("Failed to map H2F and LWH2F memory\n");
        err = -ENXIO;
		goto err_free_fpgadev;
	}

    pdev->dev.dma_mask = &platform_dma_mask;

    fpga->pdev = pdev;

	fpga_write_reg(fpga,0x40,0x1);

	int size = TX_BUF_SIZE;

	err = fpga_add_rx_buffer(fpga, size);

    if (err) {
	    printk("Failed to initialize RX buffer\n");
	    goto err_free_fpgadev;
    }

	if ((err = etn_register(fpga))) {
		dev_err(&pdev->dev,"Cannot register devices\n");
		goto err_free_fpgadev;
	}

    platform_set_drvdata(pdev, fpga);

	return 0;

err_free_fpgadev:
	if (fpga)
		kfree(fpga);
    
    return err;
}


static const struct of_device_id etn_of_match[] = {
	{ .compatible = "mtk,etn", },
	{},
};

MODULE_DEVICE_TABLE(of, etn_of_match);


static struct platform_driver etn_driver = {
	.remove = etn_remove,
	.driver = {
		.name	= "etn",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(etn_of_match),
	},
};


static int __init etn_init(void)
{
	if (platform_driver_probe(&etn_driver, etn_probe)) {
		printk("Failed to probe ETN platform driver\n");
		return -ENXIO;
	}

	return 0;
}


static void __exit etn_exit(void)
{
	platform_driver_unregister(&etn_driver);
}


MODULE_AUTHOR("Aleksandr Pakhmutov");
MODULE_DESCRIPTION("Driver for matrix");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

module_init(etn_init);
module_exit(etn_exit);