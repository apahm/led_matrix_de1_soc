#ifndef MEM_FUNC
#define MEM_FUNC
#include <vector>
#include <stdint.h>
#include <opencv2/core/core.hpp>

void mem(uint64_t *buffer,std::vector<cv::Mat> &rgb_vector);

#endif