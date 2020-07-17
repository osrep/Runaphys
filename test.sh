#!/bin/tcsh -f
####build test script for Runaphys####

rm -rf build 
mkdir build && cd build
cmake .. && make
cd test
./RuninTests

