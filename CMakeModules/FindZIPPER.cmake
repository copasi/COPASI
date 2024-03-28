# Copyright (C) 2022 - 2023 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Locate library providing crossguid
# This module defines:
# ZIPPER_INCLUDE_DIR, where to find the headers
#
# ZIPPER, ZIPPER_DEBUG
# ZIPPER_FOUND
#
# $ZIPPER_DIR is an environment variable that would
# correspond to the ./configure --prefix=$ZIPPER_DIR

MACRO (FIND_ZIPPER)

ENDMACRO ()


string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

find_library(ZIPPER_LIBRARY
    NAMES Zipper-static Zipper libZipper-static libZipper
    PATHS ${CMAKE_OSX_SYSROOT}/usr/lib
          ${${_PROJECT_DEPENDENCY_DIR}}/lib
          ${ADDITIONAL_LIB_DIRS}
          $ENV{ZIPPER_DIR}/lib
          /usr/lib
          /usr/local/lib
          CMAKE_FIND_ROOT_PATH_BOTH
    DOC "The file name of the ZIPPER library."
)

find_path(ZIPPER_INCLUDE_DIR
      NAMES zipper/zipper.h
      PATHS ${${_PROJECT_DEPENDENCY_DIR}}/include
            $ENV{ZIPPER_DIR}/include
            ${CMAKE_OSX_SYSROOT}/usr/include
            /usr/include
            /usr/local/include
            CMAKE_FIND_ROOT_PATH_BOTH
            NO_DEFAULT_PATH
      DOC "The directory containing the ZIPPER include files."
            )

if(NOT TARGET ZLIB::ZLIB)
  find_package(ZLIB)
endif()

if(NOT TARGET ZIPPER::ZIPPER)
  add_library(ZIPPER::ZIPPER UNKNOWN IMPORTED)
  set_target_properties(ZIPPER::ZIPPER PROPERTIES
    IMPORTED_LOCATION "${ZIPPER_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${ZIPPER_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "ZLIB::ZLIB")
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    ZIPPER
    REQUIRED_VARS ZIPPER_LIBRARY ZIPPER_INCLUDE_DIR)

mark_as_advanced(ZIPPER_LIBRARY ZIPPER_INCLUDE_DIR)

