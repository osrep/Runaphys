#include <stdexcept>
#include <iostream>
#include "control.h"
#include "critical_field.h"
#include "dreicer.h"
#include "avalanche.h"
#include "plasma_structures.h"
#ifdef ITM_CONSTANTS
    #include "cpo_utils.h"
#elif IMAS_CONSTANTS
    #include "ids_utils.h"
#endif
#include "products.h"

/*
Runafluid actor

timestep: in s

*/

double advance_runaway_population(const plasma_local &plasma_local, double timestep, double inv_asp_ratio, double rho_tor_norm, module_struct const &modules, double *rate_values){
	
	double rundensity_after = 0.0;
	double rate_dreicer = 0.0;
	double rate_avalanche = 0.0;
	double critical_field = 0.0;
	
	try {
		if (modules.dreicer_formula.empty()){
			rate_dreicer = 0;
		}else{
			rate_dreicer = dreicer_generation_rate(plasma_local.electron_density, plasma_local.electron_temperature, plasma_local.effective_charge, plasma_local.electric_field, modules);
		}
		
		if (modules.avalanche_formula.empty()){
			rate_avalanche = 0;
		}else{		
			rate_avalanche = avalanche_generation_rate(plasma_local.electron_density, plasma_local.electron_temperature, plasma_local.effective_charge, plasma_local.electric_field, plasma_local.magnetic_field, modules);
		}
			
		if (modules.dreicer_toroidicity){
			rate_dreicer *= calculate_toroidicity_dreicer(inv_asp_ratio, rho_tor_norm);
		}
			
		if (modules.avalanche_toroidicity){
			rate_avalanche *= calculate_toroidicity_avalanche(inv_asp_ratio, plasma_local.electric_field, plasma_local.electron_density, plasma_local.electron_temperature, rho_tor_norm);
		}
		
		rundensity_after = plasma_local.runaway_density + (plasma_local.electron_density*rate_dreicer + plasma_local.runaway_density*rate_avalanche) * timestep;
		
		critical_field = calculate_critical_field(plasma_local.electron_density, plasma_local.electron_temperature);
		
		rate_values[RATEID_DREICER] = rate_dreicer * plasma_local.electron_density;
		rate_values[RATEID_AVALANCHE] = rate_avalanche;
		rate_values[RATEID_CRITICAL_FIELD] = critical_field;
		rate_values[RATEID_ELECTRIC_FIELD] = plasma_local.electric_field/critical_field;

	} catch (const std::exception& ex) {
		// internal error in runaway distribution calculation
		std::cerr << "[Runaway Physics] ERROR: An error occurred during runaway distribution calculation." << std::endl;
		std::cerr << "[Runaway Physics] ERROR : " << ex.what() << std::endl;
		rundensity_after = ITM_INVALID_FLOAT;
		
	}
	return rundensity_after;
}

// Runafluid switch message
int list_parameter_settings(module_struct const &modules){
	
	// Dreicer message
	if (modules.dreicer_formula.empty()){
		std::cerr << "  [Runaway Physics] \tDreicer module OFF"<< std::endl;
	}else{
		std::cerr << "  [Runaway Physics] \tDreicer module ON ("  << modules.dreicer_formula << ")"<< std::endl;
	}
		
	// avalanche message
	if (modules.avalanche_formula.empty()){
		std::cerr << "  [Runaway Physics] \tAvalanche OFF"<< std::endl;
	}else{
		std::cerr << "  [Runaway Physics] \tAvalanche module ON (" << modules.avalanche_formula << ")" << std::endl;
	}
	
	// toroidicity message
	if (!modules.dreicer_toroidicity && !modules.avalanche_toroidicity){
		std::cerr << "  [Runaway Physics] \tToroidicity module OFF"<< std::endl;
		
	}else if (modules.dreicer_toroidicity && modules.avalanche_toroidicity){
		std::cerr << "  [Runaway Physics] \tToroidicity module ON"<< std::endl;
		
	}else if (modules.dreicer_toroidicity && !modules.avalanche_toroidicity){
		std::cerr << "  [Runaway Physics] \tToroidicity module ONLY for Dreicer"<< std::endl;
		
	}else if (!modules.dreicer_toroidicity && modules.avalanche_toroidicity){
		std::cerr << "  [Runaway Physics] \tToroidicity module ONLY for Avalanche"<< std::endl;
	}
}
