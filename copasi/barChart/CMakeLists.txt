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
# project (barChart)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB FORMS_BARCHART   barChart/*.ui )
file(GLOB HEADERS_BARCHART barChart/*.h  )
file(GLOB SOURCES_BARCHART barChart/*.cpp)

# create source group for IDEs
source_group(barChart FILES ${FORMS_BARCHART} ${HEADERS_BARCHART} ${SOURCES_BARCHART})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_BARCHART})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_BARCHART})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_BARCHART})

# if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CQBaseWidget.ui)
# set(FORMS CQBaseWidget.ui ${FORMS})
# set(HEADERS CQBaseWidget.h ${HEADERS})
# set(SOURCES CQBaseWidget.cpp ${SOURCES})
# else()
# set(HEADERS qwt3dBaseWidget.h ${HEADERS})
# set(SOURCES qwt3dBaseWidget.cpp ${SOURCES})
# 
# endif()
# 
# set(HEADERS qwt3dBars.h ${HEADERS})
# set(HEADERS qwt3dScale.h ${HEADERS})
# set(HEADERS qwt3dPlot.h ${HEADERS})
# set(HEADERS qwt3dColor.h ${HEADERS})
#   
# 
# 
# set(SOURCES qwt3dBars.cpp ${SOURCES})
# set(SOURCES qwt3dScale.cpp ${SOURCES})
# set(SOURCES qwt3dPlot.cpp ${SOURCES})
# set(SOURCES qwt3dColor.cpp ${SOURCES})
# 
# include(../CMakeUILib.cmake)
# 
# if (ENABLE_SBW_INTEGRATION)
#   include_directories(${SBW_INCLUDE_DIR})
#   add_definitions(-DCOPASI_SBW_INTEGRATION)
# endif(ENABLE_SBW_INTEGRATION)
#   
# 
# 
# qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
# 
# if(FORMS)
# qt4_wrap_ui(HEADERS_FORMS ${FORMS})
# endif(FORMS)
# 
# include_directories(${CMAKE_CURRENT_BINARY_DIR})
# include_directories(${CMAKE_BINARY_DIR})
# 
# add_library(barChart STATIC ${SOURCES} ${HEADERS} ${HEADERS_FORMS} ${HEADERS_MOC})
# 
# target_link_libraries(barChart ${QWTPLOT3D_LIBRARY} ${OPENGL_gl_LIBRARY})

