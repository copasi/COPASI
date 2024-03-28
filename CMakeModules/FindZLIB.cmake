# Copyright (C) 2022 - 2023 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# - Try to find the Zlib XML parsing library 

# Once done this will define
#
#  ZLIB_FOUND       - system has Zlib
#  ZLIB_LIBRARIES   - Link these to use Zlib
#  ZLIB_INCLUDE_DIR - Include directory for using Zlib
#  ZLIB_DEFINITIONS - Compiler switches required for using Zlib
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.


MACRO (FIND_ZLIB)

ENDMACRO ()

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

# Check if we have cached results in case the last round was successful.
if (NOT (ZLIB_INCLUDE_DIR AND ZLIB_LIBRARY) OR NOT ZLIB_FOUND)

    set(ZLIB_LDFLAGS)
	
    find_path(ZLIB_INCLUDE_DIR zlib.h zlib/zlib.h
	    PATHS $ENV{ZLIB_DIR}/include
	          $ENV{ZLIB_DIR}
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

    if (NOT ZLIB_INCLUDE_DIR)
        find_path(ZLIB_INCLUDE_DIR zlib.h zlib/zlib.h)
    endif ()

    find_library(ZLIB_LIBRARY 
	    NAMES zdll.lib z zlib.lib libzlib zlib libzlib.a 
	    PATHS $ENV{ZLIB_DIR}/lib
	          $ENV{ZLIB_DIR}/lib-dbg
	          $ENV{ZLIB_DIR}
              ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
              ${${_PROJECT_DEPENDENCY_DIR}}/lib
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

    if (NOT ZLIB_LIBRARY)
        find_library(ZLIB_LIBRARY NAMES zdll.lib z zlib.lib libzlib zlib libzlib.a)
    endif ()

    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_ZLIB QUIET zlib)

        message(VERBOSE "${PC_ZLIB_STATIC_LDFLAGS}")

        if (PC_ZLIB_FOUND)
            set(ZLIB_DEFINITIONS ${PC_ZLIB_CFLAGS_OTHER})
            set(ZLIB_VERSION ${PC_ZLIB_VERSION} CACHE STRING "Zlib Version found" )
        endif (PC_ZLIB_FOUND)
    endif (NOT WIN32)
    
    mark_as_advanced(ZLIB_INCLUDE_DIR ZLIB_LIBRARY)

endif () # Check for cached values

# create an zlib target to link against
if(NOT TARGET ZLIB::ZLIB)
  add_library(ZLIB::ZLIB UNKNOWN IMPORTED)
  set_target_properties(ZLIB::ZLIB PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${ZLIB_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${ZLIB_INCLUDE_DIR}")
endif()


include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    ZLIB
    VERSION_VAR   ZLIB_VERSION
    REQUIRED_VARS ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

mark_as_advanced(ZLIB_VERSION)
