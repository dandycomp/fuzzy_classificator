#ifndef getroi
#define getroi

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "createFLParameters.h"
#include "FLParameters.h"
#include "Decision.h"

#define NR_OF_CHANNEL 3

using namespace std;
using namespace cv;

static int counter = 0;
static string name = "img/img";
static string imgFormat = ".jpg";

static bool toDetect;// 2 types of algorithm. to detect or to learn.
static bool selectObject = false;
static Rect selection;
static Point origin;
static int trackObject = 0;
static Mat image;
static Mat imageClear;

static bool buttonIsJustPushedUP = false;
static void onMouse(int event, int x, int y, int, void*);
static void drawAndSave(Mat& img, Rect rect);
static void stDevAndMean(Mat& img, Rect rect);
static void detecting(Mat& img, Rect rect);
static vector<vector<float>> parameters; // m1 m2 m3 sd1 sd2 sd3
static Decision classDecision;

class GetRoi
{
public:
	GetRoi(Mat &img);
	GetRoi(Mat &img, vector<vector<float>>);
	GetRoi(Mat &img, vector<LearnData>);
	Mat m_img;
	vector<LearnData> m_LearnedData;
	void run();
	vector<vector<float>> getParameters();

};
#endif