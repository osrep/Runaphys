#ifndef CELL_H_
#define CELL_H_

// cell structure	
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

struct plasma_local {
	double rho;
	double electron_density;
	double electron_temperature;
	double effective_charge;
	double electric_field;
	double magnetic_field;
	double runaway_density; 
};


#ifdef __cplusplus
}
#endif

typedef std::vector<plasma_local> plasma_profile;

#endif	/* CELL_H_ */
