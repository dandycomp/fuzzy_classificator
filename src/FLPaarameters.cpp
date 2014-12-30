#include "FLParameters.h"

FLParameters::FLParameters(Mat& img){
	m_img = img;
	split(m_img, m_channel);
	Mat mean[3];
	Mat stDev[3];
	meanStdDev(m_channel[0], mean[0], stDev[0]);//blue
	meanStdDev(m_channel[1], mean[1], stDev[1]);//grey
	meanStdDev(m_channel[2], mean[2], stDev[2]);//red

	for (int i = 0; i < 3; i++)
	{
		m_mean[i]   = (float)mean[i] .at<double>(0, 0);
		m_stDev[i] = (float)stDev[i].at<double>(0, 0);
	}
}

void FLParameters::info()
{
	cout << " Blue : " << " mean: " << m_mean[0] << " st deviation = " << m_stDev[0] << endl;
	cout << " Green: " << " mean: " << m_mean[1] << " st deviation = " << m_stDev[1] << endl;
	cout << " Red  : " << " mean: " << m_mean[2] << " st deviation = " << m_stDev[2] << endl;
}