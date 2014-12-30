#ifndef decision
#define decision
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <vector>
#include "createFLParameters.h"

using namespace cv;
using namespace std;

class Decision{
public:
	bool clasify(vector<float> parameters);//for 1 object
	string clasifyWithLabels(vector<float> parameters);//for more object, return label
	void setParameters(vector<LearnData>, float = 0.7);
	void setParameters(vector<vector<float>>, float = 0.7);// kazda klasa posiada wartosc srednia i odchylenie std
	void setParameterAs(Decision&);
	Decision(Decision&);
	Decision(){}
	void operator=(Decision&);

private:
	vector< vector<float>> m_PatternVector;
	vector<LearnData> m_LearnedData;
	float m_minThreshold;
	string m_label;
	bool getFunction(float x, float medium, float stdDev);
};

#endif