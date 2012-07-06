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
# project (math)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_MATH math/*.h)
file(GLOB SOURCES_MATH math/*.cpp)

if (SOURCES_MATH)
# create source group for IDEs
source_group(math FILES ${SOURCES_MATH} ${HEADERS_MATH})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_MATH})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_MATH})


endif(SOURCES_MATH)


#add_library(math STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(math model)
#

# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMathDependencyGraph.h)
# 
# set(HEADERS ${HEADERS} CMathDependencyGraph.h)
# set(HEADERS ${HEADERS} CMathDependencyNode.h)
# set(HEADERS ${HEADERS} CMathExpression.h)
# set(HEADERS ${HEADERS} CMathContainer.h)
# set(HEADERS ${HEADERS} CMathEnum.h)
# set(HEADERS ${HEADERS} CMathEvent.h)
# set(HEADERS ${HEADERS} CMathObject.h)
# set(HEADERS ${HEADERS} CMathTrigger.h)
# 
# set(SOURCES ${SOURCES} CMathDependencyGraph.cpp)
# set(SOURCES ${SOURCES} CMathDependencyNode.cpp)
# set(SOURCES ${SOURCES} CMathExpression.cpp)
# set(SOURCES ${SOURCES} CMathContainer.cpp)
# set(SOURCES ${SOURCES} CMathEnum.cpp)
# set(SOURCES ${SOURCES} CMathEvent.cpp)
# set(SOURCES ${SOURCES} CMathObject.cpp)
# set(SOURCES ${SOURCES} CMathTrigger.cpp)
# 
# add_library(math STATIC ${SOURCES} ${HEADERS})
# target_link_libraries(math model)
# 
# else()
# 
# set(SOURCES ${SOURCES} ../model/CMathModel.cpp)
# set(SOURCES ${SOURCES} ../model/CMathEvent.cpp)
# set(SOURCES ${SOURCES} ../model/CMathTrigger.cpp)
# add_library(math STATIC ${SOURCES} ${HEADERS})
# 
# endif()
# 