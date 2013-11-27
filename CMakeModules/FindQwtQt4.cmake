# Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Try to find the Qwt library
# Once done this will define
#
#  QWT_FOUND - system has qwt
#  QWT_INCLUDE_DIR - the qwt include directory
#  QWT_LIBRARY - Link these to use qwt

find_path(QWT_INCLUDE_DIR qwt.h
    PATHS $ENV{QWT_DIR}/include
          $ENV{QWT_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    PATH_SUFFIXES qwt qwt-qt4
    NO_DEFAULT_PATH)

if (NOT QWT_INCLUDE_DIR)
    find_path(QWT_INCLUDE_DIR qwt.h)
endif ()

find_library(QWT_LIBRARY
    NAMES qwt-static
          qwt-qt4
          qwt
    PATHS $ENV{QWT_DIR}/lib
          $ENV{QWT_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)

if (NOT QWT_LIBRARY)
    find_library(QWT_LIBRARY
        NAMES qwt-static
              qwt-qt4
              qwt)
endif (NOT QWT_LIBRARY)

if (NOT QWT_INCLUDE_DIR)
  message(FATAL_ERROR "qwt.h not found!")
endif (NOT QWT_INCLUDE_DIR)

if (NOT QWT_LIBRARY)
  message(FATAL_ERROR "qwt library not found!")
endif (NOT QWT_LIBRARY)

set(QWT_FOUND "NO")

if(QWT_LIBRARY AND QWT_INCLUDE_DIR)
  set(QWT_FOUND "YES")
endif(QWT_LIBRARY AND QWT_INCLUDE_DIR)

# handle the QUIETLY and REQUIRED arguments and set QWT_FOUND to TRUE if
# all listed variables are TRUE

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QWT DEFAULT_MSG QWT_LIBRARY QWT_INCLUDE_DIR)

mark_as_advanced(QWT_INCLUDE_DIR QWT_LIBRARY)

