set(SOURCE_FILES
	critical_field.cpp
	growth_rate.cpp
	avalanche.cpp
	control.cpp
	dreicer.cpp
)

find_package(HDF5)

if(HDF5_FOUND)
	set(SOURCE_FILES 
			${SOURCE_FILES}
			hdf5export.cpp)
endif()
message(${SOURCE_FILES})

add_library(Runaphys ${SOURCE_FILES})
