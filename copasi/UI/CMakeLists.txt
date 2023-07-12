# Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

###############################################################################
###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################

file(GLOB FORMS_UI   UI/*.ui )
file(GLOB HEADERS_UI UI/*.h  )
file(GLOB SOURCES_UI UI/*.cpp)

list(REMOVE_ITEM FORMS_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQFileDialogBtnGrp.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQMetabolite.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQPrintAsDialog.ui
#  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQProgressItemBar.ui
  #${CMAKE_CURRENT_SOURCE_DIR}/UI/CQProgressItemText.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQRegistrationDialog.ui
#  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQTextDialog.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/FunctionItemWidget.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/CQCrossSectionTaskWidget.ui
)

include_directories(${MML_INCLUDE_DIR})

set(SOURCES_RCC)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/CQIconResource.h)
  set (HEADERS_UI ${HEADERS_UI} ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/CQIconResource.h)
  set (SOURCES_UI ${SOURCES_UI} ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/CQIconResource.cpp)
  
  if (Qt5_FOUND)
    QT5_ADD_RESOURCES(COPASI_RCC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/copasi.qrc)
  elseif(Qt6_FOUND)
    QT6_ADD_RESOURCES(COPASI_RCC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/copasi.qrc)
  else()
    QT4_ADD_RESOURCES(COPASI_RCC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resourcesUI/copasi.qrc)
  endif()
endif()

if (NOT ${ENABLE_PROVENANCE})
  list(REMOVE_ITEM SOURCES_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CEntityProvenanceDialog.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CProvenanceDialog.cpp) 
  list(REMOVE_ITEM HEADERS_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CEntityProvenanceDialog.h
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CProvenanceDialog.h) 
endif()

if (NOT ENABLE_TIME_SENS)
  list(REMOVE_ITEM SOURCES_UI ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQTimeSensWidget.cpp)
  list(REMOVE_ITEM HEADERS_UI 
  ${CMAKE_CURRENT_SOURCE_DIR}/UI/CQTimeSensWidget.h)
endif()


# create source group for IDEs
source_group(UI FILES ${FORMS_UI} ${HEADERS_UI} ${SOURCES_UI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_UI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_UI})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_UI})
