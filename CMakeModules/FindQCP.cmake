# Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Try to find the qcustomplot library
# Once done this will define
#
#  QCP_FOUND - system has qcustomplot
#  QCP_INCLUDE_DIR - the qcustomplot include directory
#  QCP_LIBRARIES - Link these to use qcustomplot

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

find_path(QCP_INCLUDE_DIR qcustomplot.h
    PATHS $ENV{QCP_DIR}/include
          $ENV{QCP_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/include
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    NO_DEFAULT_PATH)

if (NOT QCP_INCLUDE_DIR)
    find_path(QCP_INCLUDE_DIR qcustomplot.h)
endif ()

find_library(QCP_LIBRARY
    NAMES qcustomplot qcustomplot.lib
    PATHS ${${_PROJECT_DEPENDENCY_DIR}}/lib
          ${${_PROJECT_DEPENDENCY_DIR}}/lib64
          $ENV{QCP_DIR}/lib
          $ENV{QCP_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
     NO_DEFAULT_PATH)

if (NOT QCP_LIBRARY)
find_library(QCP_LIBRARY
    NAMES qcustomplot qcustomplot.lib
)
endif()

if (NOT QCP_INCLUDE_DIR)
  message(FATAL_ERROR "qcustomplot.h not found!")
endif (NOT QCP_INCLUDE_DIR)


if (NOT QCP_LIBRARY)
  message(FATAL_ERROR "qcustomplot library not found!")
endif (NOT QCP_LIBRARY)

if (NOT TARGET QCP::QCP)
add_library(QCP::QCP UNKNOWN IMPORTED)
set_target_properties(QCP::QCP
  PROPERTIES
    IMPORTED_LOCATION ${QCP_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${QCP_INCLUDE_DIR}
)
endif()

set(QCP_FOUND "NO")
if(QCP_LIBRARY AND QCP_INCLUDE_DIR)
  set(QCP_FOUND "YES")
endif(QCP_LIBRARY AND QCP_INCLUDE_DIR)


# handle the QUIETLY and REQUIRED arguments and set QCP_FOUND to TRUE if
# all listed variables are TRUE

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QCP DEFAULT_MSG QCP_LIBRARY QCP_INCLUDE_DIR)

mark_as_advanced(QCP_INCLUDE_DIR QCP_LIBRARY)
