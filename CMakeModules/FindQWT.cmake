# Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
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
    PATH_SUFFIXES qt5/qwt6 qwt qwt-qt4 qwt-qt5 qwt6
    NO_DEFAULT_PATH)

if (NOT QWT_INCLUDE_DIR)
    find_path(QWT_INCLUDE_DIR qwt.h
        PATH_SUFFIXES qt5/qwt6 qwt qwt-qt4 qwt-qt5 qwt6)
endif ()

find_library(QWT_LIBRARY
    NAMES qwt-qt5
          qwt-qt4
          qwt-static
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
        NAMES qwt-qt5
              qwt-qt4
              qwt-static
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

  if (EXISTS "${QWT_INCLUDE_DIR}/qwt_global.h")

    file(STRINGS "${QWT_INCLUDE_DIR}/qwt_global.h" QWT_H REGEX "^#define QWT_VERSION[ ]*[^\"]*$")

    string(REGEX REPLACE ".*QWT_VERSION[ ]*0x([0-9]+).*$" "\\1" QWT_VERSION_HEX "${QWT_H}")
    set(QWT_VERSION_HEX 0x${QWT_VERSION_HEX} CACHE STRING "")

    file(STRINGS "${QWT_INCLUDE_DIR}/qwt_global.h" QWT_H REGEX "^#define QWT_VERSION_STR[ ]*\"[^\"]*\"$")

    string(REGEX REPLACE ".*QWT_VERSION_STR[ ]*\"([0-9]+).*$" "\\1" QWT_VERSION_MAJOR "${QWT_H}")
    string(REGEX REPLACE ".*QWT_VERSION_STR[ ]*\"[0-9]+\\.([0-9]+).*$" "\\1" QWT_VERSION_MINOR  "${QWT_H}")
    string(REGEX REPLACE ".*QWT_VERSION_STR[ ]*\"[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" QWT_VERSION_PATCH "${QWT_H}")
    set(QWT_VERSION_STRING "${QWT_VERSION_MAJOR}.${QWT_VERSION_MINOR}.${QWT_VERSION_PATCH}" CACHE STRING "")

    # only append a TWEAK version if it exists:
    set(QWT_VERSION_TWEAK "")
    if( "${QWT_H}" MATCHES "QWT_VERSION_STR \"[0-9]+\\.[0-9]+\\.[0-9]+\\.([0-9]+)")
        set(QWT_VERSION_TWEAK "${CMAKE_MATCH_1}")
        set(QWT_VERSION_STRING "${QWT_VERSION_STRING}.${QWT_VERSION_TWEAK}")
    endif()

    set(QWT_MAJOR_VERSION "${QWT_VERSION_MAJOR}")
    set(QWT_MINOR_VERSION "${QWT_VERSION_MINOR}")
    set(QWT_PATCH_VERSION "${QWT_VERSION_PATCH}")

    MATH(EXPR QWT_VERSION_NUMERIC "${QWT_VERSION_MAJOR} * 10000 + ${QWT_VERSION_MINOR} * 100 + ${QWT_VERSION_PATCH}" )
  endif()

endif(QWT_LIBRARY AND QWT_INCLUDE_DIR)

# handle the QUIETLY and REQUIRED arguments and set QWT_FOUND to TRUE if
# all listed variables are TRUE

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QWT DEFAULT_MSG QWT_LIBRARY QWT_INCLUDE_DIR QWT_VERSION_HEX QWT_VERSION_STRING QWT_VERSION_MAJOR QWT_VERSION_MINOR QWT_VERSION_NUMERIC)

mark_as_advanced(QWT_INCLUDE_DIR QWT_LIBRARY QWT_VERSION_HEX QWT_VERSION_STRING QWT_VERSION_MAJOR QWT_VERSION_MINOR QWT_VERSION_NUMERIC)

