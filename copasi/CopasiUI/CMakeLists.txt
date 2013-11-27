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

cmake_minimum_required (VERSION 2.6)
project (CopasiUI)

include_directories(BEFORE "${PROJECT_SOURCE_DIR}/.." "${PROJECT_SOURCE_DIR}/../.." "${PROJECT_SOURCE_DIR}")

set(SOURCES ${SOURCES} main.cpp)

include(../common.cmake)
include(../CMakeConsoleApp.cmake)
include(../CMakeUIApp.cmake)

if (ENABLE_SBW_INTEGRATION)
include_directories(${SBW_INCLUDE_DIR})
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../UI)

set(COPASI_UI_FLAGS)
if(WIN32 AND NOT CYGWIN)
  option(ENABLE_COPASI_UI_CONSOLE "Show the console window (to see debug messages) when running CopasiUI" OFF)
  if (NOT ENABLE_COPASI_UI_CONSOLE)
    set(COPASI_UI_FLAGS WIN32)
    if(MSVC OR USING_INTEL)
      set(SOURCES ${SOURCES} CopasiUI.rc)
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup ")
    endif(MSVC OR USING_INTEL)
  endif(NOT ENABLE_COPASI_UI_CONSOLE)
endif(WIN32 AND NOT CYGWIN)

if (APPLE)

set(COPASI_UI_FLAGS MACOSX_BUNDLE)
set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/CopasiUI.plist )
set(MACOSX_BUNDLE_ICON_FILE ${CMAKE_SOURCE_DIR}/copasi.icns )
set(MACOSX_BUNDLE_BUNDLE_VERSION  "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")
set(MACOSX_BUNDLE_INFO_STRING "COPASI ${MACOSX_BUNDLE_BUNDLE_VERSION} is distributed under the Artistic License 2.0." )
set(MACOSX_BUNDLE_GUI_IDENTIFIER  "org.copasi.CopasiUI" )
set(MACOSX_BUNDLE_BUNDLE_NAME "CopasiUI")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "${MACOSX_BUNDLE_BUNDLE_VERSION}")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING  "${MACOSX_BUNDLE_BUNDLE_VERSION}")
set(MACOSX_BUNDLE_COPYRIGHT ${MACOSX_BUNDLE_INFO_STRING})

endif(APPLE)

add_executable(CopasiUI ${COPASI_UI_FLAGS} ${SOURCES} ${HEADERS})

if (USING_INTEL)
    target_link_libraries(CopasiUI
	${SE_EXTERNAL_LIBS} ${SE_LIBS} ${UI_LIBS}
	${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARY}
	${OPENGL_gl_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${OPENGL_glu_LIBRARY}
	${QWTPLOT3D_LIBRARY}
	${QT_QTSVG_LIBRARY} ${QWT_LIBRARY} )
else (USING_INTEL)
    target_link_libraries(CopasiUI
	${SE_EXTERNAL_LIBS} ${SE_LIBS} ${UI_LIBS}
	${QT_LIBRARIES} ${QT_QTWEBKIT_LIBRARY}
	${OPENGL_gl_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${OPENGL_glu_LIBRARY}
	${QWTPLOT3D_LIBRARY}
	${QT_QTSVG_LIBRARY} ${ZLIB_LIBRARY} ${QWT_LIBRARY} )
endif (USING_INTEL)

if (ENABLE_SBW_INTEGRATION)
target_link_libraries(CopasiUI ${SBW_LIBRARIES})
endif(ENABLE_SBW_INTEGRATION)

if(NOT APPLE)
SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/CopasiUI${CMAKE_EXECUTABLE_SUFFIX}" CACHE INTERNAL "")
install(TARGETS CopasiUI DESTINATION bin)
# ensure that next to the binaries also dependencies are copied
install(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
    " COMPONENT Runtime)

else()
# on OS X everything is different, here we need to first fix the app bundle,
# and only then install it
SET(APPS "${CMAKE_CURRENT_BINARY_DIR}/CopasiUI.app" CACHE INTERNAL "")
# ensure that next to the binaries also dependencies are copied
install(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
    " COMPONENT Runtime)
install(TARGETS CopasiUI DESTINATION COPASI)
endif()

include(InstallRequiredSystemLibraries)

