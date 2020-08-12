#include <cmath>

#include <stdexcept>
#include <iostream>

#include "avalanche.h"
#include "products.h"
#include "critical_field.h"

using namespace std;

double avalanche_generation_rate(double electron_density, double electron_temperature, double effective_charge, double electric_field, double magnetic_field, module_struct modules) {

	double avalanche_generation_rate = 0;
	double avalanche_threshold_field;

	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);
	double critical_field = calculate_critical_field(electron_density, electron_temperature);
	double runaway_collision_time = calculate_runaway_collision_time(electron_density, electron_temperature);
	
	if ( (modules.avalanche_formula == "rosenbluth_putvinski") || (modules.avalanche_formula == "rosenbluth_putvinski_with_threshold") ){

		avalanche_generation_rate = (electric_field/critical_field - 1) / (2*runaway_collision_time*coulomb_log);

		// threshold field: avalanche_thresold_field
		if (modules.avalanche_formula == "rosenbluth_putvinski_with_threshold")
			avalanche_threshold_field = calculate_avalanche_threshold_field(electron_density, electron_temperature,	effective_charge, critical_field, magnetic_field);
		else avalanche_threshold_field = 0;

		if (electric_field < avalanche_threshold_field) avalanche_generation_rate = 0;

		// Avalanche rate must be non-negative
		if(isnan(avalanche_generation_rate) || (avalanche_generation_rate<0)) avalanche_generation_rate = 0;
	}
	
	return avalanche_generation_rate;
	
}

double calculate_avalanche_threshold_field(double electron_density, double electron_temperature, double effective_charge, double critical_field, double magnetic_field){

	// electron collision time

	double runaway_collision_time = calculate_runaway_collision_time(electron_density, electron_temperature);
	double synchrotron_loss_time = calculate_synchrotron_loss_time(magnetic_field);
	double norm_synchrotron_loss_time = synchrotron_loss_time/runaway_collision_time;

	return critical_field*(1.0 + (1.0+effective_charge) / sqrt(norm_synchrotron_loss_time) / pow( 1.0/8.0 + (1.0+effective_charge) * (1.0+effective_charge) / norm_synchrotron_loss_time , 1.0/6.0));

}

double calculate_toroidicity_avalanche(double inv_asp_ratio, double electric_field, double electron_density, double electron_temperature, double rho_tor_norm){

    double inv_asp_ratio_coord = inv_asp_ratio*rho_tor_norm;
    
	double critical_field = calculate_critical_field(electron_density, electron_temperature);
	double rel_electric_field = electric_field/critical_field;
	
	double toroidicity_avalanche = pow(1.0-inv_asp_ratio_coord,2)/(ITM_PI*sqrt(inv_asp_ratio_coord*rel_electric_field));
	
	if (rel_electric_field < 1){
		toroidicity_avalanche = 1;
	}
	return toroidicity_avalanche;

}
