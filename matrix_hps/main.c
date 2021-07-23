#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>
#include <fcntl.h>
#include <asm/ioctl.h>

#include "fpga_ctrl.h"
#include "test_buffer.h"
#include "ethernet.h"

int main()
{
    const int size_buffer = 1024;
	uint64_t one_frame_buffer[size_buffer];

	memset(one_frame_buffer,0,ONE_FRAME_SIZE_OF_MATRIX);

    //grad_buffer(one_frame_buffer, size_buffer);

	int socket_fd = 0;

	socket_fd = eth_init();
	
	if(socket_fd < 0)
	{
		perror("eth_init() failded.\n");
		exit(-1);
	}

	size_t size_of_part = 512;

	char part_receive[512];
	memset(part_receive,0,512);

	for (size_t i = 0; i < 16; i++)
	{
		if(i == 0)
		{
			printf("Begin receive packet ...\n");
		}

		int size_receive = receive_buffer(socket_fd, part_receive, size_of_part);
		if(size_receive != 512)
		{
			printf("Size of receive buffer failde = %d;\n",size_receive);
			break;
		}
		memcpy(&one_frame_buffer[i * 64], part_receive,512);
	}
	
	printf("End receive packet ...\n");

	for (size_t i = 0; i < 1024; i++)
	{
		printf("one_frame_buffer[%d] = 0x%llx;\n", i, one_frame_buffer[i]);
	}
	

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
	close(socket_fd);

	return 0;
}