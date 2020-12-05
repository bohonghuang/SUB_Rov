#pragma once

#include <opencv2/opencv.hpp>

extern "C" int  __declspec(dllexport)  frameExchange(cv::Mat & src, cv::Mat & dct);

