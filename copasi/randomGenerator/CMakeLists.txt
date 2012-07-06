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
#project (randomGenerator)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_RAND randomGenerator/*.h)
file(GLOB SOURCES_RAND randomGenerator/*.cpp)


# create source group for IDEs
source_group(randomGenerator FILES ${SOURCES_RAND} ${HEADERS_RAND})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_RAND})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_RAND})

# set(HEADERS ${HEADERS} Cmt19937.h)
# set(HEADERS ${HEADERS} Cr250.h)
# set(HEADERS ${HEADERS} CRandom.h)
# 
# set(SOURCES ${SOURCES} Cmt19937.cpp)
# set(SOURCES ${SOURCES} Cr250.cpp)
# set(SOURCES ${SOURCES} CRandom.cpp)
# 

#add_library(randomGenerator STATIC ${SOURCES} ${HEADERS})


