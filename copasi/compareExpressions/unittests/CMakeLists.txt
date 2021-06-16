# Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
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
project (compareExpressions-unittests)

include_directories(
	${COPASI_INCLUDE_DIRS}
	${CPPUNIT_INCLUDE_DIR}
)

set(SOURCES
    test.cpp 
    test_depth_first_iterator.cpp  
    test_expression_comparison.cpp 
    test_node_conversion.cpp 
    test_cnormallogical.cpp 
    test_normalform.cpp 
    test_simplify.cpp 
    test_compare_utilities.cpp 
    test_biomodels217_expression.cpp
    ../../sbml/unittests/utilities.cpp
)

add_executable(compareExpressions-unittests ${SOURCES})

target_link_libraries(compareExpressions-unittests libCOPASISE-static ${CPPUNIT_LIBRARY})

add_test(NAME run_compareExpressions_unittests COMMAND ${CMAKE_CURRENT_BINARY_DIR}/compareExpressions-unittests )
set_tests_properties(run_compareExpressions_unittests PROPERTIES FAIL_REGULAR_EXPRESSION "!!!FAILURES!!!")
