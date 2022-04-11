#include <iostream>
#include <fstream>
#include "Network.h"

std::istream& operator>>(std::istream& input, Rod& rod) {
	input >>  rod.vertex1[0] >> rod.vertex1[1] >> rod.vertex1[2] >> rod.vertex2[0] >> rod.vertex2[1] >> rod.vertex2[2];
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
	createMask(parameters.GetResolution());
}

const std::vector<std::vector<std::vector<bool>>>& Network::GetMask() const {
	return Mask;
}
double Network::GetPixelSize() const {
	return voxel_size;
}

void Network::calculateMean() {
	double res_rad = 0;
	Eigen::Vector3d res_coord = { 0, 0, 0 };
	int count = 0;
	for (const auto& _rod : rod_list) {
		res_rad += _rod.radius;
		res_coord += _rod.vertex1;
		res_coord += _rod.vertex2;
		count+=2;
	}
	if (count) {
		length_mean = res_rad / count;
		network_center = res_coord / count;
	}
}

void Network::normalise() {
	
};
void Network::rescale(double scale) {

};
void Network::createMask(const int& resolution_) {

};
void Network::SetResolution(const int& resolution_) {

};