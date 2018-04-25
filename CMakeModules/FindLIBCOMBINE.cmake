# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

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


find_package(combine CONFIG REQUIRED
  CONFIGS Combine-config.cmake
          Combine-static-config.cmake
          libCombine-config.cmake
          libCombine-static-config.cmake
  PATHS $ENV{COMBINE_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
        $ENV{COMBINE_DIR}/lib/cmake
        ${COPASI_DEPENDENCY_DIR}/lib/cmake
        /usr/lib/cmake
  )

set(COMBINE_FOUND ${combine_FOUND})

get_target_property(COMBINE_INCLUDE_DIR ${COMBINE_LIBRARY_NAME} INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(COMBINE_LIBRARY ${COMBINE_LIBRARY_NAME} IMPORTED_LOCATION_RELEASE)

get_target_property(COMBINE_INTERFACE_LINK_LIBRARIES ${COMBINE_LIBRARY_NAME} INTERFACE_LINK_LIBRARIES)
if (COMBINE_INTERFACE_LINK_LIBRARIES)
  set(COMBINE_LIBRARY ${COMBINE_LIBRARY} ${COMBINE_INTERFACE_LINK_LIBRARIES})
endif (COMBINE_INTERFACE_LINK_LIBRARIES)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(COMBINE REQUIRED COMBINE_INCLUDE_DIR COMBINE_LIBRARY)

mark_as_advanced(COMBINE_INCLUDE_DIR COMBINE_LIBRARY)
