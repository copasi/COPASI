# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# - Try to find the Expat XML parsing library 

# Once done this will define
#
#  EXPAT_FOUND       - system has Expat
#  EXPAT_LIBRARY   - Link these to use Expat
#  EXPAT_INCLUDE_DIR - Include directory for using Expat
#  EXPAT_DEFINITIONS - Compiler switches required for using Expat
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

include(CheckCSourceCompiles)

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

find_path(EXPAT_INCLUDE_DIR expat.h
    PATHS $ENV{EXPAT_DIR}/include
            $ENV{EXPAT_DIR}
            ${${_PROJECT_DEPENDENCY_DIR}}/include
            CMAKE_FIND_ROOT_PATH_BOTH
            NO_DEFAULT_PATH)

if (NOT EXPAT_INCLUDE_DIR)
find_path(EXPAT_INCLUDE_DIR expat.h
    PATHS $ENV{EXPAT_DIR}/include
          $ENV{EXPAT_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/include
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
          CMAKE_FIND_ROOT_PATH_BOTH
          NO_DEFAULT_PATH)
endif ()

if (NOT EXPAT_INCLUDE_DIR)
    find_path(EXPAT_INCLUDE_DIR expat.h)
endif ()

find_library(EXPAT_LIBRARY 
    NAMES libexpat expat
    PATHS $ENV{EXPAT_DIR}/${CMAKE_INSTALL_LIBDIR}
          $ENV{EXPAT_DIR}/lib-dbg
          $ENV{EXPAT_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/lib64
          ${${_PROJECT_DEPENDENCY_DIR}}/lib
          ${${_PROJECT_DEPENDENCY_DIR}}
          CMAKE_FIND_ROOT_PATH_BOTH
          NO_DEFAULT_PATH)

if (NOT EXPAT_LIBRARY)
find_library(EXPAT_LIBRARY 
    NAMES libexpat expat
    PATHS $ENV{EXPAT_DIR}/${CMAKE_INSTALL_LIBDIR}
          $ENV{EXPAT_DIR}/lib-dbg
          $ENV{EXPAT_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
          ${${_PROJECT_DEPENDENCY_DIR}}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
          CMAKE_FIND_ROOT_PATH_BOTH
          NO_DEFAULT_PATH)
endif()

if (NOT EXPAT_LIBRARY)
    find_library(EXPAT_LIBRARY NAMES libexpat expat)
endif ()

mark_as_advanced(EXPAT_INCLUDE_DIR EXPAT_LIBRARY)


if (EXPAT_INCLUDE_DIR AND EXISTS "${EXPAT_INCLUDE_DIR}/expat.h")
file(STRINGS "${EXPAT_INCLUDE_DIR}/expat.h" expat_version_str
     REGEX "^#[\t ]*define[\t ]+XML_(MAJOR|MINOR|MICRO)_VERSION[\t ]+[0-9]+$")

unset(EXPAT_VERSION CACHE)
set(_STARTED FALSE)
foreach(VPART MAJOR MINOR MICRO)
    foreach(VLINE ${expat_version_str})
        if(VLINE MATCHES "^#[\t ]*define[\t ]+XML_${VPART}_VERSION[\t ]+([0-9]+)$")
            set(EXPAT_VERSION_PART "${CMAKE_MATCH_1}")
            if(_STARTED)
                string(APPEND EXPAT_VERSION ".${EXPAT_VERSION_PART}")
            else()
                set(EXPAT_VERSION "${EXPAT_VERSION_PART}")
                set(_STARTED TRUE)
            endif()
        endif()
    endforeach()
endforeach()
unset(_STARTED)
endif ()


# create an expat target to link against
if(NOT TARGET EXPAT::EXPAT)
  add_library(EXPAT::EXPAT UNKNOWN IMPORTED)
  set_target_properties(EXPAT::EXPAT PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${EXPAT_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${EXPAT_INCLUDE_DIR}")
endif()

# figure out if we need XML_STATIC flag
if (EXPAT_INCLUDE_DIR AND EXPAT_LIBRARY)
  enable_language(C)  
  set(EXPAT_EXPAT_CODE
"
#include <expat.h>
#include <stdio.h>

int 
main(void)
{
    printf(\"%s\", XML_ExpatVersion());
    return 0;
}
" 
)

set(CMAKE_REQUIRED_LIBRARIES_CACHE ${CMAKE_REQUIRED_LIBRARIES})
set(CMAKE_REQUIRED_INCLUDES_CACHE ${CMAKE_REQUIRED_INCLUDES})
set(CMAKE_REQUIRED_DEFINITIONS_CACHE ${CMAKE_REQUIRED_DEFINITIONS})

set(EXPAT_EXPAT_TEST)
set(CMAKE_REQUIRED_LIBRARIES "${EXPAT_LIBRARY}")
set(CMAKE_REQUIRED_INCLUDES "${EXPAT_INCLUDE_DIR}")
CHECK_C_SOURCE_COMPILES("${EXPAT_EXPAT_CODE}" EXPAT_EXPAT_TEST)

if (NOT EXPAT_EXPAT_TEST)
set(CMAKE_REQUIRED_LIBRARIES "${EXPAT_LIBRARY}")
set(CMAKE_REQUIRED_INCLUDES "${EXPAT_INCLUDE_DIR}")
set(CMAKE_REQUIRED_DEFINITIONS "-DXML_STATIC=1")

CHECK_C_SOURCE_COMPILES("${EXPAT_EXPAT_CODE}" EXPAT_EXPAT_TEST2)
if (EXPAT_EXPAT_TEST2)
  set_target_properties(EXPAT::EXPAT PROPERTIES
    INTERFACE_COMPILE_DEFINITIONS "XML_STATIC=1"
    )
else()
  message(FATAL_ERROR "Unable to compile a test executable against expat with
  
  EXPAT_INCLUDE_DIR = ${EXPAT_INCLUDE_DIR}
  EXPAT_LIBRARY     = ${EXPAT_LIBRARY}
  ")
endif()

endif()

set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES_CACHE})
set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES_CACHE})
set(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS_CACHE})
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    EXPAT
    VERSION_VAR   EXPAT_VERSION
    REQUIRED_VARS EXPAT_LIBRARY EXPAT_INCLUDE_DIR)

mark_as_advanced(EXPAT_VERSION)
