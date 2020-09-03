 [![Build Status](https://travis-ci.com/osrep/Runaphys.svg?branch=master)](https://travis-ci.com/osrep/Runaphys) [![Sonarcloud Status](https://sonarcloud.io/api/project_badges/measure?project=com.lapots.breed.judge:judge-rule-engine&metric=alert_status)](https://sonarcloud.io/dashboard?id=osrep_Runaphys)
# About Runaphys
Repository for the physics modules of the Runin and Runafluid actors.

# How to build
Building Runaphys requires cmake version 3.1 or above. To build the library you have to run the following commands:

`mkdir build && cd build #creates the folder where the build files are created.
cmake .. && make`

This will create Runaphys.a in the build folder. 

If you want to build the library and also run the tests simply type:

`./test.sh`

This will create Runaphys.a in the build folder and also run the test cases.

# References

Runaway Fluid is maintained under a Github repository dedicated to runaway electron physics. The project’s basic description, documentation and source code is stored in the Github project https://github.com/osrep.

Analytical formula used to determine the critical electric field is based on the work of A. Stahl et al [1]. The method of calculating Dreicer runaway generation growth rate stems from the article of J. W. Connor et al [2]. The runaway avalanche growth rate is based on the form in the article by E. Nilsson [3].

[1] A. Stahl, E. Hirvijoki, J. Decker, O. Embréus, and T. Fülöp. Effective Critical Electric Field for Runaway-Electron Generation. Physical Review Letters 114(11), 115002 (2015) [2] J.W. Connor and R.J. Hastie. Relativistic limitations on runaway electrons. Nuclear Fusion 15, 415 (1975) [3] E. Nilsson, J. Decker, N.J.Fisch, Y. Peysson. Trapped-Electron Runaway Effect. Journal of Plasma Physics 81(4), 475810403 (2015) [4] G.I. Pokol, et. al, Runaway electron modelling in the self-consistent core European Transport Simulator, ETS, Nuclear Fusion 59, 076024 (2019)
