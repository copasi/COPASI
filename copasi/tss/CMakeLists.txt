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
#project (tss)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_TSS tss/*.h)
file(GLOB SOURCES_TSS tss/*.cpp)

if(NOT ENABLE_COPASI_TSS)
  list(REMOVE_ITEM SOURCES_TSS
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSMethod.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSProblem.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSTask.cpp
  )
  list(REMOVE_ITEM HEADERS_TSS
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSMethod.h
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSProblem.h
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSTask.h
  )
endif(NOT ENABLE_COPASI_TSS)

# create source group for IDEs
source_group(tss FILES ${SOURCES_TSS} ${HEADERS_TSS})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_TSS})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_TSS})


#set(HEADERS ${HEADERS} CODEExporter.h)
#set(HEADERS ${HEADERS} CODEExporterC.h)
#set(HEADERS ${HEADERS} CODEExporterBM.h)
#set(HEADERS ${HEADERS} CODEExporterXPPAUT.h)
#
#set(SOURCES ${SOURCES} CODEExporter.cpp)
#set(SOURCES ${SOURCES} CODEExporterC.cpp)
#set(SOURCES ${SOURCES} CODEExporterBM.cpp)
#set(SOURCES ${SOURCES} CODEExporterXPPAUT.cpp)
#
#

#add_library(tss STATIC ${SOURCES} ${HEADERS})
#
#target_link_libraries(tss trajectory)
#
