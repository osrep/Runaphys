import ctypes as ct

class MODULE(ct.Structure):
	_fields_ = [("dreicer_formula", ct.c_char_p),
		    ("dreicer_toroidicity", ct.c_bool),
		    ("avalanche_formula", ct.c_char_p),
		    ("avalanche_toroidicity", ct.c_bool),
		    ("hdf5_output", ct.c_bool),
		    ("warning_percentage_limit", ct.c_double),
		    ("rho_edge_calculation_limit", ct.c_double)]

string1 = ""
string2 = ""

# create byte objects from the strings
dreicer_formula1 = string1.encode('utf-8')
avalanche_formula1 = string2.encode('utf-8')

dreicer_toroidicity = ct.c_bool(True)
avalanche_toroidicity = ct.c_bool(True)
hdf5_output = ct.c_bool(False)
warning_percentage_limit = ct.c_double(1.0)
rho_edge_calculation_limit = ct.c_double(0.85)

modules = MODULE(dreicer_formula1, dreicer_toroidicity, avalanche_formula1, avalanche_toroidicity, hdf5_output, warning_percentage_limit,rho_edge_calculation_limit)

#get the pointer to the structure
modules_pointer = ct.byref(modules)

class PLASMA(ct.Structure):
	_fields_ = [("rho", ct.c_double),
		    ("electron_density", ct.c_double),
		    ("electron_temperature", ct.c_double),
		    ("effective_charge", ct.c_double),
		    ("electric_field", ct.c_double),
		    ("magnetic_field", ct.c_double),
		    ("runaway_density", ct.c_double)]

rho = ct.c_double(1.8)
electron_density = ct.c_double(1e21)
electron_temperature = ct.c_double(1e5)
effective_charge = ct.c_double(1.0)
electric_field = ct.c_double(1.0)
magnetic_field = ct.c_double(2.0)
runaway_density = ct.c_double(3e15)

plasma_local = PLASMA(rho, electron_density, electron_temperature, effective_charge, electric_field, magnetic_field, runaway_density)

plasma_pointer = ct.byref(plasma_local)

lib_Runaphys = ct.cdll.LoadLibrary("/pfs/work/g2fleng/Runaphys/build/src/libRunaphys.so")

lib_Runaphys.Runaphys_advance_runaway_population.restype = ct.c_double

timestep = ct.c_double(1e-3)
inv_asp_ratio = ct.c_double(0.30303)
rho_tor_norm = ct.c_double(0.65)
rate_values_type = ct.c_double * 4
rate_values = rate_values_type(0.,0.,0.,0.)
rate_values_pointer = ct.byref(rate_values)

answer = lib_Runaphys.Runaphys_advance_runaway_population(ct.byref(plasma_local), timestep, inv_asp_ratio, rho_tor_norm, ct.byref(modules), ct.byref(rate_values))

print(answer)

