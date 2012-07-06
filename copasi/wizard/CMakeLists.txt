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
# project (wizard)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_WIZARD wizard/*.h  )
file(GLOB FORMS_WIZARD   wizard/*.ui )
file(GLOB SOURCES_WIZARD wizard/*.cpp)

# create source group for IDEs
source_group(wizard FILES ${FORMS_WIZARD} ${HEADERS_WIZARD} ${SOURCES_WIZARD})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_WIZARD})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_WIZARD})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_WIZARD})


# 
# # set(FORMS wizard.ui ${FORMS})
# # 
# # set(HEADERS wizard.h ${HEADERS})
# # 
# # set(SOURCES wizard.cpp ${SOURCES})
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
# INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
# 
# add_library(wizard STATIC ${SOURCES} ${HEADERS} ${HEADERS_FORMS} ${HEADERS_MOC})
# 
# 
# 