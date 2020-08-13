#ifndef CONTROL_H_
#define CONTROL_H_
	
#include <vector>
#include <string>

// cell structure	


struct module_struct {
	std::string dreicer_formula;
	bool dreicer_toroidicity;
	std::string avalanche_formula;
	bool avalanche_toroidicity;
	bool hdf5_output;
	double warning_percentage_limit;
	double rho_edge_calculation_limit;
	
};

double advance_runaway_population(double electron_density, double rundensity_before, double electron_temperature,
		double effective_charge, double electric_field, double magnetic_field, double timestep, double inv_asp_ratio, double rho_tor_norm, module_struct const &modules, double *rate_values);

int list_parameter_settings(module_struct const &modules);
		
#endif /* CONTROL_H_ */
