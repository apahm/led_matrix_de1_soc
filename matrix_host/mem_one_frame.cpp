#include "mem_one_frame.h"
#include <iostream>
#include <QtNetwork/qudpsocket.h>
#include <QtCore/qdebug.h>
#include <QtCore/qcoreapplication.h>

int sender_one_frame(std::vector<uint64> &buffer)
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
        memcpy(part_send,&buffer.at(buffer_iterator),512);
        if(socket.writeDatagram(part_send, 512, ip_send, port) != 512)
        {
            std::cout << "writeDatagram() failed." << std::endl;
        }
    }

    return 0;
}

void mem(std::vector<uint64_t> &buffer, std::vector<cv::Mat> &rgb_vector)
{
    uint8_t iterator = 7;
    uint64_t iter_low = 0;
    uint64_t iter_high = 0;

    for (ssize_t i =  32; i < 40; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 0; k < 32; k++)
            {
                buffer.at(k + 128 * iter_low + j * 32) |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4) | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )));
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_low += 1;
    }

    for (ssize_t i = 0; i < 8; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 64; k < 96; k++)
            {
                buffer.at(k + 128 * iter_high + j * 32) |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
                | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) 
                | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )));
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_high += 1;
    }
    iter_high = 0;
    iter_low = 0;
    for (ssize_t i =  40; i < 48; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 0; k < 32; k++)
            {
                buffer.at(k + 128 * iter_low + j * 32) |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4) | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )) << 12);
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_low += 1;
    }
    
    for (ssize_t i = 8; i < 16; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 64; k < 96; k++)
            {
                buffer.at(k + 128 * iter_high + j * 32) |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
                | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) 
                | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )) << 12);
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_high += 1;
    }
    iter_high = 0;
    iter_low = 0;
   
    for (ssize_t i =  48; i < 56; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 0; k < 32; k++)
            {
                buffer.at(k + 128 * iter_low + j * 32) |= 0xFFF000000 &((uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
                | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) 
                | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )) << 24);
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_low += 1;
    }
    
    for (ssize_t i = 16; i < 24; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 64; k < 96; k++)
            {
                buffer.at(k + 128 * iter_high + j * 32) |= 0xFFF000000 &((uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
                | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) 
                | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )) << 24);
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_high += 1;
    }
    
    iter_high = 0;
    iter_low = 0;
    for (ssize_t i =  56; i < 64; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 0; k < 32; k++)
            {
                buffer.at(k + 128 * iter_low + j * 32) |= (uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
                | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) 
                | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )) << 36;
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_low += 1;
    }
    
    for (int i = 24; i < 32; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            iterator = 7;
            for (int k = 64; k < 96; k++)
            {
                buffer.at(k + 128 * iter_high + j * 32) |= (uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
                | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) 
                | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )) << 36;
                if(iterator <= 7 && iterator > 0)
                    iterator--;
                else if(iterator == 0)
                    iterator = 8;
                else if(iterator >= 8 && iterator < 15) 
                    iterator++;
                else if(iterator == 15)
                    iterator = 23;
                else if( iterator > 16 && iterator <= 23)
                    iterator--; 
                else if(iterator == 16)
                    iterator = 24;
                else if(iterator >= 24 && iterator < 31)
                    iterator++;         
            }
 
        }
        iter_high += 1;
    }
    
    iter_high = 0;
    iter_low = 0;
    
}