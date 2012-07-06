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

cmake_minimum_required (VERSION 2.6)
project (compareExpressions)

# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )
# 
file(GLOB HEADERS_CE compareExpressions/*.h)
file(GLOB SOURCES_CE compareExpressions/*.cpp)

# create source group for IDEs
source_group(compareExpressions FILES ${SOURCES_CE} ${HEADERS_CE})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_CE})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_CE})



# set(HEADERS ${HEADERS} CNormalItem.h)
# set(HEADERS ${HEADERS} CNormalItemPower.h)
# set(HEADERS ${HEADERS} CNormalProduct.h)
# set(HEADERS ${HEADERS} CNormalSum.h)
# set(HEADERS ${HEADERS} CNormalLcm.h)
# set(HEADERS ${HEADERS} CNormalFraction.h)
# set(HEADERS ${HEADERS} CNormalBase.h)
# set(HEADERS ${HEADERS} CNormalChoiceLogical.h)
# set(HEADERS ${HEADERS} CNormalChoice.h)
# set(HEADERS ${HEADERS} CNormalLogical.h)
# set(HEADERS ${HEADERS} CNormalLogicalItem.h)
# set(HEADERS ${HEADERS} CNormalFunction.h)
# set(HEADERS ${HEADERS} CNormalCall.h)
# set(HEADERS ${HEADERS} CNormalGeneralPower.h)
# set(HEADERS ${HEADERS} CNormalTranslation.h)
# set(HEADERS ${HEADERS} ConvertToCEvaluationNode.h)
# set(HEADERS ${HEADERS} CEvaluationNodeNormalizer.h)
# set(HEADERS ${HEADERS} compare_utilities.h)
# 
# set(SOURCES ${SOURCES} CNormalItem.cpp)
# set(SOURCES ${SOURCES} CNormalItemPower.cpp)
# set(SOURCES ${SOURCES} CNormalProduct.cpp)
# set(SOURCES ${SOURCES} CNormalSum.cpp)
# set(SOURCES ${SOURCES} CNormalLcm.cpp)
# set(SOURCES ${SOURCES} CNormalFraction.cpp)
# set(SOURCES ${SOURCES} CNormalChoice.cpp)
# set(SOURCES ${SOURCES} CNormalChoiceLogical.cpp)
# set(SOURCES ${SOURCES} CNormalLogical.cpp)
# set(SOURCES ${SOURCES} CNormalLogicalItem.cpp)
# set(SOURCES ${SOURCES} CNormalFunction.cpp)
# set(SOURCES ${SOURCES} CNormalCall.cpp)
# set(SOURCES ${SOURCES} CNormalGeneralPower.cpp)
# set(SOURCES ${SOURCES} CNormalTranslation.cpp)
# set(SOURCES ${SOURCES} CNormalBase.cpp)
# set(SOURCES ${SOURCES} ConvertToCEvaluationNode.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeNormalizer.cpp)
# set(SOURCES ${SOURCES} compare_utilities.cpp)
# 

#add_library(compareExpressions STATIC ${SOURCES} ${HEADERS})

if (BUILD_TESTS)
  add_subdirectory(compareExpressions/stresstest)
  add_subdirectory(compareExpressions/unittests)
endif(BUILD_TESTS)
