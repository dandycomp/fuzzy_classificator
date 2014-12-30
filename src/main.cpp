#if 0

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include <iostream>

namespace fs = boost::filesystem;

int main(int argc, char* argv[])
{
	fs::path full_path( fs::initial_path<fs::path>() );

	if ( argc > 1 )
		full_path = fs::system_complete( fs::path( argv[1] ) );
	else
		std::cout << "\nusage:   simple_ls [path]" << std::endl;

	unsigned long err_count = 0;

	if ( !fs::exists( full_path ) )
	{
		std::cout << "\nNot found: " << full_path.string() << std::endl;
		return 1;
	}

	if ( fs::is_directory( full_path ) )
	{
		std::cout << "\nIn directory: "
			<< full_path.string() << "\n\n";
		fs::directory_iterator end_iter;
		for ( fs::directory_iterator dir_itr( full_path );
			dir_itr != end_iter;
			++dir_itr )
		{
			try
			{
				 if ( fs::is_regular_file( dir_itr->status() ) )
				{
					std::cout << dir_itr->path().filename() << "\n";
					std::cout << dir_itr->path().extension() << std::endl;
				}

			}
			catch ( const std::exception & ex )
			{
				++err_count;
				std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
			}
		}
	}
	else // must be a file
	{
		std::cout << "\nFound: " << full_path.string() << "\n";    
	}
	return 0;
}
#endif
#if 0
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

int main(void)
{
	string imagename = "img/patterns/owoce.png";
	Mat img = imread(imagename);
	if (!img.data)
	{
		cout << " \n Can't open " << imagename << endl;
		return 1;
	}
#if 1
	GetRoi create_samples(img);
	create_samples.run();
	vector<vector<float>> parameters = create_samples.getParameters();

	LearnData learnData;
	learnData.setParameters("jabko", parameters);
	learnData.info();

	save(learnData);
	fstream filewrite;
	filewrite.open("filename.txt", ios::in | ios::out | ios::app);
	filewrite.write(ss.str().c_str(), ss.str().length());
	filewrite.close();
#endif
#if 0
	fstream fileRead;
	string filename = "filename.txt";
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

	vector<float> outpParams = newLearnedData.getParameters();
	vector<vector<float>> final;
	final.push_back(outpParams);
	vector<LearnData>  outpLearnParams;
	outpLearnParams.push_back(newLearnedData);

	GetRoi detection(img, outpLearnParams);
	detection.run();
#endif
	cout << " End" << endl;
	return 0;
}

#endif
#if 1
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include <iostream>
#include "switcher.h"
#include <string>

namespace fs = boost::filesystem;

bool define = false;
bool clasify = true;

int main(int argc, char* argv[])
{
	fs::path full_path(fs::initial_path<fs::path>());

	if (argc > 1)
		full_path = fs::system_complete(fs::path(argv[1]));
	else
		std::cout << "\nusage:   simple_ls [path]" << std::endl;

	unsigned long err_count = 0;

	if (!fs::exists(full_path))
	{
		std::cout << "\nNot found: " << full_path.string() << std::endl;
		return 1;
	}

	if (fs::is_directory(full_path))
	{
		std::cout << "\nIn directory: "
			<< full_path.string() << "\n\n";
		fs::directory_iterator end_iter;
		for (fs::directory_iterator dir_itr(full_path);
			dir_itr != end_iter;
			++dir_itr)
		{
			try
			{
				if (fs::is_regular_file(dir_itr->status()))
				{
					std::cout << dir_itr->path().filename() << "\n";
					//std::cout << dir_itr->path().extension() << std::endl;
					//"img/patterns/owoce.png"
					std::string imagePath = full_path.string() + dir_itr->path().filename().string();
					//int request = switcherFunction(imagePath, define, clasify);
					int request = switcherFunction(imagePath, define, clasify);
					if (request == 1)
						return 1;
				}
			}
			catch (const std::exception & ex)
			{
				++err_count;
				std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
			}
		}
	}
	else // must be a file
	{
		std::cout << "\nFound: " << full_path.string() << "\n";
	}
	return 0;
}
#endif

