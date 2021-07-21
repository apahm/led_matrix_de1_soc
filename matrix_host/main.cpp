#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp> 
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    cv::Mat input = cv::imread("/home/alex/matrix/matrix_host/test_image/grad.jpg", cv::IMREAD_COLOR); 
    
    cv::flip(input,input,1);

    if(!input.empty())
    {
        cv::imshow("test", input);
        cv::waitKey(0);
    } 

    cv::resize(input, input, cv::Size(64, 64));

    std::vector<cv::Mat> rgb_vector;
    cv::split(input, rgb_vector);

    std::cout << (int)rgb_vector[0].at<uint8_t>(63,63) << std::endl;
    std::cout << (int)rgb_vector[1].at<uint8_t>(63,63) << std::endl;
    std::cout << (int)rgb_vector[2].at<uint8_t>(63,63) << std::endl;

    

    return 0;
}