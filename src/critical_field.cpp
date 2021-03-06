#include <cmath>
#include <stdlib.h>
#include "critical_field.h"
#include "products.h"
#include "plasma_structures.h"
#include "checks.h"

/** 
 * Checks if a electric field is larger then the critical field 
 * It requires the physical parameters of the plasma, which is given in the plasma_profile
 * Above a certain rho given by rho_max, a false flag is returned
 * regardless of the outcome of the check.
 * Otherwise if it is larger it returns true (1) and false (0) if not
 */
int is_field_critical(plasma_profile pro, double rho_max) {

	for (std::vector<plasma_local>::iterator it = pro.begin(); it != pro.end(); ++it) {
		if ( (std::abs(it->electric_field)) > (calculate_critical_field(it->electron_density, it->electron_temperature) )
		  && (it->rho < rho_max) )
			return 1;
	}

	return 0;
}

double calculate_critical_field(double electron_density, double electron_temperature) {

	electron_density_valid(electron_density);
	electron_temperature_valid(electron_temperature);
	
	// Coulomb logarithm
	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);

	// Critical field	
	return electron_density * e3 * coulomb_log / pi_e02_me_4_c2;
}

double calculate_coulomb_log(double electron_density, double electron_temperature) {

	electron_density_valid(electron_density);
	electron_temperature_valid(electron_temperature);

	// Coulomb logarithm	
	return 14.9 - 0.5 * log(electron_density * 1e-20) + log(electron_temperature * 1e-3);
}

double calculate_dreicer_field(double electron_density, double electron_temperature){

	electron_density_valid(electron_density);
	electron_temperature_valid(electron_temperature);

	// Dreicer field
	return  calculate_critical_field(electron_density, electron_temperature) * me_c2 / electron_temperature / ITM_EV ;
}

double calculate_thermal_electron_collision_time(double electron_density, double electron_temperature){

	electron_density_valid(electron_density);
	electron_temperature_valid(electron_temperature);

	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);
			
	double therm_speed = sqrt(2*electron_temperature*ITM_EV/ITM_ME);

	return pi_4_e02_me2__e4 * pow(therm_speed,3.0) / (electron_density * coulomb_log);	
}

double calculate_runaway_collision_time(double electron_density, double electron_temperature){

	electron_density_valid(electron_density);
	electron_temperature_valid(electron_temperature);

	double coulomb_log = calculate_coulomb_log(electron_density, electron_temperature);
			
	return pi_4_e02_me2_c3__e4 / (electron_density * coulomb_log);	
}

double calculate_synchrotron_loss_time(double magnetic_field){

	magnetic_field_valid(magnetic_field);
	return pi_6_e0_me3_c3__e4/magnetic_field/magnetic_field;
}
