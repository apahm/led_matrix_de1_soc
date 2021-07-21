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

int main()
{
    const int size_buffer = 1024;
	uint64_t one_frame_buffer[size_buffer];

	memset(one_frame_buffer,0,ONE_FRAME_SIZE_OF_MATRIX);

    //nayn_cat_buffer(one_frame_buffer, size_buffer);
	one_frame_buffer[0] 	= 0xFFF0F0F000FF;
	one_frame_buffer[1] 	= 0xFFF0F0F000FF;
	one_frame_buffer[2] 	= 0xFFF0F0F000FF;
	one_frame_buffer[3] 	= 0xFFF0F0F000FF;
	one_frame_buffer[4] 	= 0xFFF0F0F000FF;
	one_frame_buffer[5] 	= 0xFFF0F0F000FF;
	one_frame_buffer[6] 	= 0xFFF0F0F000FF;
	one_frame_buffer[7] 	= 0xFFF0F0F000FF;
	one_frame_buffer[8] 	= 0xFFF0F0F000FF;
	one_frame_buffer[9] 	= 0xFFF0F0F000FF;
	one_frame_buffer[10]	= 0xFFF0F0F000FF;
	one_frame_buffer[11]	= 0xFFF0F0F000FF;
	one_frame_buffer[12]	= 0xFFF0F0F000FF;
	one_frame_buffer[13]	= 0xFFF0F0F000FF;
	one_frame_buffer[14]	= 0xFFF0F0F000FF;
	one_frame_buffer[15]	= 0xFFF0F0F000FF;
	one_frame_buffer[16]	= 0xFFF0F0F000FF;
	one_frame_buffer[17]	= 0xFFF0F0F000FF;
	one_frame_buffer[18]	= 0xFFF0F0F000FF;
	one_frame_buffer[19]	= 0xFFF0F0F000FF;
	one_frame_buffer[20]	= 0xFFF0F0F000FF;
	one_frame_buffer[21]	= 0xFFF0F0F000FF;
	one_frame_buffer[22]	= 0xFFF0F0F000FF;
	one_frame_buffer[23]	= 0xFFF0F0F000FF;
	one_frame_buffer[24]	= 0xFFF0F0F000FF;
	one_frame_buffer[25]	= 0xFFF0F0F000FF;
	one_frame_buffer[26]	= 0xFFF0F0F000FF;
	one_frame_buffer[27]	= 0xFFF0F0F000FF;
	one_frame_buffer[28]	= 0xFFF0F0F000FF;
	one_frame_buffer[29]	= 0xFFF0F0F000FF;
	one_frame_buffer[30]	= 0xFFF0F0F000FF;
	one_frame_buffer[31]	= 0xFFF0F0F000FF;

	//one_frame_buffer[32] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[33] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[34] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[35] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[36] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[37] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[38] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[39] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[40] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[41] 	= 0xFFF0F0F000FF;
	//one_frame_buffer[42]	= 0xFFF0F0F000FF;
	//one_frame_buffer[43]	= 0xFFF0F0F000FF;
	//one_frame_buffer[44]	= 0xFFF0F0F000FF;
	//one_frame_buffer[45]	= 0xFFF0F0F000FF;
	//one_frame_buffer[46]	= 0xFFF0F0F000FF;
	//one_frame_buffer[47]	= 0xFFF0F0F000FF;
	//one_frame_buffer[48]	= 0xFFF0F0F000FF;
	//one_frame_buffer[49]	= 0xFFF0F0F000FF;
	//one_frame_buffer[50]	= 0xFFF0F0F000FF;
	//one_frame_buffer[51]	= 0xFFF0F0F000FF;
	//one_frame_buffer[52]	= 0xFFF0F0F000FF;
	//one_frame_buffer[53]	= 0xFFF0F0F000FF;
	//one_frame_buffer[54]	= 0xFFF0F0F000FF;
	//one_frame_buffer[55]	= 0xFFF0F0F000FF;
	//one_frame_buffer[56]	= 0xFFF0F0F000FF;
	//one_frame_buffer[57]	= 0xFFF0F0F000FF;
	//one_frame_buffer[58]	= 0xFFF0F0F000FF;
	//one_frame_buffer[59]	= 0xFFF0F0F000FF;
	//one_frame_buffer[60]	= 0xFFF0F0F000FF;
	//one_frame_buffer[61]	= 0xFFF0F0F000FF;
	//one_frame_buffer[62]	= 0xFFF0F0F000FF;
	//one_frame_buffer[63]	= 0xFFF0F0F000FF;
	
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