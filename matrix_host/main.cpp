#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp> 
#include <iostream>

int main(int argc, const char* argv[])
{
    const cv::Mat input = cv::imread("/home/alex/matrix/matrix_host/test_image/grad.jpg", cv::IMREAD_COLOR); 
    if(input.empty())
    {
        std::cout << "Image empty.\n";
    }
    else
    {
        cv::imshow("test", input);
        cv::waitKey(0);
    }
    

    return 0;
}