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
# project (layoutUI)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB FORMS_LAYOUTUI   layoutUI/*.ui )
file(GLOB HEADERS_LAYOUTUI layoutUI/*.h  )
file(GLOB SOURCES_LAYOUTUI layoutUI/*.cpp)

# remove files not used when specific options are disabled
if (NOT ENABLE_CRENDER_EXTENSION)

  list(REMOVE_ITEM HEADERS_LAYOUTUI 
  
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQFontRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQGLLayoutPainter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQGLLayoutViewer.h
  	${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQNewMainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQQtImageTexturizer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQScreenshotOptionsDialog.h
    
  )
  
  
  list(REMOVE_ITEM SOURCES_LAYOUTUI
  
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQFontRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQGLLayoutPainter.cpp
  	${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQGLLayoutViewer.cpp
  	${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQNewMainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQQtImageTexturizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQScreenshotOptionsDialog.cpp
  
  )
  
  list(REMOVE_ITEM FORMS_LAYOUTUI 
  
    ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQScreenshotDialog.ui
	
  )
    
endif(NOT ENABLE_CRENDER_EXTENSION)


if (NOT ENABLE_COPASI_AUTOLAYOUT)

  list(REMOVE_ITEM HEADERS_LAYOUTUI ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQAutolayoutWizard.h)
  list(REMOVE_ITEM SOURCES_LAYOUTUI ${CMAKE_CURRENT_SOURCE_DIR}/layoutUI/CQAutolayoutWizard.cpp)

endif(NOT ENABLE_COPASI_AUTOLAYOUT)

# create source group for IDEs
source_group(layoutUI FILES ${FORMS_LAYOUTUI} ${HEADERS_LAYOUTUI} ${SOURCES_LAYOUTUI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_LAYOUTUI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_LAYOUTUI})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_LAYOUTUI})

# additional files that do not seem to be used 


# set(FORMS ParaPanel.ui ${FORMS})
# set(FORMS NodeSizePanel.ui ${FORMS})
# set(FORMS FontChooser.ui ${FORMS})
# 
# 
# set(HEADERS CQGLNetworkPainter.h ${HEADERS})
# set(HEADERS CArrow.h ${HEADERS})
# set(HEADERS CCompartmentGraphNode.h ${HEADERS})
# set(HEADERS CGraphNode.h ${HEADERS})
# set(HEADERS CGraphCurve.h ${HEADERS})
# set(HEADERS CQGLViewport.h ${HEADERS})
# set(HEADERS CQLayoutMainWindow.h ${HEADERS})
# set(HEADERS CQPlayerControlWidget.h ${HEADERS})
# set(HEADERS CSimSummaryInfo.h ${HEADERS})
# set(HEADERS CDataEntity.h ${HEADERS})
# set(HEADERS CVisParameters.h ${HEADERS})
# set(HEADERS CQCurrentValueTable.h ${HEADERS})
# set(HEADERS BezierCurve.h ${HEADERS})
# set(HEADERS FontChooser.h ${HEADERS})
# set(HEADERS ParaPanel.h ${HEADERS})
# set(HEADERS NodeSizePanel.h ${HEADERS})
# set(HEADERS RGTextureSpec.h ${HEADERS})
# set(HEADERS CLabel.h ${HEADERS})
# 
# set(SOURCES CQLayoutMainWindow.cpp ${SOURCES})
# set(SOURCES CArrow.cpp ${SOURCES})
# set(SOURCES CCompartmentGraphNode.cpp ${SOURCES})
# set(SOURCES CGraphNode.cpp ${SOURCES})
# set(SOURCES CGraphCurve.cpp ${SOURCES})
# set(SOURCES CQGLNetworkPainter.cpp ${SOURCES})
# set(SOURCES CQPlayerControlWidget.cpp ${SOURCES})
# set(SOURCES CSimSummaryInfo.cpp ${SOURCES})
# set(SOURCES CDataEntity.cpp ${SOURCES})
# set(SOURCES CVisParameters.cpp ${SOURCES})
# set(SOURCES CQCurrentValueTable.cpp ${SOURCES})
# set(SOURCES CQGLViewport.cpp ${SOURCES})
# set(SOURCES BezierCurve.cpp ${SOURCES})
# set(SOURCES FontChooser.cpp ${SOURCES})
# set(SOURCES ParaPanel.cpp ${SOURCES})
# set(SOURCES NodeSizePanel.cpp ${SOURCES})
# set(SOURCES RGTextureSpec.cpp ${SOURCES})
# set(SOURCES CLabel.cpp ${SOURCES})
# 
# if (ENABLE_CRENDER_EXTENSION)
# 
# set(HEADERS ${HEADERS}
# 
#   CQFontRenderer.h
#   CQGLLayoutPainter.h
#   CQGLLayoutViewer.h
# 	CQNewMainWindow.h
#   CQQtImageTexturizer.h
#   CQScreenshotOptionsDialog.h
#   
# )
# 
# 
# set(SOURCES ${SOURCES}
# 
#   CQFontRenderer.cpp
#   CQGLLayoutPainter.cpp
# 	CQGLLayoutViewer.cpp
# 	CQNewMainWindow.cpp
#   CQQtImageTexturizer.cpp
#   CQScreenshotOptionsDialog.cpp
# 
# )
# 
# set(FORMS CQScreenshotDialog.ui ${FORMS})
# 
# endif(ENABLE_CRENDER_EXTENSION)
# 
# 
# if (ENABLE_COPASI_AUTOLAYOUT)
# 
#   set(HEADERS CQAutolayoutWizard.h ${HEADERS})
#   set(SOURCES CQAutolayoutWizard.cpp ${SOURCES})
# 
# endif(ENABLE_COPASI_AUTOLAYOUT)
# 
# include(../CMakeUILib.cmake)
# 
# 
# if (ENABLE_FRAMEBUFFER_SCREENSHOTS)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DFRAMEBUFFER_SCREENSHOTS=1)
# endif(ENABLE_FRAMEBUFFER_SCREENSHOTS)
# 
# if (ENABLE_COPASI_AUTOLAYOUT)
# set(COPASI_UI_MOC_OPTIONS ${COPASI_UI_MOC_OPTIONS} -DCOPASI_AUTOLAYOUT=1)
# endif(ENABLE_COPASI_AUTOLAYOUT)
# 
# if (COPASI_UI_MOC_OPTIONS)
# message(STATUS "Moc'ing layoutUI with options: ${COPASI_UI_MOC_OPTIONS}")
# qt4_wrap_cpp(HEADERS_MOC ${HEADERS} OPTIONS ${COPASI_UI_MOC_OPTIONS})
# else()
# qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
# endif(COPASI_UI_MOC_OPTIONS)
# 
# if(FORMS)
# qt4_wrap_ui(HEADERS_FORMS ${FORMS})
# endif(FORMS)
# 
# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
# INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
# 
# add_library(layoutUI STATIC ${SOURCES} ${HEADERS} ${HEADERS_MOC} ${HEADERS_FORMS})
# 
# target_link_libraries(layoutUI layout ${OPENGL_glu_LIBRARY} ${QT_QTOPENGL_LIBRARY} )

