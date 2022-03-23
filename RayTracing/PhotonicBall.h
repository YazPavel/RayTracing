#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
#include "Eigen/Eigen/Dense"
#include "GeneralFun.h"
#include "Geometry.h"
#include "Params.h"

class NanoParticle {
private:
	double radius;
	Eigen::Vector3d coord;
	friend class PhotonicBall;
	friend std::istream&  operator>>(std::istream& input, NanoParticle& NP);
	friend std::ostream&  operator<<(std::ostream& output, NanoParticle& NP);
};



class PhotonicBall: public Geometry {	
private:
	std::vector<NanoParticle> coordlist;
	int N; //aggregation number
	double radiusPB = 0;
	Eigen::Vector3d PB_center;
	double radiusNP_Mean = 0;
	int resolution = 1;
	std::vector<std::vector<std::vector<bool>>> Mask;
	std::vector<double> mesh_x;
	double delta;
	void calculateMean();
	void normalise();
	void rescale(const double& scale);
	double Feret_radius();
	void random_rotation_no_mask();
	bool check_pixel_insidePB(const Eigen::Vector3d& point);
	void createMask(const int& resolution_);
	void createMask_fast(const int& resolution_);
	void SetResolution(const int& resolution_);
public:
	PhotonicBall(const Params& parameters);
	PhotonicBall(const std::string& structure_file, const double& NPradius);
	PhotonicBall(const std::string& structure_file, const double& NPradius, const int& resolution_);
	void random_rotation(const int& resolution_);
	void random_rotation() override;
	double GetFeret_radius() const;

	const std::vector<std::vector<std::vector<bool>>>& GetMask() const override;
	double GetPixelSize() const override;
};