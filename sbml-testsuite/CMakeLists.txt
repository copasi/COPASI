# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################

cmake_minimum_required (VERSION 2.8.12)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project (sbml-testsuite  VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")


set(SOURCES ${SOURCES} wrapper.cpp)

add_executable(sbml-testsuite ${SOURCES})
target_link_libraries(sbml-testsuite libCOPASISE-static)

install(TARGETS sbml-testsuite DESTINATION bin)


option(SBML_TESTSUITE_RUN "Run the SBML testsuite as test" OFF)

if (SBML_TESTSUITE_RUN)

set(SBML_TESTSUITE_CASES_DIR "" CACHE PATH "full path to the cases/semantic directory of the SBML Testsuite")
set(SBML_TESTSUITE_LEVEL "3" CACHE STRING "The SBML Level to test (or 0 to test the highest available one)")
set(SBML_TESTSUITE_VERSION "1" CACHE STRING "The SBML Version to test (or 0 to test the highest available one)")
set(SBML_TESTSUITE_THREADS "8" CACHE STRING "Number of threads to run in parallel when running the test suite")
set(SBML_TESTSUITE_UNSUPPORTED "" CACHE STRING "Comma separated list of unsupported test tags (or empty for default selection)")
option(SBML_TESTSUITE_REMOVE_WRAPPER "remove the wrapper after finishing tests" OFF)


if (NOT EXISTS ${SBML_TESTSUITE_CASES_DIR})
  message(FATAL_ERROR "Need to specify the cases/semantic directory in order to run the tests suite")
endif()

if (NOT Java_JAVA_EXECUTABLE)
find_package(Java COMPONENTS Development REQUIRED)
endif()

add_test(
  NAME test_sbml_testsuite
  COMMAND "${CMAKE_COMMAND}"
         -DFILE_SEP="${FILE_SEP}"
         -DCASES_DIR=${SBML_TESTSUITE_CASES_DIR}
         -DNUM_THREADS=${SBML_TESTSUITE_THREADS}
         -DSBML_LEVEL=${SBML_TESTSUITE_LEVEL}
         -DSBML_VERSION=${SBML_TESTSUITE_VERSION}
         -DJAVA_EXECUTABLE=${Java_JAVA_EXECUTABLE}
         -DWRAPPER_EXECUTABLE=$<TARGET_FILE:sbml-testsuite>
         -DUNSUPPORTED="${SBML_TESTSUITE_UNSUPPORTED}"
         -DOUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/out
         -DSRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}
         -DVERSION=${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
         -DREMOVE_WRAPPER=${SBML_TESTSUITE_REMOVE_WRAPPER}
         -P "${CMAKE_CURRENT_SOURCE_DIR}/run_suite.cmake"
)
set_tests_properties(test_sbml_testsuite PROPERTIES PASS_REGULAR_EXPRESSION "All passed|RandomEventExecution")
set_tests_properties(test_sbml_testsuite PROPERTIES FAIL_REGULAR_EXPRESSION "Exceptions .* occured for:")

endif()
