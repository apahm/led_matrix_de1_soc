#ifndef FPGA_CTRL
#define FPGA_CTRL

#define ONE_FRAME_SIZE_OF_MATRIX 8

#define COPY_ONE_FRAME_TO_BUFFER _IOC(_IOC_WRITE, 'k', 1, ONE_FRAME_SIZE_OF_MATRIX)

#endif