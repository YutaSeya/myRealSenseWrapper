#include "recordVideo.h"

#include <opencv2/opencv.hpp>
#include <iostream>

recordVideo::recordVideo()
{

}

void recordVideo::init(std::string filename, int _fps, cv::Size _ksize)
{
	fps = _fps;
	// * エンコード形式 "XVID" = AVI, "MP4V" = MPEG4, "WMV1" = WMV
	fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
	writer.open(filename, fourcc, _fps, _ksize);
}

void recordVideo::record(cv::Mat _frame)
{
	writer.write(_frame);
}