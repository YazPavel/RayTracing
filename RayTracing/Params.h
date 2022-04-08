#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>


struct Params {
private:
	std::string structure_file;
	double np; // dielectric refractive index
	double nm; // media refractive index
	double wavelength;
	double lengthscale;
	double min_angle;
	double max_angle;
	int rotationN;
	int resolution;
	int angleN;
	std::vector<double> scatangle;
	double wavevector_diel;
	double wavevector_med;
	double Rayleigh_prefactor;
	template <typename T>
	void readline(std::ifstream& input, T& var);
public:
	Params();
	std::string GetStructureFile() const;
	double GetLengthScale() const;
	int GetResolution() const;
	std::vector<double> GetScatangle() const;
	double Get_wavevector_diel() const;
	double Get_wavevector_med() const;
	double Get_Rayleigh_prefactor() const;
	int Get_angleN() const;
	int Get_rotationN() const;
	friend std::ostream&  operator << (std::ostream& output, Params const& param);
};
