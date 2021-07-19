#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <fcntl.h>
#include <asm/ioctl.h>

#include "fpga_ctrl.h"


int main()
{
    const int size_buffer = 1024;
	uint64_t one_frame_buffer[size_buffer];

	memset(one_frame_buffer,0,ONE_FRAME_SIZE_OF_MATRIX);

    one_frame_buffer[0] = 0xF0F;
    one_frame_buffer[1] = 0xF1F;
    one_frame_buffer[2] = 0xF2F;
    one_frame_buffer[3] = 0xFF0;
    one_frame_buffer[4] = 0xFAF;
    one_frame_buffer[5] = 0xFFF;
    one_frame_buffer[6] = 0x0FF;
    one_frame_buffer[7] = 0xFF1;
	

	int fd_data_dev = open("/dev/matrix-data",O_WRONLY);

	if( fd_data_dev < 0 ) {
        perror( "open_data_dev" );
        exit( -1 ); 
    }

	if (ioctl(fd_data_dev, COPY_ONE_FRAME_TO_BUFFER, one_frame_buffer) != 0)
	{
		perror("ioctlsocket failed: set ");
		exit(EXIT_FAILURE);
	}
	

	/*int fd_ctrl_dev = open("/dev/matrix-ctrl",O_RDWR);

	if( fd_ctrl_dev < 0 ) {
        perror( "open_ctrl_dev" );
        exit( -1 ); 
    }

	close(fd_ctrl_dev);*/
	close(fd_data_dev);

	return 0;
}