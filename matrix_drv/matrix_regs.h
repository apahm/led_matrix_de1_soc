#ifndef _ETN_REGS_H
#define _ETN_REGS_H

#include <asm/io.h>

void fpga_write_reg(struct fpga_dev *fpga, int reg, u32 val);
u32 fpga_read_reg(struct fpga_dev *fpga, int reg);


#endif