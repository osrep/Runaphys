set(SOURCE_FILES
	critical_field.cpp
	growth_rate.cpp
	avalanche.cpp
	control.cpp
	dreicer.cpp
	checks.cpp
)
if(BUILD_DLL)
	add_library(Runaphys SHARED ${SOURCE_FILES})
	message("-- BUILDING DLL LIBRARY")
else()
	find_package(HDF5)
	
	if(HDF5_FOUND)
		message("-- HDF5 FOUND")
		set(SOURCE_FILES 
				${SOURCE_FILES}
				hdf5export.cpp)
	else()
		message("-- HDF5 NOT FOUND")
	endif()
	
	add_library(Runaphys  ${SOURCE_FILES})
endif()


