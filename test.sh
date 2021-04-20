#!/bin/tcsh -f
####build test script for Runaphys####

rm -rf build 
mkdir build && cd build
cmake .. && make
cd test
./RunaphysTests
cd .. 
cmake .. -DBUILD_DLL=true && make
cd ../test
python3 python_test.py

