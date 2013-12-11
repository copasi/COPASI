# Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Locate libsedml
# This module defines:
# LIBSEDML_INCLUDE_DIR, where to find the headers
#
# LIBSEDML_LIBRARY, LIBSEDML_LIBRARY_DEBUG
# LIBSEDML_FOUND
#
# $LIBSEDML_DIR is an environment variable that would
# correspond to the ./configure --prefix=$LIBSEDML_DIR
#
# Created by Robert Osfield.
# Modified by Ralph Gauges

find_path(LIBSEDML_INCLUDE_DIR sedml/SedBase.h
    PATHS $ENV{LIBSEDML_DIR}/include
          $ENV{LIBSEDML_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    NO_DEFAULT_PATH)

if (NOT LIBSEDML_INCLUDE_DIR)
    find_path(LIBSEDML_INCLUDE_DIR sedml/SedBase.h)
endif (NOT LIBSEDML_INCLUDE_DIR)

find_library(LIBSEDML_LIBRARY 
    NAMES sedml-static 
          sedml
          libsedml-static 
          libsedml
    PATHS $ENV{LIBSEDML_DIR}/lib
          $ENV{LIBSEDML_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)

if (NOT LIBSEDML_LIBRARY)
    find_library(LIBSEDML_LIBRARY 
        NAMES sedml-static 
              sedml)
endif (NOT LIBSEDML_LIBRARY)

if (NOT LIBSEDML_INCLUDE_DIR)
    message(FATAL_ERROR "libsedml include dir not found not found!")
endif (NOT LIBSEDML_INCLUDE_DIR)

if (NOT LIBSEDML_LIBRARY)
    message(FATAL_ERROR "LIBSEDML library not found!")
endif (NOT LIBSEDML_LIBRARY)

set(LIBSEDML_FOUND "NO")
if(LIBSEDML_LIBRARY)
    if   (LIBSEDML_INCLUDE_DIR)
        SET(LIBSEDML_FOUND "YES")
    endif(LIBSEDML_INCLUDE_DIR)
endif(LIBSEDML_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set LIBSEDML_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBSEDML DEFAULT_MSG LIBSEDML_LIBRARY LIBSEDML_INCLUDE_DIR)

mark_as_advanced(LIBSEDML_INCLUDE_DIR LIBSEDML_LIBRARY)
