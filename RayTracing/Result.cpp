#include<vector>
#include<complex>
#include<string>
#include<fstream>
#include <iostream>
#include"Result.h"

using std::vector;
using std::complex;
using std::string;
using std::endl;
using std::ofstream;






	void Result::CalculateAllCrossSections() {
		for (size_t count_turn = 0; count_turn < scat_amplitude_angle_set.size(); count_turn++) {
			vector<double> temp(scat_angle.size());
			for (size_t count = 0; count < scat_angle.size(); count++) {
				temp[count] = norm(scat_amplitude_angle_set[count_turn][count]);
			}
			scat_cross_section_angle_set.push_back(temp);
		}
	}

	void Result::CalculateMeanCrossSection() {
		vector<double> mean_cross(scat_angle.size(), 0);

		for (size_t count = 0; count < scat_angle.size(); count++) {
			for (size_t count_turn = 0; count_turn < scat_amplitude_angle_set.size(); count_turn++) {
				mean_cross[count] += norm(scat_amplitude_angle_set[count_turn][count]);
			}
			mean_cross[count] /= scat_amplitude_angle_set.size();
		}
		this->mean_cross = mean_cross;
	}

	Result::Result(const vector<double>& scat_angle_) {
		scat_angle = scat_angle_;
	}
	void Result::AddScatAmplitude(vector<complex<double>> scat_amplitude_angle) {
		scat_amplitude_angle_set.push_back(scat_amplitude_angle);
	}


	void Result::SaveScatAmplitudeAllRotations(string path) {
		ofstream output(path);
		output << "Scattering Amplitude: Angle, Real Part, Imaginary Part" << endl;
		for (size_t count_turn = 0; count_turn < scat_amplitude_angle_set.size(); count_turn++) {
			output << "Random rotation" << endl;
			for (size_t count = 0; count < scat_angle.size(); count++) {
				output << scat_angle[count] << " " << scat_amplitude_angle_set[count_turn][count].real() << " " << scat_amplitude_angle_set[count_turn][count].imag() << endl;
			}
		}

	}

	void Result::SaveScatCrossSectAllRotations(string path) {
		CalculateAllCrossSections();
		ofstream output(path);
		output << "Scattering Cross-Section: Angle, Cross-section" << endl;
		for (size_t count_turn = 0; count_turn < scat_cross_section_angle_set.size(); count_turn++) {
			output << "Random rotation" << endl;
			for (size_t count = 0; count < scat_angle.size(); count++) {
				output << scat_angle[count] << " " << scat_cross_section_angle_set[count_turn][count] << endl;
			}
		}
	}

	void Result::SaveScatCrossSectMean(string path) {
		CalculateMeanCrossSection();
		ofstream output(path);
		output << "Mean Scattering Cross-Section: Angle, Cross-section" << endl;
		for (size_t count = 0; count < scat_angle.size(); count++) {
			output << scat_angle[count] << " " << mean_cross[count] << endl;
		}

	}


