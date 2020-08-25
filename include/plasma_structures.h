#ifndef CELL_H_
#define CELL_H_

// cell structure	
#include <vector>

struct plasma_local {
	double rho;
	double electron_density;
	double electron_temperature;
	double effective_charge;
	double electric_field;
	double magnetic_field;
	double runaway_density; 
};

typedef std::vector<cell> plasma_profile;

#endif	/* CELL_H_ */
