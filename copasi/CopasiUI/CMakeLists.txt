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

cmake_minimum_required (VERSION 2.8.12...3.19.1)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

project (CopasiUI VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")


set(SOURCES ${SOURCES} main.cpp)

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

# need to bundle resource files for apple
set (RESOURCES)
if (APPLE)
  file(GLOB_RECURSE WIZARD_RESOURCES "${CMAKE_SOURCE_DIR}/copasi/wizard/help_html/*")
  file(GLOB_RECURSE EXAMPLES_RESOURCES "${CMAKE_SOURCE_DIR}/TestSuite/distribution/*")
  set (ICNS_FILE "${CMAKE_SOURCE_DIR}/copasi.icns")
  set (RESOURCES ${WIZARD_RESOURCES} ${EXAMPLES_RESOURCES} ${ICNS_FILE})
endif()

add_executable(CopasiUI ${COPASI_UI_FLAGS} ${SOURCES} ${HEADERS} ${RESOURCES})
target_link_libraries(CopasiUI libCOPASIUI)

# now modify the package location for the resource files
if (APPLE)

# Wizard files first
foreach (FILE ${WIZARD_RESOURCES})
    # Get the relative path from the data-folder to the particular file.
    file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/copasi/wizard/help_html" ${FILE})

    # Get the relative path to the file.
    get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)

    # Set it's location inside the app package (under Resources).
    set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/doc/html/${NEW_FILE_PATH}")

    # Optional: Add the file to the 'Resources' folder group in Xcode.
    #           This also preserves folder structure.
    source_group("Resources/doc/html/${NEW_FILE_PATH}" FILES "${FILE}")
endforeach ()

# then examples
foreach (FILE ${EXAMPLES_RESOURCES})
    # Get the relative path from the data-folder to the particular file.
    file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/TestSuite/distribution" ${FILE})

    # Get the relative path to the file.
    get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)

    # Set it's location inside the app package (under Resources).
    set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/examples/${NEW_FILE_PATH}")

    # Optional: Add the file to the 'Resources' folder group in Xcode.
    #           This also preserves folder structure.
    source_group("Resources/examples/${NEW_FILE_PATH}" FILES "${FILE}")
endforeach ()
# and icon
set_property(SOURCE ${ICNS_FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources")
source_group("Resources" FILES "${ICNS_FILE}")
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

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS ON)
include(InstallRequiredSystemLibraries)

