# Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Locate libsedml
# This module defines:
# LIBSEDML_INCLUDE_DIR, where to find the headers
#
# LIBSEDML_LIBRARY,
# LIBSEDML_FOUND
#
# $LIBSEDML_DIR is an environment variable that would
# correspond to the ./configure --prefix=$LIBSEDML_DIR
#
# Created by Robert Osfield.
# Modified by Ralph Gauges


if(UNIX OR CYGWIN OR MINGW)
  set(LIBSEDML_LIBRARY_NAME sedml)
else()
  set(LIBSEDML_LIBRARY_NAME libsedml)
endif()

message (VERBOSE "Looking for ${LIBSEDML_LIBRARY_NAME}")

find_package(${LIBSEDML_LIBRARY_NAME} CONFIG QUIET)

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

if (NOT ${LIBSEDML_LIBRARY_NAME}_FOUND)
  find_package(${LIBSEDML_LIBRARY_NAME} CONFIG QUIET
    PATHS /usr/lib/cmake
          /usr/local/lib/cmake
          /opt/lib/cmake
          /opt/local/lib/cmake
          /sw/lib/cmake
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}/cmake
          ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
          ${CONAN_LIB_DIRS_LIBSEDML}/cmake
          CMAKE_FIND_ROOT_PATH_BOTH
  )
endif()

if (${LIBSEDML_LIBRARY_NAME}_FOUND)

  get_target_property(LIBSEDML_LIBRARY ${LIBSEDML_LIBRARY_NAME} LOCATION)
  get_filename_component(LIB_PATH ${LIBSEDML_LIBRARY} DIRECTORY)
  file(TO_CMAKE_PATH ${LIB_PATH}/../include LIBSEDML_INCLUDE_DIR)  
  get_filename_component (LIBSEDML_INCLUDE_DIR ${LIBSEDML_INCLUDE_DIR} REALPATH)
  get_target_property(LIBSEDML_VERSION ${LIBSEDML_LIBRARY_NAME} VERSION)

else()

find_path(LIBSEDML_INCLUDE_DIR sedml/SedBase.h
    PATHS $ENV{LIBSEDML_DIR}/include
          $ENV{LIBSEDML_DIR}
           ${${_PROJECT_DEPENDENCY_DIR}}/include
          ${${_PROJECT_DEPENDENCY_DIR}}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
          CMAKE_FIND_ROOT_PATH_BOTH
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
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/lib
          ${${_PROJECT_DEPENDENCY_DIR}}
          ${CONAN_LIB_DIRS_LIBSEDML}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
          CMAKE_FIND_ROOT_PATH_BOTH
    NO_DEFAULT_PATH)

if (NOT LIBSEDML_LIBRARY)
    find_library(LIBSEDML_LIBRARY 
        NAMES sedml-static 
              sedml)
endif (NOT LIBSEDML_LIBRARY)

if (NOT LIBSEDML_LIBRARY)
    message(FATAL_ERROR "libSEDML library not found!")
endif (NOT LIBSEDML_LIBRARY)


find_library(LIBNUML_LIBRARY 
    NAMES numl-static 
          numl
          libnuml-static 
          libnuml
    PATHS $ENV{LIBSEDML_DIR}/lib
          $ENV{LIBSEDML_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/lib
          ${${_PROJECT_DEPENDENCY_DIR}}
          ${CONAN_LIB_DIRS_LIBNUML}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
          CMAKE_FIND_ROOT_PATH_BOTH
    NO_DEFAULT_PATH)

endif()

  add_library(${LIBSEDML_LIBRARY_NAME} UNKNOWN IMPORTED)
  set_target_properties(${LIBSEDML_LIBRARY_NAME} PROPERTIES IMPORTED_LOCATION ${LIBSEDML_LIBRARY})
  set_target_properties(${LIBSEDML_LIBRARY_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES ${LIBNUML_LIBRARY})
  


if (NOT LIBSEDML_INCLUDE_DIR)
    message(FATAL_ERROR "libsedml include dir not found not found!")
endif (NOT LIBSEDML_INCLUDE_DIR)

if (NOT LIBSEDML_LIBRARY)
    message(FATAL_ERROR "LIBSEDML library not found!")
endif (NOT LIBSEDML_LIBRARY)

set(LIBSEDML_FOUND "NO")
if(LIBSEDML_LIBRARY)
    if (LIBSEDML_INCLUDE_DIR)
        SET(LIBSEDML_FOUND "YES")

        if (EXISTS "${LIBSEDML_INCLUDE_DIR}/sedml/common/libsedml-version.h")

        file(STRINGS "${LIBSEDML_INCLUDE_DIR}/sedml/common/libsedml-version.h" sedml_version_str
        REGEX "^#define[\t ]+LIBSEDML_DOTTED_VERSION[\t ]+\".*\"")
        
        string(REGEX REPLACE "^#define[\t ]+LIBSEDML_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
        LIBSEDML_VERSION "${sedml_version_str}")
        unset(sbml_version_str)
        
        
        endif()
        

    endif(LIBSEDML_INCLUDE_DIR)
endif(LIBSEDML_LIBRARY)

if (NOT TARGET ${LIBSEDML_LIBRARY_NAME})
add_library(${LIBSEDML_LIBRARY_NAME} UNKNOWN IMPORTED)
set_target_properties(${LIBSEDML_LIBRARY_NAME} PROPERTIES
  IMPORTED_LOCATION "${LIBSEDML_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${LIBSEDML_INCLUDE_DIR}")
endif()

# set static on the library on windows
if ((WIN32 AND NOT CYGWIN) AND LIBSEDML_FOUND AND LIBSEDML_LIBRARY MATCHES "static")
  set_target_properties(${LIBSEDML_LIBRARY_NAME} PROPERTIES 
  INTERFACE_COMPILE_DEFINITIONS "LIBSEDML_STATIC=1"
)

endif()


# handle the QUIETLY and REQUIRED arguments and set LIBSEDML_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBSEDML 
  VERSION_VAR LIBSEDML_VERSION
  REQUIRED_VARS LIBSEDML_LIBRARY LIBSEDML_INCLUDE_DIR)

mark_as_advanced(LIBSEDML_INCLUDE_DIR LIBSEDML_LIBRARY LIBNUML_LIBRARY)
