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

#cmake_minimum_required (VERSION 2.6)
#project (lna)
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_LNA lna/*.h)
file(GLOB SOURCES_LNA lna/*.cpp)

if (SOURCES_LNA)
# create source group for IDEs
source_group(lna FILES ${SOURCES_LNA} ${HEADERS_LNA})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_LNA})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_FUN})


endif(SOURCES_LNA)

# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CLNAMethod.h)
# 
# 
# set(HEADERS ${HEADERS} CLNAMethod.h)
# set(HEADERS ${HEADERS} CLNAProblem.h)
# set(HEADERS ${HEADERS} CLNATask.h)
# 
# set(SOURCES ${SOURCES} CLNAMethod.cpp)
# set(SOURCES ${SOURCES} CLNAProblem.cpp)
# set(SOURCES ${SOURCES} CLNATask.cpp)
# 

# we need some sources
#if (NOT SOURCES)
#file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/lna.cpp "#include <copasi.h>" )
#set (SOURCES ${CMAKE_CURRENT_BINARY_DIR}/lna.cpp)
#endif(NOT SOURCES)
#
#add_library(lna STATIC ${SOURCES} ${HEADERS})

# else()
# 
# file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/lna.cpp "#include <copasi.h>" )
# add_library(lna STATIC ${CMAKE_CURRENT_BINARY_DIR}/lna.cpp)
# 
# endif()
