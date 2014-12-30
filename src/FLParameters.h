#ifndef FLP
#define FLP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>


using namespace std;
using namespace cv;

class FLParameters
{
private:
	Mat m_img;

	Mat m_channel[3];//bgr
public:
	FLParameters(Mat &img);
	void info();
	float m_mean[3];//bgr
	float m_stDev[3];//bgr
};

#endif
