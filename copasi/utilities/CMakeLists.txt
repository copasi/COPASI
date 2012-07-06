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
# project (utilities)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_UTILITIES utilities/*.h)
file(GLOB SOURCES_UTILITIES utilities/*.cpp)

list(REMOVE_ITEM SOURCES_UTILITIES 
   ${CMAKE_CURRENT_SOURCE_DIR}/utilities/CWriteConfig.cpp
)



# create source group for IDEs
source_group(utilities FILES ${SOURCES_UTILITIES} ${HEADERS_UTILITIES})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_UTILITIES})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_UTILITIES})

# set(HEADERS ${HEADERS} CAnnotatedMatrix.h)
# set(HEADERS ${HEADERS} CCopasiException.h)
# set(HEADERS ${HEADERS} CCopasiMessage.h)
# set(HEADERS ${HEADERS} CCopasiMethod.h)
# set(HEADERS ${HEADERS} CCopasiNode.h)
# set(HEADERS ${HEADERS} CCopasiParameter.h)
# set(HEADERS ${HEADERS} CCopasiParameterGroup.h)
# set(HEADERS ${HEADERS} CCopasiProblem.h)
# set(HEADERS ${HEADERS} CCopasiTask.h)
# set(HEADERS ${HEADERS} CCopasiTree.h)
# set(HEADERS ${HEADERS} CCopasiVector.h)
# set(HEADERS ${HEADERS} CDependencyGraph.h)
# set(HEADERS ${HEADERS} CDimension.h)
# set(HEADERS ${HEADERS} CDirEntry.h)
# set(HEADERS ${HEADERS} CIndexedPriorityQueue.h)
# set(HEADERS ${HEADERS} CluX.h)
# set(HEADERS ${HEADERS} CMatrix.h)
# set(HEADERS ${HEADERS} copasimathml.h)
# set(HEADERS ${HEADERS} CopasiTime.h)
# set(HEADERS ${HEADERS} COutputHandler.h)
# set(HEADERS ${HEADERS} CProcessReport.h)
# set(HEADERS ${HEADERS} CReadConfig.h)
# set(HEADERS ${HEADERS} CSlider.h)
# set(HEADERS ${HEADERS} CSparseMatrix.h)
# set(HEADERS ${HEADERS} CSort.h)
# set(HEADERS ${HEADERS} CTableCell.h)
# set(HEADERS ${HEADERS} CVector.h)
# set(HEADERS ${HEADERS} CVersion.h)
# set(HEADERS ${HEADERS} messages.h)
# set(HEADERS ${HEADERS} utility.h)
# 
# set(SOURCES ${SOURCES} CAnnotatedMatrix.cpp)
# set(SOURCES ${SOURCES} CCopasiException.cpp)
# set(SOURCES ${SOURCES} CCopasiMessage.cpp)
# set(SOURCES ${SOURCES} CCopasiMethod.cpp)
# set(SOURCES ${SOURCES} CCopasiParameter.cpp)
# set(SOURCES ${SOURCES} CCopasiParameterGroup.cpp)
# set(SOURCES ${SOURCES} CCopasiProblem.cpp)
# set(SOURCES ${SOURCES} CCopasiTask.cpp)
# set(SOURCES ${SOURCES} CDependencyGraph.cpp)
# set(SOURCES ${SOURCES} CDimension.cpp)
# set(SOURCES ${SOURCES} CDirEntry.cpp)
# set(SOURCES ${SOURCES} CIndexedPriorityQueue.cpp)
# set(SOURCES ${SOURCES} CluX.cpp)
# set(SOURCES ${SOURCES} CopasiTime.cpp)
# set(SOURCES ${SOURCES} COutputHandler.cpp)
# set(SOURCES ${SOURCES} CProcessReport.cpp)
# set(SOURCES ${SOURCES} CReadConfig.cpp)
# set(SOURCES ${SOURCES} CSlider.cpp)
# set(SOURCES ${SOURCES} CSparseMatrix.cpp)
# set(SOURCES ${SOURCES} CTableCell.cpp)
# set(SOURCES ${SOURCES} CVersion.cpp)
# set(SOURCES ${SOURCES} utility.cpp)
# 

#add_library(utilities STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(utilities report)


