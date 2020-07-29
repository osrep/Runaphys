#script that runs gcov coverage measurments
#These commands move the required coverage source to the place where gcov searhes for them


mv $TRAVIS_BUILD_DIR/build/test/CMakeFiles/RunaphysTests.dir/test.cpp.gcno $TRAVIS_BUILD_DIR/test
mv $TRAVIS_BUILD_DIR/build/test/CMakeFiles/RunaphysTests.dir/test.cpp.gcda $TRAVIS_BUILD_DIR/test
mv $TRAVIS_BUILD_DIR/build/src/CMakeFiles/Runaphys.dir/critical_field.cpp.gcno $TRAVIS_BUILD_DIR/src
mv $TRAVIS_BUILD_DIR/build/src/CMakeFiles/Runaphys.dir/critical_field.cpp.gcda $TRAVIS_BUILD_DIR/src
mv $TRAVIS_BUILD_DIR/build/src/CMakeFiles/Runaphys.dir/growth_rate.cpp.gcda $TRAVIS_BUILD_DIR/src
mv $TRAVIS_BUILD_DIR/build/src/CMakeFiles/Runaphys.dir/growth_rate.cpp.gcno $TRAVIS_BUILD_DIR/src
gcov src/critical_field.cpp.cpp 
gcov src/growth_rate.cpp.cpp