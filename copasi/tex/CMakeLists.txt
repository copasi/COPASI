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

# cmake_minimum_required (VERSION 2.8)
# project (tex)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_TEX tex/*.h)
file(GLOB SOURCES_TEX tex/*.cpp)

# create source group for IDEs
source_group(tex FILES ${HEADERS_TEX} ${SOURCES_TEX})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_TEX})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_TEX})


# 
# set(HEADERS CMathMLToTeX.h  ${HEADERS})
# set(HEADERS CStructureParser.h ${HEADERS})
# 
# set(SOURCES CMathMLToTeX.cpp ${SOURCES})
# set(SOURCES CStructureParser.cpp ${SOURCES})
# 

# include(../CMakeUILib.cmake)
# 
# qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
# 
# if(FORMS)
# qt4_wrap_ui(HEADERS_FORMS ${FORMS})
# endif(FORMS)
# 
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# INCLUDE_DIRECTORIES(${QT_QTXML_INCLUDE_DIR})
# 
# add_library(tex STATIC ${SOURCES} ${HEADERS} ${HEADERS_FORMS} ${HEADERS_MOC})
# 


