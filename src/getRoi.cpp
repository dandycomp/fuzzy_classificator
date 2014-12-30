#include "getRoi.h"

void onMouse(int event, int x, int y, int, void*)
{
	buttonIsJustPushedUP = false;

	if (selectObject)
	{
		selection.x = MIN(x, origin.x);
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);
		selection.height = std::abs(y - origin.y);

		selection &= Rect(0, 0, image.cols, image.rows);
	}
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);
		selectObject = true;
		break;
	case CV_EVENT_LBUTTONUP:
		selectObject = false;
		if (toDetect){
			detecting(image, selection);
			
		}
		else{
		drawAndSave(image, selection);
		stDevAndMean(image, selection);
		}

		if (selection.width > 0 && selection.height > 0)
			trackObject = -1;
		break;
	}
}

static void detecting(Mat& img, Rect rect)
{
	Mat roi(imageClear, selection);
	FLParameters flp(roi);
	flp.info();

	vector<float> params(6);
	for (int i = 0; i < NR_OF_CHANNEL; i++)
	{
		params[i] = flp.m_mean[i];
		params[i + NR_OF_CHANNEL] = flp.m_stDev[i];
	}
	
	//bool decide = classDecision.clasify(params);
	string label = classDecision.clasifyWithLabels(params);
	cout << " Label = " << label << endl;
	if (label != "No object")
	{
		cout << "Detected object" << endl;
		Mat roi(imageClear, selection);
		rectangle(image, selection, CV_RGB(0, 255, 255), 2);
		//dodac napis na obrazku
		putText(image, label, Point(selection.x, selection.y), 
			FONT_HERSHEY_PLAIN, 1, cvScalar(255,0,255), 2);
	}
	else
	{
		cout << " Not detected " << endl;
	}
}


static void drawAndSave(Mat& img, Rect rect){
	Mat roi(imageClear, selection);
	rectangle(image, selection, CV_RGB(0, 0, 255), 2);
	string nr = to_string(counter);
	string outpFileName = name + nr + imgFormat;
	cout << "saving" << outpFileName << endl;
	imwrite(outpFileName, roi);
	counter++;
}

static void stDevAndMean(Mat& img, Rect rect){
	Mat roi(imageClear, selection);
	FLParameters flp(roi);
	flp.info();

	//float meanAndStdParameters[NR_OF_CHANNEL * 2];
	vector<float> meanAndStdParameters(6);
	for (int i = 0; i < NR_OF_CHANNEL; i++)
	{
		meanAndStdParameters[i] = flp.m_mean[i];
		meanAndStdParameters[i + NR_OF_CHANNEL] = flp.m_stDev[i];
		//cout << " Wypisanie: " << meanAndStdParameters[i] << " std: " << meanAndStdParameters[i + NR_OF_CHANNEL] << endl;
	}
	parameters.push_back(meanAndStdParameters);
}


void GetRoi::run(){
	m_img.copyTo(image);
	m_img.copyTo(imageClear);
	Mat temp;
	Rect lastRect;
	namedWindow("Window", 0);
	setMouseCallback("Window", onMouse, 0);
	for (;;)
	{
		image.copyTo(temp);
		if (selectObject && selection.width > 0 && selection.height > 0)
		{
			rectangle(temp, selection, CV_RGB(255, 255, 0), 5);
		}
		imshow("Window", temp);
		if (waitKey(10) > 10)
			break;
	}
}

GetRoi::GetRoi(Mat&img)
{
	Decision temDec;
	classDecision.setParameterAs(temDec);
	m_img = img;
	toDetect = false;
}

GetRoi::GetRoi(Mat&img, vector<vector<float>> param)
{
	m_img = img;
	classDecision.setParameters(param);
	toDetect = true;
}

GetRoi::GetRoi(Mat &img, vector<LearnData> data){
	m_img = img;
	m_LearnedData = data;
	classDecision.setParameters(data);
	toDetect = true;
}


vector<vector<float>> GetRoi::getParameters()
{
	return parameters;
}