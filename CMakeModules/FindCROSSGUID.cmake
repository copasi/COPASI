# Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 


# Locate library providing crossguid
# This module defines:
# CROSSGUID_INCLUDE_DIR, where to find the headers
#
# CROSSGUID, CROSSGUID_DEBUG
# CROSSGUID_FOUND
#
# $CROSSGUID_DIR is an environment variable that would
# correspond to the ./configure --prefix=$CROSSGUID_DIR

find_package(crossguid CONFIG REQUIRED
  CONFIGS crossguid-config.cmake
  PATHS $ENV{CROSSGUID_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
  )

set(CROSSGUID_FOUND ${crossguid_FOUND})

get_target_property(CROSSGUID_INCLUDE_DIR crossguid INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(CROSSGUID_LIBRARY crossguid IMPORTED_LOCATION_RELEASE)
if (NOT CROSSGUID_LIBRARY)
get_target_property(CROSSGUID_LIBRARY crossguid IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG)
endif()

get_target_property(CROSSGUID_INTERFACE_LINK_LIBRARIES crossguid INTERFACE_LINK_LIBRARIES)

if (CROSSGUID_INTERFACE_LINK_LIBRARIES)
  set(CROSSGUID_LIBRARY ${CROSSGUID_LIBRARY} ${CROSSGUID_INTERFACE_LINK_LIBRARIES})
endif (CROSSGUID_INTERFACE_LINK_LIBRARIES)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CROSSGUID REQUIRED CROSSGUID_INCLUDE_DIR CROSSGUID_LIBRARY)

mark_as_advanced(CROSSGUID_INCLUDE_DIR CROSSGUID_LIBRARY)

