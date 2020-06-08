# Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Try to find the qwtplot3d library
# Once done this will define
#
#  QWTPLOT3D_FOUND - system has qwtplot3d
#  QWTPLOT3D_INCLUDE_DIR - the qwtplot3d include directory
#  QWTPLOT3D_LIBRARY - Link these to use qwtplot3d

find_path(QWTPLOT3D_INCLUDE_DIR qwt3d_plot.h
    PATHS $ENV{QWTPLOT3D_DIR}/include
          $ENV{QWTPLOT3D_DIR}
          ${QT_INCLUDE_DIRS}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include # Blastwave
          /opt/include
          /usr/freeware/include
    PATH_SUFFIXES qwtplot3d qwtplot3d-qt4 
    NO_DEFAULT_PATH)

if (NOT QWTPLOT3D_INCLUDE_DIR)
    find_path(QWTPLOT3D_INCLUDE_DIR qwt3d_plot.h
        PATH_SUFFIXES qwtplot3d qwtplot3d-qt4)
endif (NOT QWTPLOT3D_INCLUDE_DIR)

find_library(QWTPLOT3D_LIBRARY
    NAMES qwtplot3d-static
          qwtplot3d-qt4
          qwtplot3d-qt5
          qwtplot3d
    PATHS $ENV{QWTPLOT3D_DIR}/lib
          $ENV{QWTPLOT3D_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/lib
          /usr/local/lib64
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)

if (NOT QWTPLOT3D_LIBRARY)
    find_library(QWTPLOT3D_LIBRARY
        NAMES qwtplot3d-static
              qwtplot3d-qt4
              qwtplot3d-qt5
              qwtplot3d)
endif (NOT QWTPLOT3D_LIBRARY)

if (NOT QWTPLOT3D_INCLUDE_DIR)
  message(FATAL_ERROR "qwt3d_plot.h not found!")
endif (NOT QWTPLOT3D_INCLUDE_DIR)

if (NOT QWTPLOT3D_LIBRARY)
  message(FATAL_ERROR "qwtplot3D library not found!")
endif (NOT QWTPLOT3D_LIBRARY)

set(QWTPLOT3D_FOUND "NO")

if(QWTPLOT3D_LIBRARY AND QWTPLOT3D_INCLUDE_DIR)
  set(QWTPLOT3D_FOUND "YES")
endif(QWTPLOT3D_LIBRARY AND QWTPLOT3D_INCLUDE_DIR)

# handle the QUIETLY and REQUIRED arguments and set QWTPLOT3D_FOUND to TRUE if
# all listed variables are TRUE

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QWTPLOT3D DEFAULT_MSG QWTPLOT3D_LIBRARY QWTPLOT3D_INCLUDE_DIR)

mark_as_advanced(QWTPLOT3D_INCLUDE_DIR QWTPLOT3D_LIBRARY)

