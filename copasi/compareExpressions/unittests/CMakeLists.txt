###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., University of Heidelberg, and The University
# of Manchester.
# All rights reserved.
# 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.
# 
# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.
#
###############################################################################

cmake_minimum_required (VERSION 2.6)
project (compareExpressions-unittests)

include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/copasi
	${PROJECT_SOURCE_DIR}
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

include(../../common.cmake)
include(../../CMakeConsoleApp.cmake)


add_executable(compareExpressions-unittests ${SOURCES})

add_dependencies(compareExpressions-unittests ${SE_DEPENDENCIES}) 
target_link_libraries(compareExpressions-unittests ${SE_EXTERNAL_LIBS} ${SE_LIBS} ${CPPUNIT_LIBRARY})

add_test(NAME run_compareExpressions_unittests COMMAND ${CMAKE_CURRENT_BINARY_DIR}/compareExpressions-unittests )
set_tests_properties(run_compareExpressions_unittests PROPERTIES FAIL_REGULAR_EXPRESSION "!!!FAILURES!!!")