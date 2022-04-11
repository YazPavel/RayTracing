#pragma once
#include <map>
#include <complex> 
#include "Params.h"
#include "Physics.h"

class PhaseCalculationFullRTr: public Physics {
	//This class is to realise full ray tracing
private:
	std::vector<std::vector<std::vector<std::complex<double>>>> phase_tot; // incoming ray-tracing inside the material structure
	std::vector<std::vector<std::vector<std::complex<double>>>> dict_angle_vs_phase_output; // AngleID to 2D Image (y-z) of outcoming phases; output does not depend on the material structure
	int res_x;
	int res_y;
	int res_z;
	void CalculateIncomePhase(const Params& parameters, const std::vector<std::vector<std::vector<bool>>>& Mask, const double& delta);
	void CalculateOutputField(const Params& parameters, const  double& delta);
	std::vector<std::complex<double>> CalculateFarField(const Params& parameters, const std::vector<std::vector<std::vector<bool>>>& Mask, const double&  delta);

public:
	PhaseCalculationFullRTr(const Params& parameters, const Geometry& Geom);
	std::vector<std::complex<double>> CalculateScatAmplitude(const Params& parameters, const Geometry& Geom) override;

	PhaseCalculationFullRTr(const Params& parameters, const std::vector<std::vector<std::vector<bool>>>& Mask, const double& delta);
	std::vector<std::complex<double>> CalculateScatAmplitude(const Params& parameters, const std::vector<std::vector<std::vector<bool>>>& Mask, const double&  delta);
	
};

