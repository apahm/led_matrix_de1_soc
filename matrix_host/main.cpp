#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp> 
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <stddef.h>
#include <stdint.h>

#define MATRIX_SIZE 64 

void mem(uint64_t *buffer,std::vector<cv::Mat> &rgb_vector)
{
    uint8_t iterator = 7;
    uint64_t iter_low, iter_high = 0;

    for (ssize_t i =  32; i < 40; i++)
    {
        for (ssize_t j = 0; j < 2; j++)
        {
            iterator = 7;
            for (ssize_t k = 0; k < 32; k++)
            {
                buffer[k + 128 * iter_low + j * 32] |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4) | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )));
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
                buffer[k + 128 * iter_high + j * 32] |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
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
                buffer[k + 128 * iter_low + j * 32] |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4) | (0xF0 & rgb_vector[1].at<uint8_t>(i,iterator + j * 32)) | ( ( 0xF0 & rgb_vector[2].at<uint8_t>(i,iterator + j * 32)) << 4 )) << 12);
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
                buffer[k + 128 * iter_high + j * 32] |= (uint64_t)((( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
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
                buffer[k + 128 * iter_low + j * 32] |= 0xFFF000000 &((uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
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
                buffer[k + 128 * iter_high + j * 32] |= 0xFFF000000 &((uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
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
                buffer[k + 128 * iter_low + j * 32] |= (uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
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
    
    for (int i = 24; i < 36; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            iterator = 7;
            for (int k = 64; k < 96; k++)
            {
                buffer[k + 128 * iter_high + j * 32] |= (uint64_t)(( ( 0xF0 & rgb_vector[0].at<uint8_t>(i,iterator + j * 32)) >> 4)
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
int main()
{   
    cv::Mat input = cv::imread("/home/alex/matrix/matrix_host/test_image/grad.jpg", cv::IMREAD_COLOR); 
    
    cv::flip(input,input,1);

    cv::resize(input, input, cv::Size(64, 64));

    std::vector<cv::Mat> rgb_vector;
    cv::split(input, rgb_vector);

    uint64_t buffer[1024];

    
    for (size_t i = 0; i < 1024; i++)
    {
        buffer[i] = 0x0;
    }
    
    mem(buffer,rgb_vector);

    printf("Succesfuly!\n");
    return 0;
}