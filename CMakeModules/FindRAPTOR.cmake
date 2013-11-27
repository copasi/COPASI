# Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# - Try to find the Raptor RDF parsing library (http://librdf.org/raptor/)
# Once done this will define
#
#  RAPTOR_FOUND       - system has Raptor
#  RAPTOR_LIBRARIES   - Link these to use Raptor
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


MACRO (FIND_RAPTOR)

ENDMACRO ()



# Check if we have cached results in case the last round was successful.
if (NOT (RAPTOR_INCLUDE_DIR AND RAPTOR_LIBRARIES) OR NOT RAPTOR_FOUND)

    set(RAPTOR_LDFLAGS)
	
    find_path(RAPTOR_INCLUDE_DIR raptor.h
	    PATHS $ENV{RAPTOR_DIR}/include
	          $ENV{RAPTOR_DIR}
	          ~/Library/Frameworks
	          /Library/Frameworks
	          /sw/include        # Fink
	          /opt/local/include # MacPorts
	          /opt/csw/include   # Blastwave
	          /opt/include
	          /usr/freeware/include
             NO_DEFAULT_PATH)

    if (NOT RAPTOR_INCLUDE_DIR)
        find_path(RAPTOR_INCLUDE_DIR raptor.h)
    endif ()

    find_library(RAPTOR_LIBRARY 
	    NAMES raptor
	    PATHS $ENV{RAPTOR_DIR}/lib
	          $ENV{RAPTOR_DIR}/lib-dbg
	          $ENV{RAPTOR_DIR}
	          ~/Library/Frameworks
	          /Library/Frameworks
	          /sw/lib        # Fink
	          /opt/local/lib # MacPorts
	          /opt/csw/lib   # Blastwave
	          /opt/lib
	          /usr/freeware/lib64
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

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    Raptor
    VERSION_VAR   RAPTOR_VERSION
    REQUIRED_VARS RAPTOR_LIBRARY RAPTOR_INCLUDE_DIR)

mark_as_advanced(RAPTOR_VERSION)

if (NOT RAPTOR_FOUND AND Raptor_FIND_VERSION_MAJOR EQUAL "2" AND NOT Raptor_FIND_QUIET )
    pkg_check_modules(PC_RAPTOR QUIET raptor)
    if (PC_RAPTOR_FOUND)
        message( STATUS "You have raptor1 version ${PC_RAPTOR_VERSION} installed. Please update." )
    endif ()
endif ()
