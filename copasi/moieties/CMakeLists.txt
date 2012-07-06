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
#project (moieties)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_MOIETIES moieties/*.h)
file(GLOB SOURCES_MOIETIES moieties/*.cpp)

# create source group for IDEs
source_group(moieties FILES ${SOURCES_MOIETIES} ${HEADERS_MOIETIES})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_MOIETIES})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_MOIETIES})

# set(HEADERS ${HEADERS} CMoietiesMethod.h)
# set(HEADERS ${HEADERS} CMoietiesProblem.h)
# set(HEADERS ${HEADERS} CMoietiesTask.h)
# 
# set(SOURCES ${SOURCES} CMoietiesMethod.cpp)
# set(SOURCES ${SOURCES} CMoietiesProblem.cpp)
# set(SOURCES ${SOURCES} CMoietiesTask.cpp)
# 

#add_library(moieties STATIC ${SOURCES} ${HEADERS})


