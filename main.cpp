#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>

#include "realSenseWrapper.h"

using namespace std;
using namespace cv;
using namespace rs2;

int main() try
{
	realSenseWrapper sense;

	sense.init();

	while (true) {
		sense.setFrame();

		Mat color = sense.getColorImage();
		Mat depth = sense.getDepthImage();
		Mat distance = sense.getDepthDistance();

		imshow("color frame", color);
		imshow("depth frame", depth);
		imshow("depth distance", distance);

		// q key exit
		int key = waitKey(1);
		if (key == 'q') break;
	}

	destroyAllWindows();

	return 0;

}
catch (const rs2::error & e)
{
	std::cout << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const std::exception & e)
{
	std::cout << e.what() << std::endl;
	return EXIT_FAILURE;
}