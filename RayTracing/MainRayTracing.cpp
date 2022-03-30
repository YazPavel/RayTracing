#include <iostream>

#include "Params.h"
#include "PhotonicBall.h"
#include "PhaseCalculationFullRTr.h"
#include "Result.h"




int main()
{
	// Read parameters from file parameters.txt
	Params parameters;
	std::cout << parameters;
	
	// Read & prepare  PB structure data.
	PhotonicBall Geom(parameters);

	//Prepare Ray-Tracing Physics
	PhaseCalculationFullRTr calculRT(parameters, Geom.GetPixelSize());

	//Prepare results
	Result results(parameters.GetScatangle());

	//Rotate PB and run Ray-Tracing 
	for (int i = 0; i < parameters.Get_rotationN()-1; i++) {
		results.AddScatAmplitude(calculRT.CalculateScatAmplitude(parameters, Geom)); // calculate ray tracing and store the result 	
		Geom.random_rotation(); //rotate PB
		std::cout << "Rotation " << i + 1 << " out of " << parameters.Get_rotationN() << std::endl;
	}
	results.AddScatAmplitude(calculRT.CalculateScatAmplitude(parameters, Geom));
	std::cout << "Rotation " << parameters.Get_rotationN() << " out of " << parameters.Get_rotationN() << std::endl;

	results.SaveScatAmplitudeAllRotations("outputAllAmplitudes.txt");
	results.SaveScatCrossSectAllRotations("outputAllCrSect.txt");
	results.SaveScatCrossSectMean("outputMeanCrSect.txt");
}
