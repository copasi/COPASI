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

# - Try to find the Raptor RDF parsing library (http://librdf.org/raptor/)
# Once done this will define
#
#  RAPTOR_FOUND       - system has Raptor
#  RAPTOR_LIBRARY   - Link these to use Raptor
#  RAPTOR_INCLUDE_DIR - Include directory for using Raptor
#  RAPTOR_DEFINITIONS - Compiler switches required for using Raptor
#
#  Capabilities
#       RAPTOR_HAVE_TRIG   - Set if raptor has TRIG

# (c) 2007-2011 Sebastian Trueg <trueg@kde.org>
# (c) 2011 Artem Serebriyskiy <v.for.vandal@gmail.com>
# (c) 2011 Michael Jansen <kde@michael-jansen.biz>
#
# Based on FindFontconfig Copyright (c) 2006,2007 Laurent Montel, <montel@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

# Check if we have cached results in case the last round was successful.
if (NOT (RAPTOR_INCLUDE_DIR AND RAPTOR_LIBRARY) OR NOT RAPTOR_FOUND)

    set(RAPTOR_LDFLAGS)
	
    find_path(RAPTOR_INCLUDE_DIR raptor.h
	    PATHS $ENV{RAPTOR_DIR}/include
	          $ENV{RAPTOR_DIR}
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

    if (NOT RAPTOR_INCLUDE_DIR)
        find_path(RAPTOR_INCLUDE_DIR raptor.h)
    endif ()

    find_library(RAPTOR_LIBRARY 
	    NAMES raptor
	    PATHS $ENV{RAPTOR_DIR}/${CMAKE_INSTALL_LIBDIR}
	          $ENV{RAPTOR_DIR}/lib-dbg
	          $ENV{RAPTOR_DIR}
              ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
              ${${_PROJECT_DEPENDENCY_DIR}}/lib
	          ~/Library/Frameworks
	          /Library/Frameworks
	          /sw/lib        # Fink
	          /opt/local/lib # MacPorts
	          /opt/csw/lib   # Blastwave
	          /opt/lib
	          /usr/freeware/lib64
              CMAKE_FIND_ROOT_PATH_BOTH
             NO_DEFAULT_PATH)

    if (NOT RAPTOR_LIBRARY)
    find_library(RAPTOR_LIBRARY NAMES raptor)
    endif ()

    if (NOT WIN32)
        find_package(PkgConfig)
        pkg_check_modules(PC_RAPTOR QUIET raptor)

        if (PC_RAPTOR_FOUND)
            set(RAPTOR_DEFINITIONS ${PC_RAPTOR_CFLAGS_OTHER})
            set(RAPTOR_VERSION ${PC_RAPTOR_VERSION} CACHE STRING "Raptor Version found" )
            string( REGEX REPLACE "^.*-lraptor;" "" RAPTOR_LDFLAGS "${PC_RAPTOR_STATIC_LDFLAGS}")
            string( REGEX REPLACE "-lexpat[;]*" "" RAPTOR_LDFLAGS "${RAPTOR_LDFLAGS}")
        endif (PC_RAPTOR_FOUND)
    endif (NOT WIN32)
    
    if (RAPTOR_LDFLAGS)
        set(RAPTOR_LIBRARY ${RAPTOR_LIBRARY} ${RAPTOR_LDFLAGS})
    endif (RAPTOR_LDFLAGS)
	
    mark_as_advanced(RAPTOR_INCLUDE_DIR RAPTOR_LIBRARY)

endif () # Check for cached values


if (NOT RAPTOR_VERSION AND RAPTOR_INCLUDE_DIR AND EXISTS "${RAPTOR_INCLUDE_DIR}/win32_raptor_config.h")

file(STRINGS "${RAPTOR_INCLUDE_DIR}/win32_raptor_config.h" raptor_version_str
REGEX "^#define[\t ]+VERSION[\t ]+\".*\"")

string(REGEX REPLACE "^#define[\t ]+VERSION[\t ]+\"([^\"]*)\".*" "\\1"
RAPTOR_VERSION "${raptor_version_str}")
unset(raptor_version_str)


endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    RAPTOR
    VERSION_VAR   RAPTOR_VERSION
    REQUIRED_VARS RAPTOR_LIBRARY RAPTOR_INCLUDE_DIR)

mark_as_advanced(RAPTOR_VERSION)

if (NOT RAPTOR_FOUND AND Raptor_FIND_VERSION_MAJOR EQUAL "2" AND NOT Raptor_FIND_QUIET )
    pkg_check_modules(PC_RAPTOR QUIET raptor)
    if (PC_RAPTOR_FOUND)
        message( STATUS "You have raptor1 version ${PC_RAPTOR_VERSION} installed. Please update." )
    endif ()
endif ()

if(NOT TARGET RAPTOR::RAPTOR)
  add_library(RAPTOR::RAPTOR UNKNOWN IMPORTED)
  set_target_properties(RAPTOR::RAPTOR PROPERTIES
    IMPORTED_LOCATION "${RAPTOR_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${RAPTOR_INCLUDE_DIR}")
endif()

if ((WIN32 AND NOT CYGWIN) AND RAPTOR_FOUND)
  set_target_properties(RAPTOR::RAPTOR PROPERTIES 
  INTERFACE_COMPILE_DEFINITIONS "RAPTOR_STATIC")
endif()
