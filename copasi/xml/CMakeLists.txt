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
#project (copasiXML)
#
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)

file(GLOB HEADERS_XML xml/*.h)
file(GLOB SOURCES_XML xml/*.cpp)

# create source group for IDEs
source_group(xml FILES ${SOURCES_XML} ${HEADERS_XML})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_XML})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_XML})



# set(HEADERS ${HEADERS} CCopasiXML.h)
# set(HEADERS ${HEADERS} CCopasiXMLInterface.h)
# set(HEADERS ${HEADERS} CCopasiXMLVersion.h)
# set(HEADERS ${HEADERS} CExpat.h)
# set(HEADERS ${HEADERS} CFixLocalReactionParameters.h)
# set(HEADERS ${HEADERS} CXMLHandler.h)
# set(HEADERS ${HEADERS} CCopasiXMLParser.h)
# 
# set(SOURCES ${SOURCES} CCopasiXML.cpp)
# set(SOURCES ${SOURCES} CCopasiXMLInterface.cpp)
# set(SOURCES ${SOURCES} CExpat.cpp)
# set(SOURCES ${SOURCES} CFixLocalReactionParameters.cpp)
# set(SOURCES ${SOURCES} CCopasiXMLParser.cpp)
# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ListOfModelParameterSets.cpp)
# set(SOURCES ${SOURCES} ListOfModelParameterSets.cpp)
# endif()

#add_library(copasiXML STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(copasiXML function utilities scan elementaryFluxModes steadystate optimization lyap tssanalysis sensitivities moieties lna ${EXPAT_LIBRARY})

