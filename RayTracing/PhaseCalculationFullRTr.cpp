#include<vector>
#include "PhaseCalculationFullRTr.h"
#include "Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

void PhaseCalculationFullRTr::CalculateIncomePhase(const Params& parameters, const vector<vector<vector<bool>>>& Mask, const double& delta) {
	vector<vector<vector<complex<double>>>> phase_tot_(res_x, vector<vector<complex<double>>>(res_y, vector<complex<double>>(res_z, 1)));
		complex<double> shift_diel = exp(1i*parameters.Get_wavevector_diel()*delta);
		complex<double> shift_med = exp(1i*parameters.Get_wavevector_med()*delta);
		for (int i = 0; i < res_x; i++) {
			for (int j = 0; j < res_y; j++) {
				for (int k = 1; k < res_z; k++) {
					if (Mask[i][j][k]) {
						phase_tot_[i][j][k] = phase_tot_[i][j][k - 1] * shift_diel;

					}
					else {
						phase_tot_[i][j][k] = phase_tot_[i][j][k - 1] * shift_med;
					}
					
				}
			}
		}
		phase_tot = phase_tot_;
	}
void PhaseCalculationFullRTr::CalculateOutputField(const Params& parameters, const  double& delta) {
		vector<vector<vector<complex<double>>>> phase_output(parameters.Get_angleN(), vector<vector<complex<double>>>(res_y, vector<complex<double>>(res_z, 0)));
		for (int count = 0; count < parameters.Get_angleN(); count++) {
			double angle = parameters.GetScatangle()[count];
			//Vector3d kout = { 0, parameters.wavevector_med*sin(angle), parameters.wavevector_med*cos(angle) };
			double kout_y = parameters.Get_wavevector_med()*sin(angle);
			double kout_z = parameters.Get_wavevector_med()*cos(angle);
			
				for (int j = 0; j < res_y; j++) {
					for (int k = 0; k < res_z; k++) {
						//Vector3d point = { delta*i, delta*j, delta*k };
						//phase_output[i][j][k] = exp(-1i*point.dot(kout));
						phase_output[count][j][k] = exp(-1i*(kout_y*delta*j+ kout_z*delta*k));
					}
				}
			//dict_angle_vs_phase_output[count] = phase_output;
		}
		dict_angle_vs_phase_output = phase_output;
	}

vector<complex<double>> PhaseCalculationFullRTr::CalculateFarField(const Params& parameters, const vector<vector<vector<bool>>>& Mask, const double&  delta) {
		vector<complex<double>> scat_amplitude_angle(parameters.Get_angleN());
		vector<vector<complex<double>>> phase_x_integrated(parameters.GetResolution(), vector<complex<double>>(parameters.GetResolution(), 0));
		
		for (int i = 0; i < res_x; i++) {
			for (int j = 0; j < res_y; j++) {
				for (int k = 0; k < res_z; k++) {
					if (Mask[i][j][k]) {
						phase_x_integrated[j][k] += phase_tot[i][j][k];
					}
				}
			}
		}
		
		//for (const auto& angle : parameters.scatangle) {
		for (int count = 0; count < parameters.Get_angleN(); count++) {
			double angle = parameters.GetScatangle()[count];
			//Vector3d kout = { 0, parameters.wavevector_med*sin(angle), parameters.wavevector_med*cos(angle) };
			complex<double> scat_amplitude = (0.0, 0.0);
			
				for (int j = 0; j < res_y; j++) {
					for (int k = 0; k < res_z; k++) {
						scat_amplitude += phase_x_integrated[j][k] * dict_angle_vs_phase_output[count][j][k];						
					}
				}
			
			scat_amplitude_angle[count] = scat_amplitude * delta*delta*delta*parameters.Get_Rayleigh_prefactor();
		}
		return scat_amplitude_angle;
	}

PhaseCalculationFullRTr::PhaseCalculationFullRTr(const Params& parameters, const Geometry& Geom) {
		res_x = Geom.GetResolutionX();
		res_y = Geom.GetResolutionY();
		res_z = Geom.GetResolutionZ();
		CalculateOutputField(parameters, Geom.GetPixelSize());
	}
PhaseCalculationFullRTr::PhaseCalculationFullRTr(const Params& parameters, const vector<vector<vector<bool>>>& Mask, const double& delta) {
		res_x = static_cast<int>(Mask.size());
		res_y = static_cast<int>(Mask[0].size());
		res_z = static_cast<int>(Mask[0][0].size());
		CalculateOutputField(parameters, delta);
	}
	
vector<complex<double>> PhaseCalculationFullRTr::CalculateScatAmplitude(const Params& parameters, const vector<vector<vector<bool>>>& Mask, const double&  delta) {
		CalculateIncomePhase(parameters, Mask, delta);
		return CalculateFarField(parameters, Mask, delta);
	}
vector<complex<double>> PhaseCalculationFullRTr::CalculateScatAmplitude(const Params& parameters, const Geometry& Geom) {
		CalculateIncomePhase(parameters, Geom.GetMask(), Geom.GetPixelSize());
		return CalculateFarField(parameters, Geom.GetMask(), Geom.GetPixelSize());
	}
