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
#project (tssanalysis)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_TSSANALYSIS tssanalysis/*.h)
file(GLOB SOURCES_TSSANALYSIS tssanalysis/*.cpp)


# create source group for IDEs
source_group(tssanalysis FILES ${SOURCES_TSSANALYSIS} ${HEADERS_TSSANALYSIS})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_TSSANALYSIS})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_TSSANALYSIS})


# set(HEADERS ${HEADERS} CILDMMethod.h)
# set(HEADERS ${HEADERS} CILDMModifiedMethod.h)
# set(HEADERS ${HEADERS} CTSSAMethod.h)
# set(HEADERS ${HEADERS} CTSSAProblem.h)
# set(HEADERS ${HEADERS} CTSSATask.h)
# set(HEADERS ${HEADERS} CCSPMethod.h)
# 
# set(SOURCES ${SOURCES} CILDMMethod.cpp)
# set(SOURCES ${SOURCES} CILDMModifiedMethod.cpp)
# set(SOURCES ${SOURCES} CTSSAMethod.cpp)
# set(SOURCES ${SOURCES} CTSSAProblem.cpp)
# set(SOURCES ${SOURCES} CTSSATask.cpp)
# set(SOURCES ${SOURCES} CCSPMethod.cpp)
# 

#add_library(tssanalysis STATIC ${SOURCES} ${HEADERS})


