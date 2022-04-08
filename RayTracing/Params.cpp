#include "Params.h"
#include "GeneralFun.h"
#include <string>
#include <sstream>

template <typename T>
void Params::readline(std::ifstream& input, T& var) {
	std::string line;
	std::getline(input, line);
	std::stringstream ss;
	ss.str(line);
	ss >>  var;
}


	Params::Params() {
		const double pi = 3.14159265358979323846;
		std::ifstream input("parameters.txt");
		//std::string line;
		if (input) {
			readline(input, structure_file);
			readline(input, np);
			readline(input, nm);
			readline(input, wavelength);
			readline(input, lengthscale);
			readline(input, min_angle);
			readline(input, max_angle);
			readline(input, rotationN);
			readline(input, resolution);
			readline(input, angleN);

		}
		input.close();
		wavevector_diel = 2 * pi / wavelength * np;
		wavevector_med = 2 * pi / wavelength * nm;
		scatangle = GenFunc::linspace(0, pi, angleN);
		Rayleigh_prefactor = wavevector_med * wavevector_med / 4 / pi * (np*np / nm / nm - 1);


	}

std::string Params::GetStructureFile() const { return structure_file; };
double Params::GetLengthScale() const { return lengthscale; };
int Params::GetResolution() const { return resolution; };
std::vector<double> Params::GetScatangle() const { return scatangle; };
double Params::Get_wavevector_diel() const{ return wavevector_diel; };
double Params::Get_wavevector_med() const{ return wavevector_med; };
double Params::Get_Rayleigh_prefactor() const{ return Rayleigh_prefactor; };
int Params::Get_angleN() const { return angleN; };
int Params::Get_rotationN() const { return rotationN; };

 std::ostream&  operator << (std::ostream& output, Params const & param) {
		using std::endl;
		output << "dielctric refractive index = " << param.np << endl;
		output << "media refractive index = " << param.nm << endl;
		output << "wavelength = " << param.wavelength << endl;
		output << "lengthscale = " << param.lengthscale << endl;
		return output;
}