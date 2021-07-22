#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp> 
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <stddef.h>
#include <stdint.h>
#include <QtNetwork/qudpsocket.h>
#include <QtCore/qdebug.h>
#include <QtCore/qcoreapplication.h>

#include "mem_one_frame.h"

#define MATRIX_SIZE 64

int sender(uint64_t *buffer)
{
    QUdpSocket socket;
    QHostAddress ip_send("192.168.1.43");
    uint16_t port = 8080;

    // Buffer for send

    char part_send[512];
    uint8_t number_of_transfer = 16;
    uint32_t buffer_iterator = 0;
    
    for (size_t i = 0; i < number_of_transfer; i++)
    {
        buffer_iterator = i * 64;
        memcpy(part_send,&buffer[buffer_iterator],512);
        if(socket.writeDatagram(part_send, 512, ip_send, port) != 512)
        {
            std::cout << "writeDatagram() failed." << std::endl;
        }
    }

    return 0;
}

int main()
{   
    // Get the image 
    cv::Mat input = cv::imread("/home/alex/matrix/matrix_host/test_image/grad.jpg", cv::IMREAD_COLOR); 
    
    cv::flip(input,input,1);
    
    // Resize image
    cv::resize(input, input, cv::Size(64, 64));

    // Get rgb component
    std::vector<cv::Mat> rgb_vector;
    cv::split(input, rgb_vector);
    
    uint64_t buffer[1024];
    
    for (size_t i = 0; i < 1024; i++)
    {
        buffer[i] = 0x0;
    }
    
    mem(buffer,rgb_vector);
    
    sender(buffer);

    printf("Succesfuly!\n");
    return 0;
}