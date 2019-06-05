# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
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

cmake_minimum_required (VERSION 3.0)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project (CopasiUI VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")

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
set(MACOSX_BUNDLE_ICON_FILE copasi.icns )
set(MACOSX_BUNDLE_BUNDLE_VERSION  "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")
set(MACOSX_BUNDLE_INFO_STRING "COPASI ${MACOSX_BUNDLE_BUNDLE_VERSION} is distributed under the Artistic License 2.0." )
set(MACOSX_BUNDLE_GUI_IDENTIFIER  "org.copasi.CopasiUI" )
set(MACOSX_BUNDLE_BUNDLE_NAME "CopasiUI")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "${MACOSX_BUNDLE_BUNDLE_VERSION}")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING  "${MACOSX_BUNDLE_BUNDLE_VERSION}")
set(MACOSX_BUNDLE_COPYRIGHT ${MACOSX_BUNDLE_INFO_STRING})

endif(APPLE)

if (BUILD_STATIC_COPASISE) 
    # set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++") 
    # Maybe this works as well, haven't tried yet. 
    set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE) 
endif (BUILD_STATIC_COPASISE) 

add_executable(CopasiUI ${COPASI_UI_FLAGS} ${SOURCES} ${HEADERS})
target_link_libraries(CopasiUI ${SE_LIBS} ${UI_LIBS} ${SE_EXTERNAL_LIBS} ${UI_EXTERNAL_LIBS}
                      ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
QT_BIND_TO_TARGET(CopasiUI)

if (NOT USING_INTEL)
  target_link_libraries(CopasiUI ${ZLIB_LIBRARY})
endif (NOT USING_INTEL)

if (ENABLE_SBW_INTEGRATION)
target_link_libraries(CopasiUI ${SBW_LIBRARIES})
endif(ENABLE_SBW_INTEGRATION)

# On some linux systems we do require a link against the pthread library
# as well as the libz library
if (UNIX AND NOT APPLE)
  find_package(Threads)
  find_package(ZLIB)
  if (CMAKE_USE_PTHREADS_INIT)
    target_link_libraries(CopasiUI ${CMAKE_THREAD_LIBS_INIT})
  endif()
  if (ZLIB_FOUND)
    target_link_libraries(CopasiUI ${ZLIB_LIBRARIES})
  endif()
endif()

if(NOT APPLE)
    SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/CopasiUI${CMAKE_EXECUTABLE_SUFFIX}" CACHE INTERNAL "")
    install(TARGETS CopasiUI DESTINATION bin)
# ensure that next to the binaries also dependencies are copied
    if (WIN32)
        install(CODE "
            include(BundleUtilities)
            fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
            " COMPONENT Runtime)
    endif (WIN32)
else()
# on OS X everything is different, here we need to first fix the app bundle,
# and only then install it
SET(APPS)
if (CMAKE_GENERATOR STREQUAL Xcode)
SET(APPS "${CMAKE_CURRENT_BINARY_DIR}/Release/CopasiUI.app" CACHE INTERNAL "")
else()
SET(APPS "${CMAKE_CURRENT_BINARY_DIR}/CopasiUI.app" CACHE INTERNAL "")
endif()
# ensure that next to the binaries also dependencies are copied
install(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
    " COMPONENT Runtime)
install(TARGETS CopasiUI DESTINATION .)
endif()

include(InstallRequiredSystemLibraries)

