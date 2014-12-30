#ifndef switcher
#define switcher

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include "getRoi.h"
#include "FLParameters.h"
#include "createFLParameters.h"

//#include <boost\filesystem.hpp>
#include <fstream>

using namespace std;
using namespace cv;

stringstream ss;

void save(LearnData data)
{
	boost::archive::text_oarchive oa(ss);
	oa << data;
}

LearnData load()
{
	boost::archive::text_iarchive ia(ss);
	LearnData data;
	ia >> data;
	vector<float> param = data.getParameters();
	cout << " Loaded: \n label = " << data.m_label << " parameters size = " << param.size() << " 1 element = " << param[0] << endl;
	return data;
}

LearnData load(char* bufor)
{
	stringstream ss_(bufor);
	boost::archive::text_iarchive ia(ss_);
	LearnData data;
	ia >> data;
	vector<float> param = data.getParameters();
	cout << " Loaded: \n label = " << data.m_label << " parameters size = " << param.size() << " 1 element = " << param[0] << endl;
	return data;
}

int switcherFunction(string imagename, bool define, bool clasify)
{
	if (define == 0 && clasify == 0)
	{
		cout << "Nothing to do. Choose define or clasify" << endl;
		return 1;
	}

	Mat img = imread(imagename);
	if (!img.data)
	{
		cout << " \n Can't open " << imagename << endl;
		return 1;
	}
	if (define)
	{
		GetRoi create_samples(img);
		create_samples.run();
		vector<vector<float>> parameters = create_samples.getParameters();

		LearnData learnData;
		learnData.setParameters("zielone_jablko", parameters);
		learnData.info();

		save(learnData);
		fstream filewrite;
		filewrite.open("zielone_jablko.txt", ios::in | ios::out | ios::app);
		filewrite.write(ss.str().c_str(), ss.str().length());
		filewrite.close();
	}
	if (clasify)
	{
		vector<string> labels;
		labels.push_back("cytryna");
		labels.push_back("pomarancza");
		labels.push_back("sliwa");
		labels.push_back("jabko");
		labels.push_back("zielone_jablko");
		labels.push_back("wisnia");

		vector<LearnData>  outpLearnParams;
		while (labels.size() != 0)
		{
			string temp = labels.back();
			string filename = "labels\\" + temp + ".txt";
			fstream fileRead;
			char bufor[1024];
			fileRead.open(filename, ios::in);

			if (!fileRead.is_open())
			{
				cout << " \n Can't open " << filename << endl;
				return 1;
			}
			fileRead.read(bufor, 1024);
			fileRead.close();
			LearnData newLearnedData = load(bufor);
			outpLearnParams.push_back(newLearnedData);
			labels.pop_back();
		}

		GetRoi detection(img, outpLearnParams);
		detection.run();
	}
	return 0;
}
#endif
