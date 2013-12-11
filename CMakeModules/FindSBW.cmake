# Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Try to find the Systems Biology Workbench (SBW) library
# Once done this will define
#
#  SBW_FOUND - system has BZip2
#  SBW_INCLUDE_DIR - the BZip2 include directory
#  SBW_LIBRARIES - Link these to use BZip2

find_path(SBW_INCLUDE_DIR SBW/SBW.h
    PATHS $ENV{SBW_DIR}/include
          $ENV{SBW_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    NO_DEFAULT_PATH)

if (NOT SBW_INCLUDE_DIR)
    find_path(SBW_INCLUDE_DIR SBW/SBW.h)
endif ()

find_library(SBW_LIBRARIES
    NAMES SBW-static
          SBW
          sbw 
          libSBW 
          libsbw
    PATHS $ENV{SBW_DIR}/lib
          $ENV{SBW_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)

if (NOT SBW_LIBRARIES)
    find_library(SBW_LIBRARIES
        NAMES SBW-static
              SBW
              sbw 
              libSBW 
              libsbw)
endif ()

if (SBW_LIBRARIES AND WIN32)
   set(SBW_LIBRARIES ${SBW_LIBRARIES} Ws2_32.lib)
endif (SBW_LIBRARIES AND WIN32)

# handle the QUIETLY and REQUIRED arguments and set SBW_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SBW DEFAULT_MSG SBW_LIBRARIES SBW_INCLUDE_DIR)

mark_as_advanced(SBW_INCLUDE_DIR SBW_LIBRARIES)

set(SBW_FOUND "NO")

if(SBW_LIBRARIES AND SBW_INCLUDE_DIR)
        SET(SBW_FOUND "YES")
endif(SBW_LIBRARIES AND SBW_INCLUDE_DIR)
