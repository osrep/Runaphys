#ifndef CONTROL_H_
#define CONTROL_H_
	
#include <vector>
#include <string>
#include "cell.h"
	


struct module_struct {
	std::string dreicer_formula;
	bool dreicer_toroidicity;
	std::string avalanche_formula;
	bool avalanche_toroidicity;
	bool hdf5_output;
	double warning_percentage_limit;
	double rho_edge_calculation_limit;
	
};

double advance_runaway_population(const cell &cell, double timestep, double inv_asp_ratio, double rho_tor_norm, module_struct const &modules, double *rate_values);

int list_parameter_settings(module_struct const &modules);
		
#endif /* CONTROL_H_ */
