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

# only create this example if we build the gui
if (BUILD_GUI)

cmake_minimum_required (VERSION 2.6)
project (renderLayout)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 OLD)
endif(POLICY CMP0020)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 OLD)
endif(POLICY CMP0048)

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 OLD)
endif(POLICY CMP0043)

set(SOURCES ${SOURCES} main.cpp)

# set up include directory for the COPASI library
include(${CMAKE_SOURCE_DIR}/copasi/CMakeUIApp.cmake)

add_executable(renderLayout ${SOURCES} ${HEADERS})
add_dependencies(renderLayout ${SE_DEPENDENCIES}) 
target_link_libraries(renderLayout libCOPASIUI ${SE_LIBS} ${SE_EXTERNAL_LIBS})

endif(BUILD_GUI)