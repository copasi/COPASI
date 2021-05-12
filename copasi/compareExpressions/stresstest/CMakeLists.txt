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
project (compareExpressions-stresstest)

include_directories(
	${COPASI_INCLUDE_DIRS}
	${CPPUNIT_INCLUDE_DIR}
)

set(SOURCES stress_test.cpp)
set(HEADERS stress_test.h)

add_executable(compareExpressions-stresstest ${SOURCES} ${HEADERS})

target_link_libraries(compareExpressions-stresstest libCOPASISE-static ${CPPUNIT_LIBRARY})

add_test(run_compareExpressions_stresstest compareExpressions-stresstest)
