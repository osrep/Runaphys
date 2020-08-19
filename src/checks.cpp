#include "constants.h"

void electron_density_valid(double electron_density){
	if(electron_density < electron_density_lower_boundary)
		throw "Electron density value out of boundaries";
}

void electron_temperature_valid(double electron_temperature){
	if(electron_temperature < electron_temperature_lower_boundary)
		throw "Electron temperature out of boundaries";
}

void runaway_density_valid(double runaway_density){
	if(runaway_density < runaway_density_lower_boundary)
		throw "Runaway density value out of boundaries";
}

void effective_charge_valid(double Zeff){
	if(Zeff < effective_charge_lower_boundary)
		throw "Effective charge lower than 1";
}

void magnetic_field_valid(double magnetic_field){
	if(magnetic_field < magnetic_field_lower_boundary)
		throw "Magnetic field out of boundaries";
}

void inv_asp_ratio_valid(double inv_asp_ratio){
	if(inv_asp_ratio > inv_asp_ratio_higher_boundary || inv_asp_ratio < inv_asp_ratio_lower_boundary)
		throw "Invalid inv_asp_ratio";
}

void rho_tor_norm_valid(double rho_tor_norm){
	if(rho_tor_norm > rho_tor_norm_higher_boundary || rho_tor_norm < rho_tor_norm_lower_boundary)
		throw "Invalid rho_to_norm";
}

void time_step_valid(double timestep){
	if(timestep < timestep_lower_boundary)
		throw "Invalid timestep";
}