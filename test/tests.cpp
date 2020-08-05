#include <gtest/gtest.h>
#include "../include/critical_field.h"
#include "../include/growth_rate.h"
#include "dreicer.h"
#include "avalanche.h"
#include "control.h"

//Runin reference values
const double reference_te = 1e5;
const double reference_ne = 1e21;
const double reference_dreicer_field = 4.7823;
const double reference_electric_field = 0.93588;
const double reference_growth_rate_2 = 7.5813e22;
const double reference_growth_rate_1 = 5.536e22;
const double reference_thermal_electron_collision_time = 4.4596e-4;
const double reference_Zeff_1 = 1.0;
const double reference_Zeff_2 = 1.2;
const double reference_electric_field_1 = 1.0;
const double reference_electric_field_2 = 1.2;
const double reference_Coulomb_log = 18.35387764;
const double reference_rho_max = 0.95;

//Runafluid reference values
const double reference_critical_field = 0.935882;
const double reference_runaway_electron_collision_time = 1.82129e-3;
const double reference_alpha_1 = 1.2;
const double reference_alpha_2 = 0.8;
const double reference_electric_field_1_runafluid =  reference_alpha_1*reference_critical_field;
const double reference_electric_field_2_runafluid =  reference_alpha_2*reference_critical_field;

std::string str_dreicer_formula63 = "hc_formula_63";
std::string str_dreicer_formula66 = "hc_formula_66";
std::string str_dreicer_formula67 = "hc_formula_67";
std::string str_avalanche_formula = "rosenbluth_putvinski";
std::string str_avalanche_formula_threshold = "rosenbluth_putvinski_with_threshold";
double warning_percentage_limit = 1.0;
double rho_edge_calculation_limit = 0.85;

module_struct modules63 {str_dreicer_formula63, false, str_avalanche_formula, false, false, warning_percentage_limit, rho_edge_calculation_limit};
module_struct modules66 {str_dreicer_formula66, false, str_avalanche_formula, false, false, warning_percentage_limit, rho_edge_calculation_limit};
module_struct modules67 {str_dreicer_formula67, false, str_avalanche_formula, false, false, warning_percentage_limit, rho_edge_calculation_limit};

const double reference_dreicer_generation_rate_63 =4.1378e-2;
const double reference_dreicer_generation_rate_66 = 9.1233;
const double reference_dreicer_generation_rate_67 = 7.1931e1;
const double reference_lambda = 2.0169;
const double reference_Coulomb_logarithm = 18.3539;
const double reference_gamma =3.086476806;
const double reference_h = 0.175510257;
const double reference_synchrotron_loss_time = 1.28967;
const double reference_inv_asp_ratio = 0.30303;
const double reference_toroidicity_dreicer = 0.311578581;

const double reference_rho_tor_norm = 0.65;
const double reference_avalanche_threshold_field = 1.03463;

module_struct modules_no_threshold{str_dreicer_formula63, false, str_avalanche_formula, false, false, warning_percentage_limit, rho_edge_calculation_limit};
module_struct modules_threshold{str_dreicer_formula63, false, str_avalanche_formula_threshold, false, false, warning_percentage_limit, rho_edge_calculation_limit};

const double reference_magnetic_field = 2;
const int avalanche_generation_rate_mod_1 = 0;
const int avalanche_generation_rate_mod_2 = 0;
const double avalanche_generation_rate_mod_3 = 2.991547;

TEST(CoulombLog, CalculateCoulombLog) {
	EXPECT_NEAR(reference_Coulomb_log, calculate_coulomb_log(reference_ne, reference_te), 0.0001);
}

TEST(CriticalField, CalculateCriticalField) {
	EXPECT_NEAR(reference_electric_field, calculate_critical_field(reference_ne, reference_te), 0.0001);
}

TEST(GrowthRate, CalculateDreicerField) {
	EXPECT_NEAR(reference_dreicer_field, calculate_dreicer_field(reference_ne, reference_te), 0.01);
}

TEST(GrowthRate, CalculateThermalElectronCollisionTime) {
	EXPECT_NEAR(reference_thermal_electron_collision_time, calculate_thermal_electron_collision_time(reference_ne,reference_te), 0.0001);
}

TEST(GrowthRate, CalculateGrowthRate_1) {
	EXPECT_NEAR(reference_growth_rate_1, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_1, reference_electric_field_1), 1e18);
}

TEST(GrowthRate, CalculateGrowthRate_2) {
	EXPECT_NEAR(reference_growth_rate_2, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_2, reference_electric_field_2), 1e18);
}

TEST(CriticalField, IsFieldCritical) {
	cell cell1, cell2;

	//increasing critical field
	cell1.electron_density = 1.1*reference_ne;
	cell1.electron_temperature = reference_te;
	cell1.electric_field = reference_electric_field;

	//decreasing critical field
	cell2.electron_density = 0.9*reference_ne;
	cell2.electron_temperature = reference_te;
	cell2.electric_field = reference_electric_field;

	profile pro;
	pro.push_back(cell1);
	EXPECT_NEAR(0, is_field_critical(pro, reference_rho_max), 0.1);
	EXPECT_NEAR(reference_electric_field, calculate_critical_field(reference_ne,reference_te), 0.1);

	pro.push_back(cell2);
	EXPECT_NEAR(1, is_field_critical(pro, reference_rho_max), 0.1);

}

TEST(GrowthRate, IsGrowthRateOverLimit) {
	cell cell1, cell2;

	cell1.electron_density = 0.9*reference_ne;
	cell1.electron_temperature = reference_te;
	cell1.effective_charge = reference_Zeff_1;
	cell1.electric_field = reference_electric_field_1;

	cell2.electron_density = 1.1*reference_ne;
	cell2.electron_temperature = reference_te;
	cell2.effective_charge = reference_Zeff_2;
	cell2.electric_field = reference_electric_field_2;

	profile pro;
	pro.push_back(cell1);
	EXPECT_EQ(1, is_growth_rate_over_limit(pro, reference_growth_rate_1, reference_rho_max));

	pro.push_back(cell2);
	EXPECT_EQ(0, is_growth_rate_over_limit(pro, reference_growth_rate_2, reference_rho_max));
}

//Runafluid tests

TEST(CriticalField, CalculateRunawayCollisionTime) {
	EXPECT_NEAR(reference_runaway_electron_collision_time, calculate_runaway_collision_time(reference_ne, reference_te), reference_runaway_electron_collision_time*1e-4);
}

TEST(CriticalField, CalculateSynchrotronLossTime) {
	EXPECT_NEAR(reference_synchrotron_loss_time, calculate_synchrotron_loss_time(reference_magnetic_field), reference_synchrotron_loss_time*1e-5);
}

TEST(Dreicer, DreicerGenerationRate_63) {
	EXPECT_NEAR(reference_dreicer_generation_rate_63, dreicer_generation_rate(reference_ne, reference_te,reference_Zeff_1,
																		  reference_electric_field_1_runafluid,reference_rho_tor_norm,modules63), reference_dreicer_generation_rate_63*1e-4);
}

TEST(Dreicer, DreicerGenerationRate_66) {
	EXPECT_NEAR(reference_dreicer_generation_rate_66, dreicer_generation_rate(reference_ne, reference_te, reference_Zeff_1,
																		  reference_electric_field_1_runafluid,reference_rho_tor_norm,modules66), reference_dreicer_generation_rate_66*1e-4);
}

TEST(Dreicer, DreicerGenerationRate_67) {
	EXPECT_NEAR(reference_dreicer_generation_rate_67, dreicer_generation_rate(reference_ne, reference_te, reference_Zeff_1,
																		  reference_electric_field_1_runafluid,reference_rho_tor_norm,modules67), reference_dreicer_generation_rate_67*1e-4);
}

TEST(Dreicer, CalculateLambda) {
	EXPECT_NEAR(reference_lambda,calculate_lambda(reference_alpha_1),reference_lambda*1e-4);
}

TEST(Dreicer, CalculateGamma) {
	EXPECT_NEAR(reference_gamma,calculate_gamma(reference_Zeff_1, reference_alpha_1),reference_gamma*1e-9);
}

TEST(Dreicer, CalculateH) {
	EXPECT_NEAR(reference_h,calculate_h(reference_alpha_1, reference_Zeff_1), reference_h*1e-8);
}

TEST(Dreicer, CalculateToroidicityDreicer) {
	EXPECT_NEAR(reference_toroidicity_dreicer,calculate_toroidicity_dreicer(reference_inv_asp_ratio,reference_rho_tor_norm),reference_toroidicity_dreicer*1e-6);
}

TEST(Avalanche, CalculateAvalancheThresholdField){								//new test with good inputs and outputs
	EXPECT_NEAR(reference_avalanche_threshold_field, calculate_avalanche_threshold_field(reference_ne, reference_te, reference_Zeff_1, reference_critical_field, reference_magnetic_field),reference_avalanche_threshold_field*1e-5);
}


TEST(Avalanche, CalculateAvalancheGenerationRate) {

	EXPECT_NEAR(avalanche_generation_rate_mod_1, avalanche_generation_rate(reference_ne, reference_te, reference_Zeff_1,
																		 reference_electric_field_2_runafluid,reference_magnetic_field,
																		 modules_no_threshold), avalanche_generation_rate_mod_1*1e-6);
	EXPECT_NEAR(avalanche_generation_rate_mod_2, avalanche_generation_rate(reference_ne, reference_te, reference_Zeff_1,
																		 reference_electric_field_2_runafluid,reference_magnetic_field,
																		 modules_no_threshold), avalanche_generation_rate_mod_2*1e-6);
	EXPECT_NEAR(avalanche_generation_rate_mod_3, avalanche_generation_rate(reference_ne, reference_te, reference_Zeff_1,
																		 reference_electric_field_1_runafluid,reference_magnetic_field,
																		 modules_threshold), avalanche_generation_rate_mod_3*1e-5);

}