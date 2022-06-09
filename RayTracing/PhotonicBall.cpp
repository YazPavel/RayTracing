#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
#include "Eigen/Eigen/Dense"
#include "GeneralFun.h"
#include "PhotonicBall.h"
#include "Params.h"

using std::istream;
using std::ostream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
const double pi = 3.14159265358979323846;

istream&  operator>>(istream& input, NanoParticle& NP) {
		input >> NP.radius >> NP.coord(0) >> NP.coord(1) >> NP.coord(2);
		return input;
}

ostream&  operator<<(ostream& output, NanoParticle& NP) {
		output << NP.radius << " " << NP.coord(0) << NP.coord(1) << " " << NP.coord(2) << endl;
		return output;
}




	void PhotonicBall::calculateMean() {
		double res_rad = 0;
		Eigen::Vector3d res_coord = { 0, 0, 0 };
		int count = 0;
		for (const auto& NP : coordlist) {
			res_rad += NP.radius;
			res_coord += NP.coord;
			count++;
		}
		if (count) {
			radiusNP_Mean = res_rad / count;
			PB_center = res_coord / count;
		}
	}

	void PhotonicBall::normalise() {
		PhotonicBall::calculateMean();
		for (auto& NP : coordlist) {
			// makes average radius equal to 1 und put center to 0 0 0
			NP.coord -= PB_center;
			NP.coord /= radiusNP_Mean;
			NP.radius /= radiusNP_Mean;
		}
		PB_center = { 0, 0, 0 };
		radiusNP_Mean = 1.0;
	}
	void PhotonicBall::rescale(const double& scale) {
		for (auto& NP : coordlist) {
			// makes average radius equal to 1 und put center to 0 0 0
			NP.coord *= scale;

			NP.radius *= scale;
		}
		PB_center *= scale;
		radiusNP_Mean *= scale;
	}

	double PhotonicBall::Feret_radius() {
		PhotonicBall::calculateMean();
		double res = 0;
		for (const auto& NP : coordlist) {
			res = std::max(res, (NP.coord - PB_center).norm());
		}
		return res + radiusNP_Mean;
	}

	void PhotonicBall::SetResolution(int resolution_) {
		res_x = resolution_;
		res_y = resolution_;
		res_z = resolution_;
		mesh_x = GenFunc::linspace(-radiusPB * 1.00, radiusPB*1.00, res_x);
		voxelSize = mesh_x[1] - mesh_x[0];
	}

	PhotonicBall::PhotonicBall(const string& structure_file, const double& NPradius) {
		// data file consists of lines: R X Y Z. The output is normalised to have <R>=1
		ifstream input(structure_file);
		if (input) {
			NanoParticle NP;
			N = 0;
			while (input >> NP) {
				coordlist.push_back(NP);
				N++;
			}
			cout << "Nanoparticle positions are read" << endl;
		}

		normalise(); // move particle to 0 and put <R_NP>=1
		rescale(NPradius); //  put <R_NP>=Rtarget
		radiusPB = Feret_radius();
	}

	PhotonicBall::PhotonicBall(const string& structure_file, const double& NPradius, const int& resolution_) {
		// data file consists of lines: R X Y Z. The output is normalised to have <R>=1
		ifstream input(structure_file);
		if (input) {
			NanoParticle NP;
			N = 0;
			while (input >> NP) {
				coordlist.push_back(NP);
				N++;
			}
			cout << "Nanoparticle positions are read" << endl;
			cout << "Number of nanoparticles is " << N << endl;
		}

		normalise(); // move particle to 0 and put <R_NP>=1
		rescale(NPradius); //  put <R_NP>=Rtarget
		radiusPB = Feret_radius();
		SetResolution(resolution_);
		createMask_fast(resolution_);
	}

	PhotonicBall::PhotonicBall(const Params& parameters) {
		// data file consists of lines: R X Y Z. The output is normalised to have <R>=1
		ifstream input(parameters.GetStructureFile());
		if (input) {
			NanoParticle NP;
			N = 0;
			while (input >> NP) {
				coordlist.push_back(NP);
				N++;
			}
			cout << "Nanoparticle positions are read" << endl;
			cout << "Number of nanoparticles is " << N << endl;
		}

		normalise(); // move particle to 0 and put <R_NP>=1
		rescale(parameters.GetLengthScale()); //  put <R_NP>=Rtarget
		radiusPB = Feret_radius();
		createMask_fast(parameters.GetResolution());
	}

	void PhotonicBall::random_rotation_no_mask() {
		srand(time(0));
		double u = (double)rand() / RAND_MAX;
		double v = (double)rand() / RAND_MAX;
		double theta_r = 2 * pi * u;
		double phi_r = acos(2 * v - 1);
		std::vector<double> ax1 = { 0, 0, 1 };
		std::vector<double> ax2 = { 0, 1, 0 };
		Eigen::Matrix3d rot_m = GenFunc::rotationMatrix(theta_r, ax1)* GenFunc::rotationMatrix(phi_r, ax2);
		for (NanoParticle& NP : coordlist) {
			NP.coord = rot_m * NP.coord;
		}
	}




	void PhotonicBall::random_rotation(const int& resolution_) {
		srand(time(0));
		double u = (double)rand() / RAND_MAX;
		double v = (double)rand() / RAND_MAX;
		double theta_r = 2 * pi * u;
		double phi_r = acos(2 * v - 1);
		std::vector<double> ax1 = { 0, 0, 1 };
		std::vector<double> ax2 = { 0, 1, 0 };
		Eigen::Matrix3d rot_m = GenFunc::rotationMatrix(theta_r, ax1)* GenFunc::rotationMatrix(phi_r, ax2);
		for (NanoParticle& NP : coordlist) {
			NP.coord = rot_m * NP.coord;
		}
		createMask_fast(resolution_);
	}

	void PhotonicBall::random_rotation()  {
		srand(time(0));
		double u = (double)rand() / RAND_MAX;
		double v = (double)rand() / RAND_MAX;
		double theta_r = 2 * pi * u;
		double phi_r = acos(2 * v - 1);
		std::vector<double> ax1 = { 0, 0, 1 };
		std::vector<double> ax2 = { 0, 1, 0 };
		Eigen::Matrix3d rot_m = GenFunc::rotationMatrix(theta_r, ax1)* GenFunc::rotationMatrix(phi_r, ax2);
		for (NanoParticle& NP : coordlist) {
			NP.coord = rot_m * NP.coord;
		}
		createMask_fast(res_x);
	}


	bool PhotonicBall::check_pixel_insidePB(const Eigen::Vector3d& point) {
		for (const auto& NP : coordlist) {
			if ((NP.coord - point).norm() < NP.radius) {
				return true;
			}
		}
		return false;
	}

	void PhotonicBall::createMask_fast(const int& resolution_) {
		SetResolution(resolution_);
		std::vector<std::vector<std::vector<bool>>> Mask_(res_x, std::vector<std::vector<bool>>(res_x, std::vector<bool>(res_x, false)));
		
		Eigen::Vector3d v(1,1,1);
		for (const auto& NP : coordlist) {
			Eigen::Vector3d maxcoord = (NP.coord + (NP.radius-mesh_x[0])*v)/voxelSize;
			Eigen::Vector3d mincoord = (NP.coord - (NP.radius + mesh_x[0])*v)/voxelSize;
			std::vector<int> maxID(3);
			std::vector<int> minID(3);
			for (int i = 0; i < 3; i++) {
				maxID[i] = ((int)maxcoord[i]) + 1;
				if (maxID[i] > res_x -1) { maxID[i] = res_x -1; }
			}
			for (int i = 0; i < 3; i++) {
				minID[i] = ((int)mincoord[i]) - 1;
				if (minID[i] < 0) { minID[i] = 0; }
			}

			for (int i = minID[0]; i <= maxID[0]; i++) {
				for (int j = minID[1]; j <= maxID[1]; j++) {
					for (int k = minID[2]; k <= maxID[2]; k++) {
						Eigen::Vector3d point;
						point << mesh_x[i], mesh_x[j], mesh_x[k];
						if ((NP.coord - point).norm() < NP.radius) {
							Mask_[i][j][k] = true;
						}
					}
				}
			}

		}
		Mask = Mask_;
	}

	
	const std::vector<std::vector<std::vector<bool>>>& PhotonicBall::GetMask() const{
		return Mask;
	}
	double PhotonicBall::GetPixelSize() const{
		return voxelSize;
	}
	double PhotonicBall::GetFeret_radius() const {
		return radiusPB;
	}