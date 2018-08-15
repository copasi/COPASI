# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

#
# Locate libCOMBINE
# This module defines:
# COMBINE_INCLUDE_DIR, where to find the headers
#
# COMBINE_LIBRARY, COMBINE_LIBRARY_DEBUG
# COMBINE_FOUND
#
# $COMBINE_DIR is an environment variable that would
# correspond to the ./configure --prefix=$COMBINE_DIR
#
# Created by Robert Osfield.
# Modified by Ralph Gauges

# message (STATUS "$ENV{COMBINE_DIR}")


set(COMBINE_LIBRARY_NAME)
if (UNIX)
  set(COMBINE_LIBRARY_NAME Combine-static)
else()
  set(COMBINE_LIBRARY_NAME libCombine-static)
endif()


find_package(${COMBINE_LIBRARY_NAME} CONFIG QUIET)

if (NOT ${COMBINE_LIBRARY_NAME}_FOUND)
  find_package(${COMBINE_LIBRARY_NAME} CONFIG QUIET
  CONFIGS ${COMBINE_LIBRARY_NAME}-config.cmake
  PATHS $ENV{COMBINE_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
        $ENV{COMBINE_DIR}/lib/cmake
        ${COPASI_DEPENDENCY_DIR}/lib/cmake
        /usr/lib/cmake
  )
endif()

if (${COMBINE_LIBRARY_NAME}_FOUND)

get_target_property(COMBINE_INCLUDE_DIR ${COMBINE_LIBRARY_NAME} INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(COMBINE_LIBRARY ${COMBINE_LIBRARY_NAME} IMPORTED_LOCATION_RELEASE)

if (NOT COMBINE_LIBRARY)
  get_target_property(COMBINE_LIBRARY ${COMBINE_LIBRARY_NAME} IMPORTED_LOCATION_DEBUG)
endif()

if (NOT COMBINE_LIBRARY)
  set(COMBINE_LIBRARY)
endif()

get_target_property(COMBINE_INTERFACE_LINK_LIBRARIES ${COMBINE_LIBRARY_NAME} INTERFACE_LINK_LIBRARIES)

if (COMBINE_INTERFACE_LINK_LIBRARIES)
  set(COMBINE_LIBRARY ${COMBINE_LIBRARY} ${COMBINE_INTERFACE_LINK_LIBRARIES})
endif (COMBINE_INTERFACE_LINK_LIBRARIES)

else()
  # Fallback if no CONFIG is found

  find_path(COMBINE_INCLUDE_DIR combine/combinearchive.h
    PATHS $ENV{COMBINE_DIR}/include
          $ENV{COMBINE_DIR}
          ${COPASI_DEPENDENCY_DIR}/include
          ${COPASI_DEPENDENCY_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    NO_DEFAULT_PATH)

  if (NOT COMBINE_INCLUDE_DIR)
    message(FATAL_ERROR "COMBINE include dir not found not found!")
  endif (NOT COMBINE_INCLUDE_DIR)

  if (NOT COMBINE_INCLUDE_DIR)
    find_path(COMBINE_INCLUDE_DIR combine/combinearchive.h)
  endif (NOT COMBINE_INCLUDE_DIR)

  find_library(COMBINE_LIBRARY 
    NAMES ${COMBINE_LIBRARY_NAME}
    PATHS $ENV{COMBINE_DIR}/lib
          $ENV{COMBINE_DIR}
          ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}
          ${COPASI_DEPENDENCY_DIR}/lib
          ${COPASI_DEPENDENCY_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib         Fink
          /opt/local/lib  MacPorts
          /opt/csw/lib    Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)
    
  if (NOT COMBINE_LIBRARY)
    find_library(COMBINE_LIBRARY 
        NAMES ${COMBINE_LIBRARY_NAME})
  endif (NOT COMBINE_LIBRARY)
endif()

if (NOT COMBINE_LIBRARY)
    message(FATAL_ERROR "COMBINE library not found!")
endif (NOT COMBINE_LIBRARY)

set(COMBINE_FOUND "NO")
if(COMBINE_LIBRARY)
    if   (COMBINE_INCLUDE_DIR)
        SET(COMBINE_FOUND "YES")
    endif(COMBINE_INCLUDE_DIR)
endif(COMBINE_LIBRARY)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(COMBINE REQUIRED COMBINE_INCLUDE_DIR COMBINE_LIBRARY)

mark_as_advanced(COMBINE_INCLUDE_DIR COMBINE_LIBRARY)
