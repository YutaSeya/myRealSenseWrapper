#include "realSensseWrapper.h"

#include <iostream>

using namespace std;
using namespace cv;
using namespace rs2;

realSensseWrapper::realSensseWrapper()
{
	// デバイスを抽象化するパイプラインを構築
	if (pipe == nullptr) {
		pipe = new pipeline();
	}
}

realSensseWrapper::~realSensseWrapper()
{
	delete pipe;
}

void realSensseWrapper::setCameraSize(int select, Size ksize)
{
	if(select == COLOR_CAMERA){
		if (ksize.width > 1920) ksize.width = 1920;
		else if (ksize.width < 1) ksize.width = 1;

		if (ksize.height > 1080) ksize.height = 1080;
		else if (ksize.height < 1) ksize.height = 1;

		color_size = ksize;
	}
	else if (select == DEPTH_CAMERA) {
		if (ksize.width > 1280) ksize.width = 1280;
		else if (ksize.width < 1) ksize.width = 1;

		if (ksize.height > 720) ksize.height = 720;
		else if (ksize.height < 1) ksize.height = 1;
		depth_size = ksize;
	}
	else {
		cout << "selection is missing" << endl;
	}
}

void realSensseWrapper::setFps(int _color_fps, int _depth_fps)
{
	if (_color_fps < 0) _color_fps = 1;
	else if (_color_fps > 90) _color_fps = 90;

	if (_depth_fps < 0) _depth_fps = 1;
	else if (_depth_fps > 90) _depth_fps = 90;

	color_fps = _color_fps;
	depth_fps = _depth_fps;
}

int realSensseWrapper::init()
{

	config cfg;
	// 明示的にストリームを有効化する
	// カラーストリーム画像をBGR8フォーマット
	cfg.enable_stream(RS2_STREAM_COLOR, color_size.width, color_size.height, RS2_FORMAT_BGR8, color_fps);
	// デプスカメラのz16フォーマット
	cfg.enable_stream(RS2_STREAM_DEPTH, depth_size.width, depth_size.height, RS2_FORMAT_Z16, depth_fps);

	pipe->start(cfg);

	// 初期化に成功したら1を返す
	return 1;
}

Size realSensseWrapper::getSize(int select)
{
	if (select == DEPTH_CAMERA) {
		return depth_size;
	}
	else {
		return color_size;
	}
}

void realSensseWrapper::setFrame()
{
	// ストリームがフレームセットを取得するまで待機
	frameset frames = pipe->wait_for_frames();

	// フレームセットからカラーフレームを取得
	color_frame = frames.get_color_frame();
	// フレームセットからデプスフレームを取得(BGRの色つきのマップに変更)
	depth_color_frame = frames.get_depth_frame().apply_filter(color_map);
	// フレームセットからデプスフレームを取得(距離用)
	depth_distance_frame = frames.get_depth_frame();

	is_data = true;
}

Mat realSensseWrapper::getColorImage()
{
	if (!is_data) {
		// 初回のみ、データを取得する
		setFrame();
	}
	
	Mat data(color_size, CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
	return data;
	

}

Mat realSensseWrapper::getDepthImage()
{
	if (!is_data) {
		// 初回のみ、データを取得する
		setFrame();
	}
	
	Mat data(depth_size, CV_8UC3, (void*)depth_color_frame.get_data(), cv::Mat::AUTO_STEP);
	cvtColor(data, data, COLOR_RGB2BGR);
	return data;
}

Mat realSensseWrapper::getDepthDistance()
{
	if (!is_data) {
		// 初回のみ、データを取得する
		setFrame();
	}
	Mat dis(depth_size, CV_16UC1, (void*)depth_distance_frame.get_data(), cv::Mat::AUTO_STEP);
	dis.convertTo(dis, CV_64F);
	auto depth_scale = pipe->get_active_profile().get_device().first<depth_sensor>().get_depth_scale();
	dis = dis * depth_scale;
	return dis;
}