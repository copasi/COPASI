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
# project (commandline)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )
# 
file(GLOB HEADERS_COMMANDLINE commandline/*.h)
file(GLOB SOURCES_COMMANDLINE commandline/*.cpp)

# create source group for IDEs
source_group(commandline FILES ${SOURCES_COMMANDLINE} ${HEADERS_COMMANDLINE})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_COMMANDLINE})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_COMMANDLINE})



# set(HEADERS ${HEADERS} CConfigurationFile.h)
# set(HEADERS ${HEADERS} CLocaleString.h)
# set(HEADERS ${HEADERS} COptionParser.h)
# set(HEADERS ${HEADERS} COptions.h)
# 
# 
# set(SOURCES ${SOURCES} CConfigurationFile.cpp)
# set(SOURCES ${SOURCES} CLocaleString.cpp)
# set(SOURCES ${SOURCES} COptionParser.cpp)
# set(SOURCES ${SOURCES} COptions.cpp)

# add_library(commandline STATIC ${SOURCES} ${HEADERS})
# 
# target_link_libraries(commandline copasiXML)
# 
