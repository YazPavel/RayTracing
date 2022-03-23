#include "Params.h"
#include "GeneralFun.h"


	Params::Params() {
		std::ifstream input("parameters.txt");
		std::string line;
		if (input) {
			input >> structure_file;
			input >> np >> line;
			input >> nm >> line;
			input >> wavelength >> line;
			input >> lengthscale >> line;
			input >> min_angle >> line;
			input >> max_angle >> line;
			input >> rotationN >> line;
			input >> resolution >> line;
			input >> angleN >> line;
		}
		wavevector_diel = 2 * M_PI / wavelength * np;
		wavevector_med = 2 * M_PI / wavelength * nm;
		scatangle = GenFunc::linspace(0, M_PI, angleN);
		Rayleigh_prefactor = wavevector_med * wavevector_med / 4 / M_PI * (np*np / nm / nm - 1);


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