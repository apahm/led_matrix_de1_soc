/**
 * File operations for /dev/matrix-data char device.
 */
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <linux/poll.h>
#include <asm/io.h>
#include <asm/ioctl.h>

#include "matrix_main.h"
#include "matrix_regs.h"
#include "matrix_dma.h"

#define COPY_ONE_FRAME_TO_BUFFER _IOC(_IOC_WRITE, 'k', 1, TX_BUF_SIZE)

static long matrix_data_dev_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
    struct fpga_dev *fpga = filp->private_data;
    struct fpga_rx_buff *rx_buff = &fpga->buff;
    
    uint32_t size = rx_buff->size;

    switch(cmd) {
        case COPY_ONE_FRAME_TO_BUFFER:
            if( copy_from_user(rx_buff->addr, (uint64_t *)arg, TX_BUF_SIZE ) )
                return -EFAULT;
            printk("value = 0x%llx;\n",*(uint64_t *)rx_buff->addr);
        break;
    default:
        return -ENOTTY;
    }

    return 0;
}

static int matrix_data_dev_open(struct inode *inode, struct file *filp)
{
	struct fpga_dev *fpga = container_of(filp->private_data, struct fpga_dev, data_dev);

	filp->private_data = fpga;

	return 0;
}

static int matrix_data_dev_release(struct inode *inode, struct file *filp)
{
    return 0;
}


ssize_t matrix_data_dev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    return 0;
}

ssize_t matrix_data_dev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    struct fpga_dev *fpga = filp->private_data;
    struct fpga_rx_buff *rx_buff = &fpga->buff;
    
    uint32_t size = rx_buff->size;
    
    unsigned long ret_cfu = 0;

    ssize_t len = min(rx_buff->size - *f_pos, count);
    if (len <= 0)
            return 0;  

    ret_cfu = copy_from_user(rx_buff->addr,buf,count);
    if(ret_cfu)
            return -EFAULT;
            
    *f_pos += count;
    return ret_cfu;

}


loff_t matrix_data_dev_lseek (struct file *filp, loff_t off, int whence)
{
    struct fpga_dev *fpga = filp->private_data;
	
    loff_t newpos;
    uint32_t size;

    size = fpga->buff.size;

    switch(whence) {

        case SEEK_SET:
            newpos = off;
            break;

        case SEEK_CUR:
            newpos = filp->f_pos + off;
            break;

        case SEEK_END:
            newpos = size + off;
            break;

        default: 
            return -EINVAL;
        }

    if (newpos < 0) 
        return -EINVAL;

    if (newpos > size)
        newpos = size;  

    filp->f_pos = newpos;

    return newpos;
}


const struct file_operations matrix_data_dev_fops = {
	.owner   = THIS_MODULE,
	.open    = matrix_data_dev_open,
	.release = matrix_data_dev_release,
	.read    = matrix_data_dev_read,
	.write   = matrix_data_dev_write,
    .llseek  = matrix_data_dev_lseek,
    .unlocked_ioctl = matrix_data_dev_ioctl,
};

