#include <stdlib.h>
#include <cmath>
#include <vector>
#include "constants.h"
#include "growth_rate.h"
#include "critical_field.h"

/*
Growth rate warning

The module outputs an integer value (0 or 1) which indicates, whether the growth rate of runaway electron
generation is above the limit value given in Demultiplexer workflow, thus runaway generation is to be expected.
If the growth rate exceeds the limit value this warning raises.

*/



// Calculation of growth rate
double calculate_growth_rate(double electron_density, double electron_temperature,
							 double effective_charge, double electric_field) {
	
	double growth_rate;

	// diffusion time
	double thermal_electron_collision_time = calculate_thermal_electron_collision_time(electron_density, electron_temperature);

	double dreicer_field = calculate_dreicer_field(electron_density,electron_temperature);

	// growth rate
	double me_c2 = ITM_ME * pow(ITM_C, 2);
	growth_rate = electron_density / thermal_electron_collision_time
			* pow(dreicer_field / electric_field, 3.0 * (1.0 + effective_charge) / 16.0)
			* exp(-dreicer_field / (4.0 * electric_field) - sqrt((1.0 + effective_charge) * dreicer_field / electric_field));

	return growth_rate;
}
