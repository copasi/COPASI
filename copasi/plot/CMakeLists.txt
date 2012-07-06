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
# project (plot)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_PLOT plot/*.h)
file(GLOB SOURCES_PLOT plot/*.cpp)



# create source group for IDEs
source_group(plot FILES ${SOURCES_PLOT} ${HEADERS_PLOT})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_PLOT})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_PLOT})


# set(HEADERS ${HEADERS} CPlotItem.h)
# set(HEADERS ${HEADERS} CPlotSpecification.h)
# set(HEADERS ${HEADERS} COutputDefinitionVector.h)
# 
# set(SOURCES ${SOURCES} CPlotItem.cpp)
# set(SOURCES ${SOURCES} CPlotSpecification.cpp)
# set(SOURCES ${SOURCES} COutputDefinitionVector.cpp)
# 
#
#add_library(plot STATIC ${SOURCES} ${HEADERS})
#
#target_link_libraries(plot copasiDM)

