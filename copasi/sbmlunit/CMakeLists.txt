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
# project (sbmlunit)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )
# 
file(GLOB HEADERS_SBMLUNIT sbmlunit/*.h)
file(GLOB SOURCES_SBMLUNIT sbmlunit/*.cpp)

# create source group for IDEs
source_group(sbmlunit FILES ${SOURCES_SBMLUNIT} ${HEADERS_SBMLUNIT})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_SBMLUNIT})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_SBMLUNIT})


# 
# set(HEADERS ${HEADERS} CUnitInterfaceSBML.h)
# set(HEADERS ${HEADERS} CUnit.h)
# set(HEADERS ${HEADERS} Expression2PresentationMML.h)
# set(HEADERS ${HEADERS} Expression2PresentationMMLUnits.h)
# 
# set(SOURCES ${SOURCES} CUnitInterfaceSBML.cpp)
# set(SOURCES ${SOURCES} CUnit.cpp)
# set(SOURCES ${SOURCES} Expression2PresentationMML.cpp)
# set(SOURCES ${SOURCES} Expression2PresentationMMLUnits.cpp)
# 

#add_library(sbmlunit STATIC ${SOURCES} ${HEADERS})


