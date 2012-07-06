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
#project (scan)
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_SCAN scan/*.h)
file(GLOB SOURCES_SCAN scan/*.cpp)


# create source group for IDEs
source_group(scan FILES ${SOURCES_SCAN} ${HEADERS_SCAN})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_SCAN})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_SCAN})



# set(HEADERS ${HEADERS} CScanMethod.h)
# set(HEADERS ${HEADERS} CScanProblem.h)
# set(HEADERS ${HEADERS} CScanTask.h)
# 
# set(SOURCES ${SOURCES} CScanMethod.cpp)
# set(SOURCES ${SOURCES} CScanProblem.cpp)
# set(SOURCES ${SOURCES} CScanTask.cpp)
# 

#add_library(scan STATIC ${SOURCES} ${HEADERS})


