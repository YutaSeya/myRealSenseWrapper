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
	// �R���X�g���N�^
	realSenseWrapper();
	// �f�X�g���N�^
	~realSenseWrapper();

	// �摜�T�C�Y�̐ݒ�
	void setCameraSize(int select, cv::Size ksize);

	// fps��ݒ�
	void setFps(int _color_fps = 30, int _depth_fps = 30);

	// �����ݒ�p�֐�
	int init();

	// �摜�T�C�Y���擾
	cv::Size getSize(int select);

	// FPS���擾
	int getFPS(int select);

	// �摜���擾����O�ɌĂԕK�v������
	void setFrame();

	// RGB�J�����̃f�[�^��Mat�N���X�̌`���ŕԂ�
	cv::Mat getColorImage();

	// Depth�J�����̃f�[�^��F�t���ɂ���Mat�N���X�̌`���ŕԂ�
	cv::Mat getDepthImage();

	// Depth�J�����̋����̃f�[�^��Mat�N���X�̌`���ŕԂ�
	cv::Mat getDepthDistance();
};
