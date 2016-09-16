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

message (STATUS "$ENV{COMBINE_DIR}")

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
    NAMES Combine-static 
          Combine
          libCombine-static
          libCombine
    PATHS $ENV{COMBINE_DIR}/lib
          $ENV{COMBINE_DIR}
          ${COPASI_DEPENDENCY_DIR}/lib
          ${COPASI_DEPENDENCY_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)
    
if (NOT COMBINE_LIBRARY)
    find_library(COMBINE_LIBRARY 
        NAMES libCombine-static
              libCombine)
endif (NOT COMBINE_LIBRARY)

find_library(ZIPPER_LIBRARY 
    NAMES Zipper-static 
          Zipper
          libZipper-static
          libZipper
    PATHS $ENV{COMBINE_DIR}/lib
          $ENV{COMBINE_DIR}
          ${COPASI_DEPENDENCY_DIR}/lib
          ${COPASI_DEPENDENCY_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)
    
if (NOT ZIPPER_LIBRARY)
    find_library(ZIPPER_LIBRARY 
        NAMES libZipper-static
              libZipper)
endif (NOT ZIPPER_LIBRARY)

if (NOT COMBINE_LIBRARY)
    message(FATAL_ERROR "COMBINE library not found!")
endif (NOT COMBINE_LIBRARY)

set(COMBINE_FOUND "NO")
if(COMBINE_LIBRARY)
    if   (COMBINE_INCLUDE_DIR)
        SET(COMBINE_FOUND "YES")
    endif(COMBINE_INCLUDE_DIR)
endif(COMBINE_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set COMBINE_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(COMBINE DEFAULT_MSG COMBINE_LIBRARY ZIPPER_LIBRARY COMBINE_INCLUDE_DIR)

mark_as_advanced(COMBINE_INCLUDE_DIR COMBINE_LIBRARY ZIPPER_LIBRARY)
