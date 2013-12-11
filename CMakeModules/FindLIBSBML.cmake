# Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Locate libsbml
# This module defines:
# LIBSBML_INCLUDE_DIR, where to find the headers
#
# LIBSBML_LIBRARY, LIBSBML_LIBRARY_DEBUG
# LIBSBML_FOUND
#
# $LIBSBML_DIR is an environment variable that would
# correspond to the ./configure --prefix=$LIBSBML_DIR
#
# Created by Robert Osfield.
# Modified by Ralph Gauges

message (STATUS "$ENV{LIBSBML_DIR}")

find_path(LIBSBML_INCLUDE_DIR sbml/SBase.h
    PATHS $ENV{LIBSBML_DIR}/include
          $ENV{LIBSBML_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    NO_DEFAULT_PATH)

if (NOT LIBSBML_INCLUDE_DIR)
    message(FATAL_ERROR "libsbml include dir not found not found!")
endif (NOT LIBSBML_INCLUDE_DIR)

if (NOT LIBSBML_INCLUDE_DIR)
    find_path(LIBSBML_INCLUDE_DIR sbml/SBase.h)
endif (NOT LIBSBML_INCLUDE_DIR)

find_library(LIBSBML_LIBRARY 
    NAMES sbml-static 
          sbml
          libsbml-static 
          libsbml
    PATHS $ENV{LIBSBML_DIR}/lib
          $ENV{LIBSBML_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)

if (NOT LIBSBML_LIBRARY)
    find_library(LIBSBML_LIBRARY 
        NAMES sbml-static 
              sbml)
endif (NOT LIBSBML_LIBRARY)

if (NOT LIBSBML_LIBRARY)
    message(FATAL_ERROR "LIBSBML library not found!")
endif (NOT LIBSBML_LIBRARY)

set(LIBSBML_FOUND "NO")
if(LIBSBML_LIBRARY)
    if   (LIBSBML_INCLUDE_DIR)
        SET(LIBSBML_FOUND "YES")
    endif(LIBSBML_INCLUDE_DIR)
endif(LIBSBML_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set LIBSBML_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBSBML DEFAULT_MSG LIBSBML_LIBRARY LIBSBML_INCLUDE_DIR)

mark_as_advanced(LIBSBML_INCLUDE_DIR LIBSBML_LIBRARY)
