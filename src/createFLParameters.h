#ifndef learningParameters
#define learningParameters

#include <string>
#include <vector>
#include <iostream>

using namespace std;
#include <boost\serialization\vector.hpp>
#include <boost\serialization\string.hpp>
#include <boost\archive\text_oarchive.hpp> 
#include <boost\archive\text_iarchive.hpp> 
#include <sstream> 

class LearnData{
	friend class boost::serialization::access;
	vector<vector<float>> m_all_parameters;
	vector<float> m_final_parameters;
	void generatesFinalParameteres();

public:
	void setParameters(string, vector<vector<float>>);
	void setParameters(vector<vector<float>>);
	void info();
	string m_label;
	vector<float> getParameters(){ return m_final_parameters; }
	void setParameterAs(LearnData&);

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_label;
		ar & m_final_parameters;
		ar & m_all_parameters;
	}


	/*
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		// note, version is always the latest when saving
		ar  & m_label;
		ar  & getParameters;
	}
	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		if (version > 0)
			ar & driver_name;
		ar  & stops;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()	
	*/
};

//BOOST_CLASS_VERSION(LearnData, 1)

#endif