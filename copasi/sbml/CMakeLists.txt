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
#project (sbmlimport)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)
# 

file(GLOB HEADERS_SBML sbml/*.h)
file(GLOB SOURCES_SBML sbml/*.cpp)

if(NOT ENABLE_CELLDESIGNER_IMPORT)
 list(REMOVE_ITEM SOURCES_SBML ${CMAKE_CURRENT_SOURCE_DIR}/sbml/CCellDesignerImporter.cpp)
 list(REMOVE_ITEM HEADERS_SBML ${CMAKE_CURRENT_SOURCE_DIR}/sbml/CCellDesignerImporter.h)
endif(NOT ENABLE_CELLDESIGNER_IMPORT)


# create source group for IDEs
source_group(sbml FILES ${SOURCES_SBML} ${HEADERS_SBML})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_SBML})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_SBML})

# set(HEADERS ${HEADERS} StdException.h)
# set(HEADERS ${HEADERS} CSBMLExporter.h)
# set(HEADERS ${HEADERS} ConverterASTNode.h)
# set(HEADERS ${HEADERS} SBMLImporter.h)
# set(HEADERS ${HEADERS} SBMLIncompatibility.h)
# set(HEADERS ${HEADERS} SBMLReference.h)
# set(HEADERS ${HEADERS} SBMLUtils.h)
# set(HEADERS ${HEADERS} UnitConversionFactory.hpp)
# set(HEADERS ${HEADERS} incompatibilities.h)
# 
# 
# set(SOURCES ${SOURCES} StdException.cpp)
# set(SOURCES ${SOURCES} CSBMLExporter.cpp)
# set(SOURCES ${SOURCES} ConverterASTNode.cpp)
# set(SOURCES ${SOURCES} SBMLImporter.cpp)
# set(SOURCES ${SOURCES} SBMLIncompatibility.cpp)
# set(SOURCES ${SOURCES} SBMLReference.cpp)
# set(SOURCES ${SOURCES} SBMLUtils.cpp)
# set(SOURCES ${SOURCES} UnitConversionFactory.cpp)
# 
# if(ENABLE_CELLDESIGNER_IMPORT)
# if (EXISTS  ${CMAKE_CURRENT_SOURCE_DIR}/CCellDesignerImporter.cpp)
#   set(HEADERS ${HEADERS} CCellDesignerImporter.h)
#   set(SOURCES ${SOURCES} CCellDesignerImporter.cpp)
# endif()
# endif(ENABLE_CELLDESIGNER_IMPORT)
# 
#add_library(sbmlimport STATIC ${SOURCES} ${HEADERS})
#
#target_link_libraries(sbmlimport compareExpressions layout)

if (BUILD_TESTS)
add_subdirectory(sbml/unittests)
endif(BUILD_TESTS)