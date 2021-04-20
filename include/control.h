#ifndef CONTROL_H_
#define CONTROL_H_
	
#include <vector>
#include <string>
#include "plasma_structures.h"
	
#ifdef __cplusplus
extern "C" {
#endif

struct module_struct_wrap
{
	const char* dreicer_formula;
	bool dreicer_toroidicity;
	const char* avalanche_formula;
	bool avalanche_toroidicity;
	bool hdf5_output;
	double warning_percentage_limit;
	double rho_edge_calculation_limit;
	
};

struct module_struct {
	std::string dreicer_formula;
	bool dreicer_toroidicity;
	std::string avalanche_formula;
	bool avalanche_toroidicity;
	bool hdf5_output;
	double warning_percentage_limit;
	double rho_edge_calculation_limit;
	
};

double advance_runaway_population(const plasma_local &plasma_local, double timestep, double inv_asp_ratio, double rho_tor_norm, module_struct const &modules, double *rate_values);
	
#ifdef __cplusplus
}
#endif

int list_parameter_settings(module_struct const &modules);

#endif /* CONTROL_H_ */

