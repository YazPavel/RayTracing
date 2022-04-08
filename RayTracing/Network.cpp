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
			edge_list.push_back(rod);
			N_edges++;
		}
		std::cout << "Rod positions are read" << std::endl;
		std::cout << "Number of rods is " << N_edges << std::endl;
	}
}

const std::vector<std::vector<std::vector<bool>>>& Network::GetMask() const {
	return Mask;
}
double Network::GetPixelSize() const {
	return voxel_size;
}