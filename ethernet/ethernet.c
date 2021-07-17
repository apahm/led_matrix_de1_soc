#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "ethernet.h"

int eth_init()
{
	int sockfd;
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
	{
		printf("eth_init() failed: socket return : %d.\n",sockfd);
		return -1;
	}

	struct sockaddr_in servaddr;

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		printf("eth_init() failed: bind failed.\n");
		return -1;
	}
	return sockfd;
}


int set_receive_buffer_size(int sockfd,unsigned int size_of_receive_buffer)
{
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (const char*)(&size_of_receive_buffer), sizeof(size_of_receive_buffer)) != 0)
	{
		printf("set_receive_buffer_size() failed: setsockopt failed: set recive buffer size.\n");
		return -1;
	}
	return 0;
}
// Driver code

int receive_buffer(int sockfd,uint8_t *buffer, ssize_t size_of_buffer)
{
	int len, ret;
	struct sockaddr_in cliaddr;
	memset(&cliaddr, 0, sizeof(cliaddr));

	len = sizeof(cliaddr); 

	ret = recvfrom(sockfd, buffer, size_of_buffer, MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
	buffer[ret] = '\0';
	return ret;
}

int write_buffer(int sockfd, char *buffer, ssize_t size_of_buffer)
{
	return 0;
}

int close(int sockfd)
{
	if (close(sockfd) != 0)
	{
		printf("close(): close failed. \n");
		return -1;
	}
	return 0;
}
	
	

	

