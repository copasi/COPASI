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
#project (layout)
#
#include_directories(
#  "${PROJECT_SOURCE_DIR}/.." 
#  "${PROJECT_SOURCE_DIR}/../.." 
#  "${PROJECT_SOURCE_DIR}"
#)
# 
file(GLOB HEADERS_LAYOUT layout/*.h)
file(GLOB SOURCES_LAYOUT layout/*.cpp)


if (NOT ENABLE_CRENDER_EXTENSION)

  list(REMOVE_ITEM SOURCES_LAYOUT
  
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLColorDefinition.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLDefaultStyles.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLEllipse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGlobalRenderInformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGlobalStyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGradientBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGradientStop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGradientStops.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGraphicalPrimitive1D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGraphicalPrimitive2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLGroup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLImage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLImageTexturizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLineEnding.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLinearGradient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLocalRenderInformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLocalStyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLPolygon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRadialGradient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRelAbsVector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRenderCubicBezier.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRenderCurve.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRenderFlattener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRenderInformationBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRenderPoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLRenderResolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLStyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLText.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLTransformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLTransformation2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLUnresolvedReferenceException.cpp
  )

  
endif (NOT ENABLE_CRENDER_EXTENSION)

  
if(NOT OPENGL_FOUND)

  list(REMOVE_ITEM SOURCES_LAYOUT
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLayoutRenderer.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/layout/utility_classes.cpp
  )
	
  list(REMOVE_ITEM HEADERS_LAYOUT
    ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLFontRendererBase.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLLayoutRenderer.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/layout/utility_classes.h
  )  
endif(NOT OPENGL_FOUND)

# remove other elements that 
list(REMOVE_ITEM SOURCES_LAYOUT 
  ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLSimpleImageTexturizer.cpp
)

# create source group for IDEs
source_group(layout FILES ${SOURCES_LAYOUT} ${HEADERS_LAYOUT})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_LAYOUT})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_LAYOUT})



