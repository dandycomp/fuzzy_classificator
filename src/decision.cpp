#include "Decision.h"
#include <math.h>

void Decision::setParameters(vector<vector<float>> vec, float threshold)
{
	m_PatternVector = vec;
	m_minThreshold = threshold;
}

void Decision::setParameters(vector<LearnData> learnData, float threshold)
{
	m_LearnedData = learnData;
	m_PatternVector.clear();
	vector<LearnData>::iterator it;
	for (it = learnData.begin(); it != learnData.end(); ++it)
	{
		m_PatternVector.push_back((*it).getParameters());
	}
	m_minThreshold = threshold;
}


float Decision::getFunction(float x, float medium, float stdDev)
{
	//float val = exp(- pow((x - medium),2) / (2.0 * pow(stdDev,2) ));
	return exp(-pow((x - medium), 2) / (2.0 * pow(stdDev, 2)));
	//cout << " Probability = " << val << endl;
	//return val > m_minThreshold ? true : false;
}

bool Decision::clasify(vector<float> parameters)
{
	// temp function
	vector<float> pattern = m_PatternVector[0];
	
	for (int i = 0; i < 3; i++){
		//if (abs(parameters[i] - pattern[i]) > pattern[i + 3])
		//	return false;
		float mediumPattern = pattern[i];
		float devPattern = pattern[i + 3];
		float medOfImageToClasify = parameters[i];
		bool decis = getFunction(medOfImageToClasify, mediumPattern, devPattern);
		
		if (!decis)
			return false;
	}
	return true;
}

string Decision::clasifyWithLabels(vector<float> parameters)
{
	float max_probability = 0;
	string label_of_maxProbability = "";
	for (int i = 0; i < m_LearnedData.size(); i++)
	{
		LearnData lrnData; 
		lrnData.setParameterAs(m_LearnedData[i]);
		vector<float> pattern = lrnData.getParameters();
		bool decis = false;
		float common_probability = 1.0;
		for (int i = 0; i < 3; i++){
			//if (abs(parameters[i] - pattern[i]) > pattern[i + 3])
			//	return false;
			float mediumPattern = pattern[i];
			float devPattern = pattern[i + 3];
			float medOfImageToClasify = parameters[i];
			float probability;
			probability = getFunction(medOfImageToClasify, mediumPattern, devPattern);
			decis = probability > m_minThreshold ? true : false;
			common_probability = common_probability < probability ? common_probability : probability;
			cout << " Return " << decis << endl;
			if (!decis)
				break;
		}
		if (decis && common_probability > max_probability){
				max_probability = common_probability;
				label_of_maxProbability = lrnData.m_label;
		}
	}
	if (label_of_maxProbability != "")
		return label_of_maxProbability;
	else
		return "No object";
}

Decision :: Decision(Decision& dc){
	m_PatternVector = dc.m_PatternVector;
	m_LearnedData = dc.m_LearnedData;
	m_minThreshold = dc.m_minThreshold;
	m_label = dc.m_label;
}

void Decision::operator= (Decision& dc){
	m_PatternVector = dc.m_PatternVector;
	m_LearnedData = dc.m_LearnedData;
	m_minThreshold = dc.m_minThreshold;
	m_label = dc.m_label;
}

void Decision::setParameterAs(Decision& dc){
	m_PatternVector = dc.m_PatternVector;
	m_LearnedData = dc.m_LearnedData;
	m_minThreshold = dc.m_minThreshold;
	m_label = dc.m_label;
}