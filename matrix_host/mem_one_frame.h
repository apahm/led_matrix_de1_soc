#ifndef MEM_FUNC
#define MEM_FUNC
#include <vector>
#include <stdint.h>
#include <opencv2/core/core.hpp>


int sender_one_frame(std::vector<uint64> &buffer);
void mem(std::vector<uint64_t> &buffer,std::vector<cv::Mat> &rgb_vector);

#endif