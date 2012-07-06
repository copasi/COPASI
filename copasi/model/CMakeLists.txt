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
# project (model)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )
# 

file(GLOB HEADERS_MODEL model/*.h)
file(GLOB SOURCES_MODEL model/*.cpp)

# create source group for IDEs
source_group(model FILES ${SOURCES_MODEL} ${HEADERS_MODEL})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_MODEL})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_MODEL})

# set(HEADERS ${HEADERS} CAnnotation.h)
# set(HEADERS ${HEADERS} CChemEq.h)
# set(HEADERS ${HEADERS} CChemEqElement.h)
# set(HEADERS ${HEADERS} CChemEqInterface.h)
# set(HEADERS ${HEADERS} CChemEqParser.h)
# set(HEADERS ${HEADERS} CChemEqParser_yacc.h)
# set(HEADERS ${HEADERS} CCompartment.h)
# set(HEADERS ${HEADERS} CDotOutput.h)
# set(HEADERS ${HEADERS} CEvent.h)
# set(HEADERS ${HEADERS} CMathModel.h)
# set(HEADERS ${HEADERS} CMetab.h)
# set(HEADERS ${HEADERS} CMetabNameInterface.h)
# set(HEADERS ${HEADERS} CMMLOutput.h)
# set(HEADERS ${HEADERS} CModel.h)
# set(HEADERS ${HEADERS} CModelAnalyzer.h)
# set(HEADERS ${HEADERS} CModelExpansion.h)
# set(HEADERS ${HEADERS} CModelMerging.h)
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CModelParameter.h)
# set(HEADERS ${HEADERS} CModelParameter.h)
# set(HEADERS ${HEADERS} CModelParameterGroup.h)
# set(HEADERS ${HEADERS} CModelParameterSet.h)
# endif()
# set(HEADERS ${HEADERS} CModelValue.h)
# set(HEADERS ${HEADERS} CMoiety.h)
# set(HEADERS ${HEADERS} CObjectLists.h)
# set(HEADERS ${HEADERS} CProcessQueue.h)
# set(HEADERS ${HEADERS} CReaction.h)
# set(HEADERS ${HEADERS} CReactionInterface.h)
# set(HEADERS ${HEADERS} CState.h)
# 
# set(SOURCES ${SOURCES} CAnnotation.cpp)
# set(SOURCES ${SOURCES} CChemEq.cpp)
# set(SOURCES ${SOURCES} CChemEqElement.cpp)
# set(SOURCES ${SOURCES} CChemEqInterface.cpp)
# set(SOURCES ${SOURCES} CChemEqParser.cpp)
# set(SOURCES ${SOURCES} CChemEqParser_lex.cpp)
# set(SOURCES ${SOURCES} CChemEqParser_yacc.cpp)
# set(SOURCES ${SOURCES} CCompartment.cpp)
# set(SOURCES ${SOURCES} CDotOutput.cpp)
# set(SOURCES ${SOURCES} CEvent.cpp)
# set(SOURCES ${SOURCES} CMathModel.cpp)
# set(SOURCES ${SOURCES} CMetab.cpp)
# set(SOURCES ${SOURCES} CMetabNameInterface.cpp)
# set(SOURCES ${SOURCES} CMMLOutput.cpp)
# set(SOURCES ${SOURCES} CModel.cpp)
# set(SOURCES ${SOURCES} CModelAnalyzer.cpp)
# set(SOURCES ${SOURCES} CModelExpansion.cpp)
# set(SOURCES ${SOURCES} CModelMerging.cpp)
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CModelParameter.cpp)
# set(SOURCES ${SOURCES} CModelParameter.cpp)
# set(SOURCES ${SOURCES} CModelParameterGroup.cpp)
# set(SOURCES ${SOURCES} CModelParameterSet.cpp)
# endif()
# 
# set(SOURCES ${SOURCES} CModelValue.cpp)
# set(SOURCES ${SOURCES} CMoiety.cpp)
# set(SOURCES ${SOURCES} CObjectLists.cpp)
# set(SOURCES ${SOURCES} CProcessQueue.cpp)
# set(SOURCES ${SOURCES} CReaction.cpp)
# set(SOURCES ${SOURCES} CReactionInterface.cpp)
# set(SOURCES ${SOURCES} CState.cpp)
# 

#add_library(model STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(model math commandline MIRIAM)

