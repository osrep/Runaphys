cmake_minimum_required(VERSION 3.1)

project(Runaphys VERSION 1.0.0
              LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)

# TODO check flags to use
set(CMAKE_CXX_FLAGS "-Wall -ggdb -O3 -fPIC -march=native -mno-avx -fprofile-arcs -ftest-coverage ")

include_directories("include")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

message("flag: ${BUILD_TESTING}")

# Include tests in build only when specified
if(BUILD_TESTING)
	message("-- Building tests")
	add_subdirectory(test)
endif()
