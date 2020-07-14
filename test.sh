#!/bin/tcsh -f
####build test script for Runaphys####

mkdir build && cd build
cmake .. && make
cd test
./RuninTests

