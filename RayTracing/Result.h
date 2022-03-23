#pragma once
#include<vector>
#include<complex>
#include<string>
#include<fstream>
#include <iostream>

using std::vector;
using std::complex;
using std::string;
using std::ofstream;

class Result {
	// this class is to keep the results and make simple data post-treatment
private:
	vector<vector<complex<double>>> scat_amplitude_angle_set;
	vector<vector<double>> scat_cross_section_angle_set;
	vector<double> scat_angle;
	vector<double> mean_cross;
	void CalculateAllCrossSections();

	void CalculateMeanCrossSection();
public:
	Result(const vector<double>& scat_angle_);
	void AddScatAmplitude(vector<complex<double>> scat_amplitude_angle);


	void SaveScatAmplitudeAllRotations(string path);

	void SaveScatCrossSectAllRotations(string path);

	void SaveScatCrossSectMean(string path);
};

