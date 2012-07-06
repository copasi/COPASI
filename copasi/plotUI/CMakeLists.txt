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
# project (plotUI)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_PLOTUI plotUI/*.h  )
file(GLOB FORMS_PLOTUI   plotUI/*.ui )
file(GLOB SOURCES_PLOTUI plotUI/*.cpp)

if (NOT COPASI_BANDED_GRAPH)
 list(REMOVE_ITEM HEADERS_PLOTUI ${CMAKE_CURRENT_SOURCE_DIR}/plotUI/BandedGraphWidget.h )
 list(REMOVE_ITEM FORMS_PLOTUI   ${CMAKE_CURRENT_SOURCE_DIR}/plotUI/BandedGraphWidget.ui )
 list(REMOVE_ITEM SOURCES_PLOTUI ${CMAKE_CURRENT_SOURCE_DIR}/plotUI/BandedGraphWidget.cpp )
  
endif(NOT COPASI_BANDED_GRAPH)

# create source group for IDEs
source_group(plotUI FILES ${FORMS_PLOTUI} ${HEADERS_PLOTUI} ${SOURCES_PLOTUI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_PLOTUI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_PLOTUI})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_PLOTUI})


# set(HEADERS
# 
#   COutputHandlerPlot.h
#   CopasiPlot.h
#   HistoWidget.h
#   PlotSubwidget.h
#   curve2dwidget.h
#   plotwindow.h
#   scrollbar.h
#   scrollzoomer.h
# 
# ${HEADERS})
# 
# if(COPASI_BANDED_GRAPH)
#   set(HEADERS BandedGraphWidget.h ${HEADERS})
# endif(COPASI_BANDED_GRAPH)
# 
# set(SOURCES
# 
#   COutputHandlerPlot.cpp
#   CopasiPlot.cpp
#   HistoWidget.cpp
#   PlotSubwidget.cpp
#   curve2dwidget.cpp
#   plotwindow.cpp
#   scrollbar.cpp
#   scrollzoomer.cpp
# 
# ${SOURCES})
# 
# if(COPASI_BANDED_GRAPH)
#   set(SOURCES BandedGraphWidget.cpp ${SOURCES})
# endif(COPASI_BANDED_GRAPH)
# 
# 
# set(FORMS
# 
# 
#   HistoWidget.ui
#   PlotSubwidget.ui
#   curve2dwidget.ui
# 
# ${FORMS})
# 
# if(COPASI_BANDED_GRAPH)
#   set(FORMS BandedGraphWidget.ui ${FORMS})
# endif(COPASI_BANDED_GRAPH)
# 
#if (ENABLE_SBW_INTEGRATION)
#  include_directories(${SBW_INCLUDE_DIR})
#  add_definitions(-DCOPASI_SBW_INTEGRATION)
#endif(ENABLE_SBW_INTEGRATION)
#  
#
#include(../CMakeUILib.cmake)
#
#qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
#
#if(FORMS)
#qt4_wrap_ui(HEADERS_FORMS ${FORMS})
#endif(FORMS)
#
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
#INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
#INCLUDE_DIRECTORIES(${QT_QTSVG_INCLUDE_DIR})
#
#add_library(plotUI STATIC ${SOURCES} ${HEADERS} ${HEADERS_FORMS} ${HEADERS_MOC})
#
#target_link_libraries(plotUI plot UI ${QWT_LIBRARIES} ${QT_LIBRARIES} ${QT_QTSVG_LIBRARY})
#