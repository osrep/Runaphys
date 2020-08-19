#include <stdlib.h>
#include <cmath>
#include <vector>
#include "constants.h"
#include "growth_rate.h"
#include "critical_field.h"
#include "cell.h"

/**
 * Checks if growth is over a specified limit, given by the limit parameter
 * It requires the physical parameters of the plasma, which is given in the profile
 * Above a certain rho given by rho_max, a false flag is returned
 * regardless of the outcome of the check.
 * Otherwise if it is over the limit it returns true (1) and false (0) if not
 */
int is_growth_rate_over_limit(profile pro, double limit, double rho_max) {

	for (std::vector<cell>::iterator it = pro.begin(); it != pro.end(); ++it) {
		if ( (calculate_growth_rate(it->electron_density, it->electron_temperature,
				it->effective_charge, std::abs(it->electric_field)) > std::abs(limit))
				&& (it->rho < rho_max) )
			return 1;
	}
	return 0;
}

double calculate_growth_rate(double electron_density, double electron_temperature,
				double effective_charge, double electric_field) {

	if(electron_density < electron_density_lower_boundary)
		throw "Electron density value out of boundaries";
	if(electron_temperature < electron_temperature_lower_boundary)
		throw "Electron temperature out of boundaries";
	if(effective_charge < effective_charge_lower_boundary)
		throw "Effective charge higher than 1";
	
	double growth_rate;

	// diffusion time
	double thermal_electron_collision_time = calculate_thermal_electron_collision_time(electron_density, electron_temperature);

	double dreicer_field = calculate_dreicer_field(electron_density,electron_temperature);

	// growth rate
	growth_rate = electron_density / thermal_electron_collision_time
			* pow(dreicer_field / electric_field, 3.0 * (1.0 + effective_charge) / 16.0)
			* exp(-dreicer_field / (4.0 * electric_field) - sqrt((1.0 + effective_charge) * dreicer_field / electric_field));

	return growth_rate;
}
