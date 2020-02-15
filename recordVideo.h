#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

class recordVideo
{
private:
	int fourcc = 0;
	int fps = 30;
	cv::VideoWriter writer;

public:
	recordVideo();

	void init(std::string filename, int _fps, cv::Size _ksize);

	void record(cv::Mat _frame);
};

