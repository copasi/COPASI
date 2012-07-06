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
#project (steadystate)
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)
# 

file(GLOB HEADERS_STEADY steadystate/*.h)
file(GLOB SOURCES_STEADY steadystate/*.cpp)

# create source group for IDEs
source_group(steadystate FILES ${SOURCES_STEADY} ${HEADERS_STEADY})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_STEADY})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_STEADY})




# set(HEADERS ${HEADERS} CEigen.h)
# set(HEADERS ${HEADERS} CMCAMethod.h)
# set(HEADERS ${HEADERS} CMCAProblem.h)
# set(HEADERS ${HEADERS} CMCATask.h)
# set(HEADERS ${HEADERS} CNewtonMethod.h)
# set(HEADERS ${HEADERS} CSteadyStateMethod.h)
# set(HEADERS ${HEADERS} CSteadyStateProblem.h)
# set(HEADERS ${HEADERS} CSteadyStateTask.h)
# 
# set(SOURCES ${SOURCES} CEigen.cpp)
# set(SOURCES ${SOURCES} CMCAMethod.cpp)
# set(SOURCES ${SOURCES} CMCAProblem.cpp)
# set(SOURCES ${SOURCES} CMCATask.cpp)
# set(SOURCES ${SOURCES} CNewtonMethod.cpp)
# set(SOURCES ${SOURCES} CSteadyStateMethod.cpp)
# set(SOURCES ${SOURCES} CSteadyStateProblem.cpp)
# set(SOURCES ${SOURCES} CSteadyStateTask.cpp)
# 


#add_library(steadystate STATIC ${SOURCES} ${HEADERS})


