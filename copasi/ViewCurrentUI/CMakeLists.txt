# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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

cmake_minimum_required (VERSION 2.8.12)
project (ViewCurrentUI)

if (NOT BUILD_GUI)
  message(FATAL_ERROR "ViewCurrentUI requires a UI build. Please toggle BUILD_GUI." )
endif()


SET(HEADERS ${HEADERS} worker.h arguments.h)
qt4_wrap_cpp(MOC_HEADERS ${HEADERS})

set(SOURCES ${SOURCES} ${MOC_HEADERS} main.cpp worker.cpp arguments.cpp)

set(COPASI_UI_FLAGS)
if(WIN32 AND NOT CYGWIN)
  if (NOT ENABLE_COPASI_UI_CONSOLE)
    set(COPASI_UI_FLAGS WIN32)
    if(MSVC OR USING_INTEL)
      set(SOURCES ${SOURCES} ViewCurrentUI.rc)
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup ")
    endif(MSVC OR USING_INTEL)
  endif(NOT ENABLE_COPASI_UI_CONSOLE)
endif(WIN32 AND NOT CYGWIN)

if (APPLE)
 
set(COPASI_UI_FLAGS MACOSX_BUNDLE)
set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/ViewCurrentUI.plist )
set(MACOSX_BUNDLE_ICON_FILE ${CMAKE_SOURCE_DIR}/copasi.icns )
set(MACOSX_BUNDLE_BUNDLE_VERSION  "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")
set(MACOSX_BUNDLE_INFO_STRING "COPASI ${MACOSX_BUNDLE_BUNDLE_VERSION} is distributed under the Artistic License 2.0." )
set(MACOSX_BUNDLE_GUI_IDENTIFIER  "org.copasi.ViewCurrentUI" )
set(MACOSX_BUNDLE_BUNDLE_NAME "ViewCurrentUI")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "${MACOSX_BUNDLE_BUNDLE_VERSION}")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING  "${MACOSX_BUNDLE_BUNDLE_VERSION}")
set(MACOSX_BUNDLE_COPYRIGHT ${MACOSX_BUNDLE_INFO_STRING})

endif(APPLE)

add_executable(ViewCurrentUI ${COPASI_UI_FLAGS} ${SOURCES} ${HEADERS})

target_link_libraries(ViewCurrentUI libCOPASIUI)
QT_BIND_TO_TARGET(ViewCurrentUI)

install(TARGETS ViewCurrentUI DESTINATION bin)
