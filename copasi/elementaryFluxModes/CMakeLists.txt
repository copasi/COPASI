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
# project (elementaryFluxModes)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_FEM elementaryFluxModes/*.h)
file(GLOB SOURCES_FEM elementaryFluxModes/*.cpp)

# remove files not used when specific options are disabled
if (NOT COPASI_SSA)
  list(REMOVE_ITEM SOURCES_FEM ${CMAKE_CURRENT_SOURCE_DIR}/elementaryFluxModes/CSSAMethod.cpp)
  list(REMOVE_ITEM HEADERS_FEM ${CMAKE_CURRENT_SOURCE_DIR}/elementaryFluxModes/CSSAMethod.h)
endif(NOT COPASI_SSA)


# create source group for IDEs
source_group(elementaryFluxModes FILES ${SOURCES_FEM} ${HEADERS_FEM})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_FEM})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_FEM})



# set(HEADERS ${HEADERS} CBitPatternMethod.h)
# set(HEADERS ${HEADERS} CBitPatternTreeMethod.h)
# set(HEADERS ${HEADERS} CBitPatternTree.h)
# set(HEADERS ${HEADERS} CBitPatternTreeNode.h)
# set(HEADERS ${HEADERS} CEFMAlgorithm.h)
# set(HEADERS ${HEADERS} CEFMMethod.h)
# set(HEADERS ${HEADERS} CEFMProblem.h)
# set(HEADERS ${HEADERS} CEFMTask.h)
# set(HEADERS ${HEADERS} CFluxMode.h)
# set(HEADERS ${HEADERS} CFluxScore.h)
# set(HEADERS ${HEADERS} CStepMatrix.h)
# set(HEADERS ${HEADERS} CStepMatrixColumn.h)
# set(HEADERS ${HEADERS} CTableauLine.h)
# set(HEADERS ${HEADERS} CTableauMatrix.h)
# set(HEADERS ${HEADERS} CZeroSet.h)
# 
# if (COPASI_SSA)
#    set(HEADERS ${HEADERS} CSSAMethod.h)
# endif (COPASI_SSA)
# 
# 
# 
# set(SOURCES ${SOURCES} CBitPatternMethod.cpp)
# set(SOURCES ${SOURCES} CBitPatternTreeMethod.cpp)
# set(SOURCES ${SOURCES} CBitPatternTree.cpp)
# set(SOURCES ${SOURCES} CBitPatternTreeNode.cpp)
# set(SOURCES ${SOURCES} CEFMAlgorithm.cpp)
# set(SOURCES ${SOURCES} CEFMMethod.cpp)
# set(SOURCES ${SOURCES} CEFMProblem.cpp)
# set(SOURCES ${SOURCES} CEFMTask.cpp)
# set(SOURCES ${SOURCES} CFluxMode.cpp)
# set(SOURCES ${SOURCES} CFluxScore.cpp)
# set(SOURCES ${SOURCES} CStepMatrix.cpp)
# set(SOURCES ${SOURCES} CStepMatrixColumn.cpp)
# set(SOURCES ${SOURCES} CTableauLine.cpp)
# set(SOURCES ${SOURCES} CTableauMatrix.cpp)
# set(SOURCES ${SOURCES} CZeroSet.cpp)
# 
# 
# if (COPASI_SSA)
#    set(SOURCES ${SOURCES} CSSAMethod.cpp)
# endif (COPASI_SSA)
# 
#
#add_library(elementaryFluxModes STATIC ${SOURCES} ${HEADERS})


