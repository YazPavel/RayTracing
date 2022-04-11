#include <iostream>
#include <fstream>
#include "Network.h"
#include <math.h>

std::istream& operator>>(std::istream& input, Rod& rod) {
	input >> rod.radius >>  rod.vertex1[0] >> rod.vertex1[1] >> rod.vertex1[2] >> rod.vertex2[0] >> rod.vertex2[1] >> rod.vertex2[2];
	return input;
}


Network::Network(const Params& parameters) {
	std::ifstream input(parameters.GetStructureFile());
	if (input) {
		Rod rod;
		N_edges = 0;
		while (input >> rod) {
			rod_list.push_back(rod);
			N_edges++;
		}
		std::cout << "Rod positions are read" << std::endl;
		std::cout << "Number of rods is " << N_edges << std::endl;
	}
	normalise(); // move network to 0 and put <L>=1
	rescale(parameters.GetLengthScale()); //  put <L>=Ltarget
	SetResolution(parameters.GetResolution());
	createMask();
}

const std::vector<std::vector<std::vector<bool>>>& Network::GetMask() const {
	return Mask;
}
double Network::GetPixelSize() const {
	return voxel_size;
}
void Network::CalculateMean() {
	double res_len = 0;
	Eigen::Vector3d res_coord = { 0, 0, 0 };
	int count = 0;
	for (const auto& _rod : rod_list) {
		res_len += (_rod.vertex1 - _rod.vertex2).norm();
		res_coord += _rod.vertex1;
		res_coord += _rod.vertex2;
		count+=2;
	}
	if (count) {
		length_mean = res_len / count*2;
		network_center = res_coord / count;
	}
}

void Network::normalise() {
	Network::CalculateMean();
	for (auto& _rod : rod_list) {
		// makes average radius equal to 1 und put center to 0 0 0
		_rod.vertex1 -= network_center;
		_rod.vertex2 -= network_center;
		_rod.vertex1 /= length_mean;
		_rod.vertex2 /= length_mean;
		
		_rod.radius /= length_mean;
	}
	network_center = { 0, 0, 0 };
	length_mean = 1.0;
};
void Network::rescale(double scale) {
	for (auto& _rod : rod_list) {
		// makes average radius equal to 1 und put center to 0 0 0
		_rod.vertex1 *= scale;
		_rod.vertex2 *= scale;
		_rod.radius *= scale;
	}
	length_mean *= scale;
	network_center *= scale;
};
void Network::createMask() {

};
void Network::SetResolution(int resolution_) {
	Eigen::Vector3d min_coord = rod_list[0].vertex1;
	Eigen::Vector3d max_coord = rod_list[0].vertex1;
	for (const auto& _rod : rod_list) {
		for (int i = 0; i < 3; i++) {
			if (_rod.vertex1[i] > max_coord[i]) { max_coord[i] = _rod.vertex1[i]; }
			if (_rod.vertex1[i] < min_coord[i]) { min_coord[i] = _rod.vertex1[i]; }
		}
		for (int i = 0; i < 3; i++) {
			if (_rod.vertex2[i] > max_coord[i]) { max_coord[i] = _rod.vertex2[i]; }
			if (_rod.vertex2[i] < min_coord[i]) { min_coord[i] = _rod.vertex2[i]; }
		}
	}
	Eigen::Vector3d coord = max_coord-min_coord;
	int count=0;
	double min_box_size = coord[0];
		for (int  i= 1; i < 3; i++) {
			if (coord[i] < min_box_size) {
				count = i;
				min_box_size = coord[i];
		}
	}
		voxel_size = min_box_size / resolution_;
		res_x = int(coord[0] / voxel_size)+1;
		res_y = int(coord[1] / voxel_size)+1;
		res_z = int(coord[2] / voxel_size)+1;
		
};
	

