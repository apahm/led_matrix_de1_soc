#include "matrix_main.h"
#include "matrix_regs.h"

u32 fpga_read_reg(struct fpga_dev *fpga, int reg)
{
	u32 tmp;
	tmp =  ioread32(fpga->H2F + reg);
	return tmp;
}

void fpga_write_reg(struct fpga_dev *fpga, int reg, u32 val)
{
	iowrite32(val, fpga->H2F + reg);
}