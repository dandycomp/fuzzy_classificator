#ifndef decision
#define decision
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <vector>
#include "createFLParameters.h"

using namespace cv;
using namespace std;
static float THRESHOLD = 0.7;
class Decision{
public:
	bool clasify(vector<float> parameters);//for 1 object
	string clasifyWithLabels(vector<float> parameters);//for more object, return label
	void setParameters(vector<LearnData>, float = THRESHOLD);
	void setParameters(vector<vector<float>>, float = THRESHOLD);// kazda klasa posiada wartosc srednia i odchylenie std
	void setParameterAs(Decision&);
	Decision(Decision&);
	Decision(){}
	void operator=(Decision&);

private:
	vector< vector<float>> m_PatternVector;
	vector<LearnData> m_LearnedData;
	float m_minThreshold;
	string m_label;
	float getFunction(float x, float medium, float stdDev);
};

#endif