#script that runs gcov coverage measurments
#These commands move the required coverage source to the place where gcov searhes for them


mv ./build/test/CMakeFiles/RunaphysTests.dir/tests.cpp.gcno $TRAVIS_BUILD_DIR/test
mv ./build/test/CMakeFiles/RunaphysTests.dir/tests.cpp.gcda $TRAVIS_BUILD_DIR/test
mv ./build/src/CMakeFiles/Runaphys.dir/critical_field.cpp.gcno $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/critical_field.cpp.gcda $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/growth_rate.cpp.gcda $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/growth_rate.cpp.gcno $TRAVIS_BUILD_DIR/src

mv ./build/src/CMakeFiles/Runaphys.dir/avalanche.cpp.gcno $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/avalanche.cpp.gcda $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/control.cpp.gcno $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/control.cpp.gcda $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/dreicer.cpp.gcno $TRAVIS_BUILD_DIR/src
mv ./build/src/CMakeFiles/Runaphys.dir/dreicer.cpp.gcda $TRAVIS_BUILD_DIR/src


gcov src/critical_field.cpp.cpp 
gcov src/growth_rate.cpp.cpp
gcov src/avalanche.cpp.cpp
gcov src/control.cpp.cpp
gcov src/dreicer.cpp.cpp