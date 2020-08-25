#ifndef CRITICAL_FIELD_H_
#define CRITICAL_FIELD_H_

#include "plasma_structures.h"

int is_field_critical(plasma_profile pro, double rho_max);

double calculate_coulomb_log(double electron_density, double electron_temperature);

double calculate_critical_field(double electron_density, double electron_temperature);

double calculate_dreicer_field(double electron_density, double electron_temperature);

double calculate_thermal_electron_collision_time(double electron_density, double electron_temperature);

double calculate_runaway_collision_time(double electron_density, double electron_temperature);

double calculate_synchrotron_loss_time(double magnetic_field);

#endif /* CRITICAL_FIELD_H_ */
