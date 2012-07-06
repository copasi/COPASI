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
#project (sensitivities)
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_SENSE sensitivities/*.h)
file(GLOB SOURCES_SENSE sensitivities/*.cpp)

# create source group for IDEs
source_group(sensitivities FILES ${SOURCES_SENSE} ${HEADERS_SENSE})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_SENSE})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_SENSE})


# 
# set(HEADERS ${HEADERS} CSensMethod.h)
# set(HEADERS ${HEADERS} CSensProblem.h)
# set(HEADERS ${HEADERS} CSensTask.h)
# 
# set(SOURCES ${SOURCES} CSensMethod.cpp)
# set(SOURCES ${SOURCES} CSensProblem.cpp)
# set(SOURCES ${SOURCES} CSensTask.cpp)
# 
# 
#add_library(sensitivities STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(sensitivities utilities)


