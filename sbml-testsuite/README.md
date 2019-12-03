## SBML Test suite
This document describes running the semantic SBML Testsuite ([1]) for COPASI. This test suite contains a number of cases of increasing complexity that uses all the different features encodable by SBML in turn. It is possible to run the SBML test suite as part of the cmake test procedure of COPASI. All that is necessary for that is to: 

1. download & exctract an archive of the SBML Test suite cases
2. ensure you have a Java runtime environment installed (so it is findable by cmake)
3. configure the build so the test suite runner is built
4. run the test suite via ctest / via SBML Test Runner GUI 

### Obtaining the Test suite cases
Here you can either take an official release of the semantic test suite archives as available from github: 

* <https://github.com/sbmlteam/sbml-test-suite/releases>

You only need the semantic cases such as: 

* <https://github.com/sbmlteam/sbml-test-suite/releases/download/3.3.0/sbml-semantic-test-cases-2017-12-12.zip>

or you could clone the repository:

	git clone https://github.com/sbmlteam/sbml-test-suite.git

*NOTE*: for later you will need the full path to the `sbml-test-suite/cases/semantic` directory. 

### Configuring the COPASI build
At the bare minimum you need the [test wrapper](wrapper.cpp)  executable compiled and available. This wrapper parses the test description, generates the COPASI file with the specified output and then simulates the model. The test wrapper is not compiled automatically, you will need to supply the cmake build option: 

 * `-DBUILD_SEMANTIC_TESTSUITE=ON`

if COPASI is compiled with that option, the `sbml-testsuite` executable will be placed into this folder. 

#### Configuring the CTest Parameters

To run the SBML test suite automatically via CTest, we have the following additional cmake parameters: 

* `-DSBML_TESTSUITE_RUN=ON`: specify that ctest should run the test suite (required)
* `-DSBML_TESTSUITE_CASES_DIR=<path>`: the full path to the cases/semantic directory from above (required)
* `-DSBML_TESTSUITE_LEVEL=<num>`: the sbml level to test (defaults to 3)
* `-DSBML_TESTSUITE_VERSION=<num>`: the sbml vesion to test (defaults to 1)
* `-DSBML_TESTSUITE_UNSUPPORTED=<list>`: the list of test / component tags that are considered unsupported (defaults to the known list of unsupported features: "AlgebraicRule,CSymbolDelay,CSymbolRateOf,AssignedVariableStoichiometry,FastReaction, VolumeConcentrationRates,L3v2MathML,BoolNumericSwap,fbc")
* `-DSBML_TESTSUITE_THREADS=<num>`: number of threads the testrunner may use to run in parallel (defaults to 8, i.e; 8 parallel running test cases each time)
* `-DSBML_TESTSUITE_REMOVE_WRAPPER=<bool>`: a flag whether the test runner should be removed from the list of known test runners for the sbml test suite. (defaults to OFF)

Cmake will be trying to find the java interpreter to use. In case that is not successful you may want to specify a full path to your java executable in the option `-DJava_JAVA_EXECUTABLE=<full path to java>`. 

After the configuration is done, build COPASI. For more information on how to build COPASI see also the documentation in the [root folder](../README.md). At that point the binary directory should have the `sbml-testsuite` executable present. Please *NOTE* the full path to it for the next step. 

### Run with CTest

When configured as above in the build folder a call to: 

	ctest -R sbml 

will execute the SBML test suite since there are 1780 cases, that might take a while. Unfortunately CTest does not provide much output along the way. You might thus opt to display more information by running:

	ctest -R sbml -V

which should provide output like: 

	copasi@cdash-copasi:~/Development/build_copasi# ctest -R sbml -V
    UpdateCTestConfiguration  from :/copasi/Development/build_copasi/DartConfiguration.tcl
    Parse Config file:/copasi/Development/build_copasi/DartConfiguration.tcl
    UpdateCTestConfiguration  from :/copasi/Development/build_copasi/DartConfiguration.tcl
    Parse Config file:/copasi/Development/build_copasi/DartConfiguration.tcl
    Test project /copasi/Development/build_copasi
    Constructing a list of tests
    Done constructing a list of tests
    Updating test list for fixtures
    Added 0 tests to meet fixture requirements
    Checking test dependency graph...
    Checking test dependency graph end
    test 2
        Start 2: test_sbml_testsuite
    
    2: Test command: /usr/bin/cmake "-DFILE_SEP=":"" "-DCASES_DIR=/copasi/Development/sbml-test-suite/cases/semantic" "-DNUM_THREADS=8" "-DSBML_LEVEL=3" "-DSBML_VERSION=1" "-DJAVA_EXECUTABLE=/usr/bin/java" "-DWRAPPER_EXECUTABLE=/copasi/Development/build_copasi/sbml-testsuite/sbml-testsuite" "-DUNSUPPORTED=""" "-DOUT_DIR=/copasi/Development/build_copasi/sbml-testsuite/out" "-DSRC_DIR=/copasi/Development/COPASI/sbml-testsuite" "-DVERSION=4.26.210" "-DREMOVE_WRAPPER=OFF" "-P" "/copasi/Development/COPASI/sbml-testsuite/run_suite.cmake"
    2: Test timeout computed to be: 3000
    2: -- Not supporting: 'AlgebraicRule,CSymbolDelay,CSymbolRateOf,AssignedVariableStoichiometry,FastReaction, VolumeConcentrationRates,L3v2MathML,BoolNumericSwap,fbc'
    2: -- initialize testsuite
    2: -- remove wrapper COPASI 4.27.217 if it exists
    2: -- add wrapper COPASI 4.27.217
    2: -- run wrapper COPASI 4.27.217 with #threads:8 for SBML L3V1
    2: .................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
    2: All passed.
    2:
    2: ...done
    1/1 Test #2: test_sbml_testsuite ..............   Passed  200.39 sec
    
    The following tests passed:
            test_sbml_testsuite
    
    100% tests passed, 0 tests failed out of 1


### Run using the SBML Testsuite Runner
If you have installed the graphical test suite runner, and you ran the ctest before, you should already find the COPASI wrapper registered in the list of wrappers. If not, you can do so manually, by starting the test runner and selected the configuration screen and entering the values as in the screenshot below: 

![SBML Test wrapper configuration](https://cl.ly/21a77100b35b/[210d7621cf2affe85fe9881f0943ef3c]_Image%202019-12-03%20at%204.49.18%20PM.png)

### References

[1]: http://sbml.org/Software/SBML_Test_Suite 