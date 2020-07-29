cmake_minimum_required(VERSION 3.1)

project(Runaphys VERSION 1.0.0
              LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

# TODO check flags to use
set(CMAKE_CXX_FLAGS "-Wall -ggdb -O3 -fPIC -march=native -mno-avx -fprofile-arcs -ftest-coverage -fprofile-dir test")

include_directories("include")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory(src)
include(CodeCoverage)
#append_coverage_compiler_flags()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

# Include tests in build only when specified
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(test)
endif()
