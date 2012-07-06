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

# cmake_minimum_required (VERSION 2.6)
# project (fitting)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_FITTING parameterFitting/*.h)
file(GLOB SOURCES_FITTING parameterFitting/*.cpp)

# create source group for IDEs
source_group(fitting FILES ${SOURCES_FITTING} ${HEADERS_FITTING})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_FITTING})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_FITTING})


# set(HEADERS ${HEADERS} CExperiment.h)
# set(HEADERS ${HEADERS} CExperimentSet.h)
# set(HEADERS ${HEADERS} CExperimentObjectMap.h)
# set(HEADERS ${HEADERS} CExperimentFileInfo.h)
# set(HEADERS ${HEADERS} CFitItem.h)
# set(HEADERS ${HEADERS} CFitMethod.h)
# set(HEADERS ${HEADERS} CFitProblem.h)
# set(HEADERS ${HEADERS} CFitTask.h)
# 
# set(SOURCES ${SOURCES} CExperiment.cpp)
# set(SOURCES ${SOURCES} CExperimentSet.cpp)
# set(SOURCES ${SOURCES} CExperimentObjectMap.cpp)
# set(SOURCES ${SOURCES} CExperimentFileInfo.cpp)
# set(SOURCES ${SOURCES} CFitItem.cpp)
# set(SOURCES ${SOURCES} CFitMethod.cpp)
# set(SOURCES ${SOURCES} CFitProblem.cpp)
# set(SOURCES ${SOURCES} CFitTask.cpp)
# 

#add_library(fitting STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(fitting utilities)
#
