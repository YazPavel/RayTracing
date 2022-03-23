#include "GeneralFun.h"


Eigen::Matrix3d GenFunc::rotationMatrix(const double& angle, const std::vector<double>& axis) {
	Eigen::Matrix3d m;
	m << cos(angle) + axis[0] * axis[0] * (1 - cos(angle)), axis[0] * axis[1] * (1 - cos(angle)) - axis[2] * sin(angle), axis[0] * axis[2] * (1 - cos(angle)) + axis[1] * sin(angle),
		axis[0] * axis[1] * (1 - cos(angle)) + axis[2] * sin(angle), cos(angle) + axis[1] * axis[1] * (1 - cos(angle)), axis[2] * axis[1] * (1 - cos(angle)) - axis[0] * sin(angle),
		axis[0] * axis[2] * (1 - cos(angle)) - axis[1] * sin(angle), axis[2] * axis[1] * (1 - cos(angle)) + axis[0] * sin(angle), cos(angle) + axis[2] * axis[2] * (1 - cos(angle));
	return m;
}

std::vector<double> GenFunc::linspace(const double& start, const double&  finish, const int& step_num) {
	std::vector<double> linspaced(step_num);
	if (step_num == 0) { return linspaced; }
	if (step_num == 1) {
		linspaced[0] = start;
		return linspaced;
	}
	double delta = (finish - start) / (step_num - 1);
	for (int i = 0; i < step_num - 1; ++i)
	{
		linspaced[i] = (start + delta * i);
	}
	linspaced[step_num - 1] = finish;
	return linspaced;
}