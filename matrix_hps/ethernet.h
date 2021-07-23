#ifndef ETHERHNET
#define ETHERHNET

#define PORT	 				8080
#define SIZE_OF_RECEIVE_BUFFER_MAX  180224
#define SIZE_OF_RECEIVE_BUFFER_CURRENT (8*1024)

int eth_init();
int set_receive_buffer_size(int sockfd,unsigned int size_of_receive_buffer);
int receive_buffer(int sockfd,uint8_t *buffer, ssize_t size_of_buffer);
int write_buffer(int sockfd, char *buffer, ssize_t size_of_buffer);
int close(int sockfd);



#endif