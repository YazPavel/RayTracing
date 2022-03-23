#pragma once
#include <vector>
#include <complex> 
#include "Params.h"
#include "Geometry.h"

class Physics {
public:
	virtual std::vector<std::complex<double>> CalculateScatAmplitude(const Params& parameters, const Geometry& Geom) = 0;

};

