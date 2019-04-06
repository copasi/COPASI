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

cmake_minimum_required (VERSION 3.0)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project (catch-test  VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")

include_directories("${PROJECT_SOURCE_DIR}/.." "${PROJECT_SOURCE_DIR}/../copasi" "${PROJECT_SOURCE_DIR}")

file(GLOB TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)


include(../copasi/common.cmake)
include(../copasi/CMakeConsoleApp.cmake)


add_executable(catch-test ${TEST_SOURCES})
add_dependencies(catch-test ${SE_DEPENDENCIES}) 
target_link_libraries(catch-test libCOPASISE-static ${SE_LIBS} ${SE_EXTERNAL_LIBS} )


add_test(test_catch_run ${CMAKE_CURRENT_BINARY_DIR}/catch-test )
set_tests_properties(test_catch_run PROPERTIES ENVIRONMENT 
  "srcdir=${CMAKE_CURRENT_SOURCE_DIR}")

