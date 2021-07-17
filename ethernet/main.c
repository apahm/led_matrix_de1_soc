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
    const int size_buffer = 1;
	uint64_t one_frame_buffer[size_buffer];

    one_frame_buffer[0] = 0x100020004000800;
	

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

	int fd_ctrl_dev = open("/dev/matrix-ctrl",O_RDWR);

	if( fd_ctrl_dev < 0 ) {
        perror( "open_ctrl_dev" );
        exit( -1 ); 
    }


	close(fd_ctrl_dev);
	close(fd_data_dev);
}