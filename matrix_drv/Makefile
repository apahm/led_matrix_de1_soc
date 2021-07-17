LINUXDIR := /home/alex/linux/linux-socfpga.a9

# This is default values until you set them from env.

obj-m += matrix.o

matrix-objs := matrix_main.o matrix_dma.o matrix_regs.o matrix_data_fops.o matrix_ctrl_fops.o


default:
	make ARCH=arm  CROSS_COMPILE=arm-none-linux-gnueabihf- \
	-C $(LINUXDIR) M=$(shell pwd)

clean:
	make -C $(LINUXDIR) M=$(shell pwd) clean