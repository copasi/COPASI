# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
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

cmake_minimum_required (VERSION 2.6)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project (runScan VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")

include_directories("${PROJECT_SOURCE_DIR}/../../.." "${PROJECT_SOURCE_DIR}/../../../.." "${PROJECT_SOURCE_DIR}")

set(SOURCES ${SOURCES} runScan.cpp)

include(../../../CMakeConsoleApp.cmake)

add_executable(runScan ${SOURCES} ${HEADERS})
add_dependencies(runScan ${SE_DEPENDENCIES}) 
target_link_libraries(runScan ${SE_LIBS} ${SE_EXTERNAL_LIBS})
