#ifndef CHECKS_H
#define CHECKS_H

#include "constants.h"

void electron_density_valid(double electron_density);

void electron_temperature_valid(double electron_temperature);

void runaway_density_valid(double runaway_density);

void effective_charge_valid(double Zeff);

void magnetic_field_valid(double magnetic_field);

void inv_asp_ratio_valid(double inv_asp_ratio);

void rho_tor_norm_valid(double rho_tor_norm);

void time_step_valid(double timestep);

#endif //CHECKS_H