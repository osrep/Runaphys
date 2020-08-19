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

const double reference_runaway_electron_density_before = 3.12292e15;
const double reference_timestep = 1.82e-3;
const double reference_runaway_electron_density_after63 = 7.85e16;
const double reference_runaway_electron_density_after66 = 1.66e19;
const double reference_runaway_electron_density_after67 = 1.31e20;
double rate_values[4] = {0,0,0,0};

cell CELL = {reference_rho_tor_norm, reference_ne, reference_te, reference_Zeff_1,reference_electric_field_1_runafluid, reference_magnetic_field, reference_runaway_electron_density_before};

const double invalid_electron_density_value = -1;
const double invalid_electron_temp = -1;
const double invalid_eff_charge = -1;
const double invalid_magnetic_field = -1;
const double invalid_inv_asp_ratio = -1;
const double invalid_rho_tor_norm = -1;

module_struct modules_off; 

TEST(CoulombLog, CalculateCoulombLog) {
	EXPECT_NEAR(reference_Coulomb_log, calculate_coulomb_log(reference_ne, reference_te), 0.0001);
}
TEST(CoulombLog, ExpectErrorThrowDensity) {
	EXPECT_THROW(calculate_coulomb_log(invalid_electron_density_value, reference_te), const char*);
}
TEST(CoulombLog, ExpectErrorThrowTemp) {
	EXPECT_THROW(calculate_coulomb_log(reference_ne, invalid_electron_temp), const char*);
}

TEST(CriticalField, CalculateCriticalField) {
	EXPECT_NEAR(reference_electric_field, calculate_critical_field(reference_ne, reference_te), 0.0001);
}
TEST(CriticalField, ExpectErrorThrowDensity) {
	EXPECT_THROW(calculate_critical_field(invalid_electron_density_value, reference_te),const char*);
}
TEST(CriticalField, ExpectErrorThrowTemperature) {
	EXPECT_THROW(calculate_critical_field(reference_ne, invalid_electron_temp),const char*);
}

TEST(GrowthRate, CalculateDreicerField) {
	EXPECT_NEAR(reference_dreicer_field, calculate_dreicer_field(reference_ne, reference_te), 0.01);
}
TEST(GrowthRate, ExpectErrorThrowDensityDreicer) {
	EXPECT_THROW(calculate_dreicer_field(invalid_electron_density_value, reference_te), const char*);
}
TEST(GrowthRate, ExpectErrorThrowTempDreicer) {
	EXPECT_THROW(calculate_dreicer_field(reference_ne, invalid_electron_temp), const char*);
}

TEST(GrowthRate, CalculateThermalElectronCollisionTime) {
	EXPECT_NEAR(reference_thermal_electron_collision_time,calculate_thermal_electron_collision_time(reference_ne,reference_te), 0.0001);
}
TEST(GrowthRate, ExpectErrorThrowDensityThermalElectronCollisionTime) {
	EXPECT_THROW( calculate_thermal_electron_collision_time(invalid_electron_density_value,reference_te), const char*);
}
TEST(GrowthRate, ExpectErrorThrowTempThermalElectronCollisionTime) {
	EXPECT_THROW(calculate_thermal_electron_collision_time(reference_ne,invalid_electron_temp), const char*);
}

TEST(GrowthRate, CalculateGrowthRate_1) {
	EXPECT_NEAR(reference_growth_rate_1, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_1, reference_electric_field_1), 1e18);
}
TEST(GrowthRate, ExpectErrorThrowDensity) {
	EXPECT_THROW(calculate_growth_rate(invalid_electron_density_value, reference_te, reference_Zeff_1, reference_electric_field_1), const char*);
}
TEST(GrowthRate, ExpectErrorThrowTemp) {
	EXPECT_THROW(calculate_growth_rate(reference_ne, invalid_electron_temp, reference_Zeff_1, reference_electric_field_1), const char*);
}
TEST(GrowthRate, ExpectErrorThrowEff) {
	EXPECT_THROW(calculate_growth_rate(reference_ne, reference_te, invalid_eff_charge, reference_electric_field_1), const char*);
}

TEST(GrowthRate, CalculateGrowthRate_2) {
	EXPECT_NEAR(reference_growth_rate_2, calculate_growth_rate(reference_ne, reference_te, reference_Zeff_2, reference_electric_field_2), 1e18);
}
TEST(GrowthRate, ExpectErrorThrowDensity2) {
	EXPECT_THROW(calculate_growth_rate(invalid_electron_density_value, reference_te, reference_Zeff_1, reference_electric_field_2), const char*);
}
TEST(GrowthRate, ExpectErrorThrowTemp2) {
	EXPECT_THROW(calculate_growth_rate(reference_ne, invalid_electron_temp, reference_Zeff_1, reference_electric_field_2), const char*);
}
TEST(GrowthRate, ExpectErrorThrowEff2) {
	EXPECT_THROW(calculate_growth_rate(reference_ne, reference_te, invalid_eff_charge, reference_electric_field_2), const char*);
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
TEST(CriticalField, ExpectThrowDensityRunawayCollisionTime) {
	EXPECT_THROW(calculate_runaway_collision_time(invalid_electron_density_value, reference_te), const char*);
}
TEST(CriticalField, ExpectThrowTempRunawayCollisionTime) {
	EXPECT_THROW(calculate_runaway_collision_time(reference_ne, invalid_electron_temp), const char*);
}

TEST(CriticalField, CalculateSynchrotronLossTime) {
	EXPECT_NEAR(reference_synchrotron_loss_time, calculate_synchrotron_loss_time(reference_magnetic_field), reference_synchrotron_loss_time*1e-5);
}
TEST(CriticalField, ExpectThrowMagneticField){
	EXPECT_THROW(calculate_synchrotron_loss_time(invalid_magnetic_field), const char*);
}

TEST(Dreicer, DreicerGenerationRate_63) {
	EXPECT_NEAR(reference_dreicer_generation_rate_63, dreicer_generation_rate(reference_ne, reference_te,reference_Zeff_1,
																		  reference_electric_field_1_runafluid,modules63), reference_dreicer_generation_rate_63*1e-4);
}
TEST(Dreicer, ExpectThrowDensity){
	EXPECT_THROW(dreicer_generation_rate(invalid_electron_density_value, reference_te,reference_Zeff_1,
			  reference_electric_field_1_runafluid,modules63), const char*);
}
TEST(Dreicer, ExpectThrowTemp){
	EXPECT_THROW(dreicer_generation_rate(reference_ne, invalid_electron_temp,reference_Zeff_1,
			  reference_electric_field_1_runafluid,modules63), const char*);
}
TEST(Dreicer, ExpectThrowEffCharge){
	EXPECT_THROW(dreicer_generation_rate(reference_ne, reference_te,invalid_eff_charge,
			  reference_electric_field_1_runafluid,modules63),const char*);
}


TEST(Dreicer, DreicerGenerationRate_66) {
	EXPECT_NEAR(reference_dreicer_generation_rate_66, dreicer_generation_rate(reference_ne, reference_te, reference_Zeff_1,
																		  reference_electric_field_1_runafluid,modules66), reference_dreicer_generation_rate_66*1e-4);
}

TEST(Dreicer, DreicerGenerationRate_67) {
	EXPECT_NEAR(reference_dreicer_generation_rate_67, dreicer_generation_rate(reference_ne, reference_te, reference_Zeff_1,
																		  reference_electric_field_1_runafluid,modules67), reference_dreicer_generation_rate_67*1e-4);
}

TEST(Dreicer, CalculateLambda) {
	EXPECT_NEAR(reference_lambda,calculate_lambda(reference_alpha_1),reference_lambda*1e-4);
}

TEST(Dreicer, CalculateGamma) {
	EXPECT_NEAR(reference_gamma,calculate_gamma(reference_Zeff_1, reference_alpha_1),reference_gamma*1e-9);
}
TEST(Dreicer, ExpectErrorThrowEffChargeGamma){
	EXPECT_THROW(calculate_gamma(invalid_eff_charge, reference_alpha_1), const char*);
}

TEST(Dreicer, CalculateH) {
	EXPECT_NEAR(reference_h,calculate_h(reference_alpha_1, reference_Zeff_1), reference_h*1e-8);
}
TEST(Dreicer, ExpectErrorThrowEffChargeH){
	EXPECT_THROW(calculate_h(reference_alpha_1, invalid_eff_charge),const char*);
}

TEST(Dreicer, CalculateToroidicityDreicer) {
	EXPECT_NEAR(reference_toroidicity_dreicer,calculate_toroidicity_dreicer(reference_inv_asp_ratio,reference_rho_tor_norm),reference_toroidicity_dreicer*1e-6);
}
TEST(Dreicer, ExpectErrorThrowInvAspRatio){
	EXPECT_THROW(calculate_toroidicity_dreicer(invalid_inv_asp_ratio,reference_rho_tor_norm), const char*);
}
TEST(Dreicer, ExpectErrorThrowRhoTorNorm){
	EXPECT_THROW(calculate_toroidicity_dreicer(reference_inv_asp_ratio,invalid_rho_tor_norm), const char*);
}


TEST(Avalanche, CalculateAvalancheThresholdField){								//new test with good inputs and outputs
	EXPECT_NEAR(reference_avalanche_threshold_field, calculate_avalanche_threshold_field(reference_ne, reference_te, reference_Zeff_1, reference_critical_field, reference_magnetic_field),reference_avalanche_threshold_field*1e-5);
}
TEST(Avalanche, ExpectErrorElDensity){
	EXPECT_THROW(calculate_avalanche_threshold_field(invalid_eff_charge, reference_te, reference_Zeff_1, reference_critical_field, reference_magnetic_field),const char*);
}
TEST(Avalanche, ExpectErrorTemp){
	EXPECT_THROW(calculate_avalanche_threshold_field(reference_ne, invalid_electron_temp, reference_Zeff_1, reference_critical_field, reference_magnetic_field),const char*);
}
TEST(Avalanche, ExpectErrorEffCharge){
	EXPECT_THROW(calculate_avalanche_threshold_field(reference_ne, reference_te, invalid_eff_charge, reference_critical_field, reference_magnetic_field),const char*);
}
TEST(Avalanche, ExpectErrorMagneticField){
	EXPECT_THROW(calculate_avalanche_threshold_field(reference_ne, reference_te, reference_Zeff_1, reference_critical_field, invalid_magnetic_field),const char*);
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
TEST(Avalanche, ExpectErrorElDensityGenRate){
	EXPECT_THROW( avalanche_generation_rate(invalid_electron_density_value, reference_te, reference_Zeff_1,
											reference_electric_field_2_runafluid,reference_magnetic_field,
																					modules_no_threshold),const char*);
}
TEST(Avalanche, ExpectErrorTempGenRate){
	EXPECT_THROW( avalanche_generation_rate(reference_ne, invalid_electron_temp, reference_Zeff_1,
											reference_electric_field_2_runafluid,reference_magnetic_field,
																					modules_no_threshold),const char*);
}
TEST(Avalanche, ExpectErrorEffChargeGenRate){
	EXPECT_THROW( avalanche_generation_rate(reference_ne, reference_te, invalid_eff_charge,
											reference_electric_field_2_runafluid,reference_magnetic_field,
																					modules_no_threshold),const char*);
}
TEST(Avalanche, ExpectErrorMagneticFieldGenRate){
	EXPECT_THROW( avalanche_generation_rate(reference_ne, reference_te, reference_Zeff_1,
											reference_electric_field_2_runafluid,invalid_magnetic_field,
																					modules_no_threshold),const char*);
}

TEST(Control, AdvanceRunawayPopulation_63)  {
	EXPECT_NEAR(reference_runaway_electron_density_after63, advance_runaway_population(CELL, reference_timestep,reference_inv_asp_ratio, reference_rho_tor_norm, modules63, rate_values), reference_runaway_electron_density_after63*1e-3);
}
TEST(Control, AdvanceRunawayPopulation_66)  {
	EXPECT_NEAR(reference_runaway_electron_density_after66, advance_runaway_population(CELL, reference_timestep,reference_inv_asp_ratio, reference_rho_tor_norm, modules66, rate_values), reference_runaway_electron_density_after66*1e-3);
}
TEST(Control, AdvanceRunawayPopulation_67)  {
	EXPECT_NEAR(reference_runaway_electron_density_after67, advance_runaway_population(CELL, reference_timestep,reference_inv_asp_ratio, reference_rho_tor_norm, modules67, rate_values), reference_runaway_electron_density_after67*1e-3);
}

TEST(list_parameter_setting, modulesOFF){
	testing::internal::CaptureStderr();
	list_parameter_settings(modules_off);
	std::string output = testing::internal::GetCapturedStderr();
	EXPECT_EQ("  [Runaway Fluid] \tDreicer module OFF\n  [Runaway Fluid] \tAvalanche OFF\n  [Runaway Fluid] \tToroidicity module OFF\n", output);
}
TEST(list_parameter_setting, modulesON){
	testing::internal::CaptureStderr();
	list_parameter_settings(modules63);
	std::string output = testing::internal::GetCapturedStderr();
	EXPECT_EQ("  [Runaway Fluid] \tDreicer module ON (hc_formula_63)\n  [Runaway Fluid] \tAvalanche module ON (rosenbluth_putvinski)\n  [Runaway Fluid] \tToroidicity module OFF\n", output);
}