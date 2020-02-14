#pragma once

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

class realSenseWrapper
{
private:
	rs2::pipeline* pipe = nullptr;
	cv::Size color_size = cv::Size(1280, 720);
	cv::Size depth_size = cv::Size(1280, 720);
	int color_fps = 30;
	int depth_fps = 30;

	rs2::colorizer color_map;
	
	rs2::frame color_frame;
	rs2::frame depth_color_frame;
	rs2::frame depth_distance_frame;

	bool is_data = false;

public:
	enum {
		COLOR_CAMERA,
		DEPTH_CAMERA,
	};


public:
	// コンストラクタ
	realSenseWrapper();
	// デストラクタ
	~realSenseWrapper();

	// 画像サイズの設定
	void setCameraSize(int select, cv::Size ksize);

	// fpsを設定
	void setFps(int _color_fps = 30, int _depth_fps = 30);

	// 初期設定用関数
	int init();

	// 画像サイズを取得
	cv::Size getSize(int select);

	// FPSを取得
	int getFPS(int select);

	// 画像を取得する前に呼ぶ必要がある
	void setFrame();

	// RGBカメラのデータをMatクラスの形式で返す
	cv::Mat getColorImage();

	// Depthカメラのデータを色付きにしてMatクラスの形式で返す
	cv::Mat getDepthImage();

	// Depthカメラの距離のデータをMatクラスの形式で返す
	cv::Mat getDepthDistance();
};
