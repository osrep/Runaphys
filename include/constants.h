#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#ifdef ITM_CONSTANTS
    #include <itm_constants.h>
    
#elif IMAS_CONSTANTS
    #include <imas_constants.h>
    
    // value of pi
    #define ITM_PI		IMAS_PI

    // speed of light [m/s]
    #define ITM_C		IMAS_C

    // electron volt [eV]
    #define ITM_EV		IMAS_EV

    // elementary charge [coulomb]
    #define ITM_QE		ITM_EV

    // electron mass [kg]
    #define ITM_ME		IMAS_ME

    // vacuum permeability
    #define ITM_MU0		IMAS_MU0

    // vacuum permittivity
    #define ITM_EPS0	IMAS_EPS0    
    
    // ERROR CODE
    const double ITM_INVALID_INT = -999999999;
    
#else
    // value of pi
    const double ITM_PI = 3.141592653589793238462643383280;

    // speed of light [m/s]
    const double ITM_C = 2.99792458e8;

    // electron volt [eV]
    const double ITM_EV	= 1.602176565e-19;

    // elementary charge [coulomb]
    #define ITM_QE	 ITM_EV

    // electron mass [kg]
    const double ITM_ME	= 9.10938291e-31;

    // vacuum permeability
    const double ITM_MU0 = 4.0e-7 * ITM_PI;

    // vacuum permittivity
    const double ITM_EPS0 = 1.0 / (ITM_MU0 * ITM_C * ITM_C);

    // ERROR CODE
    const double ITM_INVALID_INT = -999999999;
    const double ITM_INVALID_FLOAT = -9.0e40;

    //parameter boundaries
    const double electron_density_lower_boundary = 0;

    const double electron_temperature_lower_boundary = 0;

    const double runaway_density_lower_boundary = 0;

    const double effective_charge_lower_boundary = 1;

    const double magnetic_field_lower_boundary = 0;

    const double inv_asp_ratio_higher_boundary = 1;
    const double inv_asp_ratio_lower_boundary = 0;

    const double rho_tor_norm_higher_boundary = 1;
    const double rho_tor_norm_lower_boundary = 0;

    const double timestep_lower_boundary = 0;	
	
#endif
	// rate identifiers
	const int N_RATES = 4;
	const int RATEID_DREICER = 0;
	const int RATEID_AVALANCHE = 1;
	const int RATEID_ELECTRIC_FIELD = 2;
	const int RATEID_CRITICAL_FIELD = 3;

    // distsource_identifier for runaways (7)
    const int DISTSOURCE_IDENTIFIER = 7;
#endif 