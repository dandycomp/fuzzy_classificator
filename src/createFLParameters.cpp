#include "createFLParameters.h"

void LearnData::setParameters(string label, vector<vector<float>> paramVect)
{
	m_label = label;
	m_all_parameters = paramVect;
	generatesFinalParameteres();
}

void LearnData::setParameters(vector<vector<float>> paramVect)
{
	std::cout << " Write label: " << std::endl;
	char c = cin.get();
	string label = to_string(c);
	setParameters(label, paramVect);
}


void LearnData::generatesFinalParameteres()
{
	if (!m_all_parameters.data())
		cout << " No input data " << endl;

	int sizeOfParameters = m_all_parameters.size();

	float med_sumB, med_sumG, med_sumR;
		med_sumB = med_sumG = med_sumR = 0.0;
	float stdev_sumR, stdev_sumG, stdev_sumB;
	stdev_sumR = stdev_sumG = stdev_sumB = 0.0;

		for (int i = 0; i < sizeOfParameters; i++)
	{
		med_sumB += m_all_parameters[i][0];
		med_sumG += m_all_parameters[i][1];
		med_sumR += m_all_parameters[i][2];

		stdev_sumB += m_all_parameters[i][3];
		stdev_sumG += m_all_parameters[i][4];
		stdev_sumR += m_all_parameters[i][5];
	}

		float  blue_median_of_medians = med_sumB / (float)sizeOfParameters;
		float green_median_of_medians = med_sumG / (float)sizeOfParameters;
		float   red_median_of_medians = med_sumR / (float)sizeOfParameters;

		float  blue_median_of_deviation = stdev_sumB / (float)sizeOfParameters;
		float green_median_of_deviation = stdev_sumG / (float)sizeOfParameters;
		float   red_median_of_deviation = stdev_sumR / (float)sizeOfParameters;

		m_final_parameters.clear();
		m_final_parameters.push_back( blue_median_of_medians  );
		m_final_parameters.push_back(green_median_of_medians  );
		m_final_parameters.push_back(red_median_of_medians    );
		m_final_parameters.push_back(blue_median_of_deviation );
		m_final_parameters.push_back(green_median_of_deviation);
		m_final_parameters.push_back(red_median_of_deviation  );

}

void LearnData::info()
{
	if (!m_final_parameters.data()){
		cout << " Wrong vector of final data " << endl;
		cin.get();
	}

	cout << "\n\n\n****** Generatet common parameters: ******" << endl;
		cout << " Medium B = " << m_final_parameters[0] << ", G = " <<
		m_final_parameters[1] << ", R = " << m_final_parameters[2] << endl;

		cout << " Deviation B = " << m_final_parameters[3] << ", G = " <<
		m_final_parameters[4] << ", R = " << m_final_parameters[5] << endl;
	cout << "******************************************" << endl;
}

void LearnData::setParameterAs(LearnData& data){
	m_final_parameters = data.m_final_parameters;
	m_label = data.m_label;
}