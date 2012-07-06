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


if(NOT ENABLE_COPASI_AUTOLAYOUT)
  list(REMOVE_ITEM HEADERS_LAYOUT
     ${CMAKE_CURRENT_SOURCE_DIR}/layout/CAbstractLayoutInterface.h
     ${CMAKE_CURRENT_SOURCE_DIR}/layout/CCopasiSpringLayout.h
     ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLayoutEngine.h
  )
  list(REMOVE_ITEM SOURCES_LAYOUT
     ${CMAKE_CURRENT_SOURCE_DIR}/layout/CAbstractLayoutInterface.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/layout/CCopasiSpringLayout.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLayoutEngine.cpp
  )
endif (NOT ENABLE_COPASI_AUTOLAYOUT)

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
  
endif (NOT ENABLE_CRENDER_EXTENSION)

# remove other elements that 
list(REMOVE_ITEM SOURCES_LAYOUT 
  ${CMAKE_CURRENT_SOURCE_DIR}/layout/CLSimpleImageTexturizer.cpp
)

# create source group for IDEs
source_group(layout FILES ${SOURCES_LAYOUT} ${HEADERS_LAYOUT})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_LAYOUT})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_LAYOUT})



# set(HEADERS ${HEADERS} CLayout.h)
# set(HEADERS ${HEADERS} CLayoutInitializer.h)
# set(HEADERS ${HEADERS} CLBase.h)
# set(HEADERS ${HEADERS} CLCurve.h)
# set(HEADERS ${HEADERS} CLGraphicalObject.h)
# set(HEADERS ${HEADERS} CLGlyphs.h)
# set(HEADERS ${HEADERS} CListOfLayouts.h)
# set(HEADERS ${HEADERS} CLReactionGlyph.h)
# set(HEADERS ${HEADERS} SBMLDocumentLoader.h)
# 
# if(ENABLE_COPASI_AUTOLAYOUT)
# set(HEADERS ${HEADERS} CAbstractLayoutInterface.h)
# set(HEADERS ${HEADERS} CCopasiSpringLayout.h)
# set(HEADERS ${HEADERS} CLayoutEngine.h)
# endif (ENABLE_COPASI_AUTOLAYOUT)
# 
# if(ENABLE_CRENDER_EXTENSION)
# set(HEADERS ${HEADERS} CLColorDefinition.h)
# set(HEADERS ${HEADERS} CLDefaultStyles.h)
# set(HEADERS ${HEADERS} CLEllipse.h)
# set(HEADERS ${HEADERS} CLGlobalRenderInformation.h)
# set(HEADERS ${HEADERS} CLGlobalStyle.h)
# set(HEADERS ${HEADERS} CLGradientBase.h)
# set(HEADERS ${HEADERS} CLGradientStop.h)
# set(HEADERS ${HEADERS} CLGradientStops.h)
# set(HEADERS ${HEADERS} CLGraphicalPrimitive1D.h)
# set(HEADERS ${HEADERS} CLGraphicalPrimitive2D.h)
# set(HEADERS ${HEADERS} CLGroup.h)
# set(HEADERS ${HEADERS} CLImage.h)
# set(HEADERS ${HEADERS} CLImageTexturizer.h)
# set(HEADERS ${HEADERS} CLLineEnding.h)
# set(HEADERS ${HEADERS} CLLinearGradient.h)
# set(HEADERS ${HEADERS} CLLocalRenderInformation.h)
# set(HEADERS ${HEADERS} CLLocalStyle.h)
# set(HEADERS ${HEADERS} CLPolygon.h)
# set(HEADERS ${HEADERS} CLRadialGradient.h)
# set(HEADERS ${HEADERS} CLRectangle.h)
# set(HEADERS ${HEADERS} CLRelAbsVector.h)
# set(HEADERS ${HEADERS} CLRenderCubicBezier.h)
# set(HEADERS ${HEADERS} CLRenderCurve.h)
# set(HEADERS ${HEADERS} CLRenderFlattener.h)
# set(HEADERS ${HEADERS} CLRenderInformationBase.h)
# set(HEADERS ${HEADERS} CLRenderPoint.h)
# set(HEADERS ${HEADERS} CLRenderResolver.h)
# set(HEADERS ${HEADERS} CLRGBAColor.h)
# set(HEADERS ${HEADERS} CLStyle.h)
# set(HEADERS ${HEADERS} CLText.h)
# set(HEADERS ${HEADERS} CLTransformation.h)
# set(HEADERS ${HEADERS} CLTransformation2D.h)
# set(HEADERS ${HEADERS} CLUnresolvedReferenceException.h)
# 
# endif (ENABLE_CRENDER_EXTENSION)
# 
# set(SOURCES ${SOURCES} CLayout.cpp)
# set(SOURCES ${SOURCES} CLayoutInitializer.cpp)
# set(SOURCES ${SOURCES} CLBase.cpp)
# set(SOURCES ${SOURCES} CLCurve.cpp)
# set(SOURCES ${SOURCES} CLGraphicalObject.cpp)
# set(SOURCES ${SOURCES} CLGlyphs.cpp)
# set(SOURCES ${SOURCES} CListOfLayouts.cpp)
# set(SOURCES ${SOURCES} CLReactionGlyph.cpp)
# set(SOURCES ${SOURCES} SBMLDocumentLoader.cpp)
# 
# if (ENABLE_COPASI_AUTOLAYOUT)
# set(SOURCES ${SOURCES} CAbstractLayoutInterface.cpp)
# set(SOURCES ${SOURCES} CCopasiSpringLayout.cpp)
# set(SOURCES ${SOURCES} CLayoutEngine.cpp)
# endif (ENABLE_COPASI_AUTOLAYOUT)
# 
# if (ENABLE_CRENDER_EXTENSION)
# set(SOURCES ${SOURCES} CLColorDefinition.cpp)
# set(SOURCES ${SOURCES} CLDefaultStyles.cpp)
# set(SOURCES ${SOURCES} CLEllipse.cpp)
# set(SOURCES ${SOURCES} CLGlobalRenderInformation.cpp)
# set(SOURCES ${SOURCES} CLGlobalStyle.cpp)
# set(SOURCES ${SOURCES} CLGradientBase.cpp)
# set(SOURCES ${SOURCES} CLGradientStop.cpp)
# set(SOURCES ${SOURCES} CLGradientStops.cpp)
# set(SOURCES ${SOURCES} CLGraphicalPrimitive1D.cpp)
# set(SOURCES ${SOURCES} CLGraphicalPrimitive2D.cpp)
# set(SOURCES ${SOURCES} CLGroup.cpp)
# set(SOURCES ${SOURCES} CLImage.cpp)
# set(SOURCES ${SOURCES} CLImageTexturizer.cpp)
# set(SOURCES ${SOURCES} CLLineEnding.cpp)
# set(SOURCES ${SOURCES} CLLinearGradient.cpp)
# set(SOURCES ${SOURCES} CLLocalRenderInformation.cpp)
# set(SOURCES ${SOURCES} CLLocalStyle.cpp)
# set(SOURCES ${SOURCES} CLPolygon.cpp)
# set(SOURCES ${SOURCES} CLRadialGradient.cpp)
# set(SOURCES ${SOURCES} CLRectangle.cpp)
# set(SOURCES ${SOURCES} CLRelAbsVector.cpp)
# set(SOURCES ${SOURCES} CLRenderCubicBezier.cpp)
# set(SOURCES ${SOURCES} CLRenderCurve.cpp)
# set(SOURCES ${SOURCES} CLRenderFlattener.cpp)
# set(SOURCES ${SOURCES} CLRenderInformationBase.cpp)
# set(SOURCES ${SOURCES} CLRenderPoint.cpp)
# set(SOURCES ${SOURCES} CLRenderResolver.cpp)
# set(SOURCES ${SOURCES} CLStyle.cpp)
# set(SOURCES ${SOURCES} CLText.cpp)
# set(SOURCES ${SOURCES} CLTransformation.cpp)
# set(SOURCES ${SOURCES} CLTransformation2D.cpp)
# set(SOURCES ${SOURCES} CLUnresolvedReferenceException.cpp)
# 
# if(OPENGL_FOUND)
# 
# set(HEADERS ${HEADERS} CLFontRendererBase.h)
# set(HEADERS ${HEADERS} CLLayoutRenderer.h)
# set(SOURCES ${SOURCES} CLLayoutRenderer.cpp)
# set(HEADERS ${HEADERS} utility_classes.h)
# set(SOURCES ${SOURCES} utility_classes.cpp)
#
# endif(OPENGL_FOUND)
# 
# endif (ENABLE_CRENDER_EXTENSION)
# 

#add_library(layout STATIC ${SOURCES} ${HEADERS})


