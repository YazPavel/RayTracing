#pragma once
#include <vector>
#include "Eigen/Eigen/Dense"


namespace GenFunc {
Eigen::Matrix3d rotationMatrix(const double& angle, const std::vector<double>& axis);

std::vector<double> linspace(const double& start, const double&  finish, const int& step_num);
}
