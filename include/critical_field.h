#ifndef CRITICAL_FIELD_H_
#define CRITICAL_FIELD_H_

#include "cell.h"


double calculate_coulomb_log(double electron_density, double electron_temperature);

double calculate_critical_field(double electron_density, double electron_temperature);

double calculate_dreicer_field(double electron_density, double electron_temperature);

double calculate_thermal_electron_collision_time(double electron_density, double electron_temperature);

#endif /* CRITICAL_FIELD_H_ */
