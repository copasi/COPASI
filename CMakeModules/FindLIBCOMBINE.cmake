# Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

#
# Locate libLIBCOMBINE
# This module defines:
# LIBCOMBINE_INCLUDE_DIR, where to find the headers
#
# LIBCOMBINE_LIBRARY
# LIBCOMBINE_FOUND
#
# Created by Robert Osfield.
# Modified by Ralph Gauges

set(LIBCOMBINE_LIBRARY_NAME)
if (UNIX)
  set(LIBCOMBINE_LIBRARY_NAME Combine-static)
else()
  set(LIBCOMBINE_LIBRARY_NAME libCombine-static)
endif()

find_package(${LIBCOMBINE_LIBRARY_NAME} CONFIG QUIET)

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

if (NOT ${LIBCOMBINE_LIBRARY_NAME}_FOUND)
  find_package(${LIBCOMBINE_LIBRARY_NAME} CONFIG QUIET
  CONFIGS ${LIBCOMBINE_LIBRARY_NAME}-config.cmake
  PATHS $ENV{LIBCOMBINE_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        $ENV{LIBCOMBINE_DIR}/lib/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib64/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
        $ENV{LIBCOMBINE_DIR}/lib/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
        /usr/lib/cmake
        ${CONAN_LIB_DIRS_LIBCOMBINE}/cmake
        CMAKE_FIND_ROOT_PATH_BOTH
  )
endif()

if (${LIBCOMBINE_LIBRARY_NAME}_FOUND)

get_target_property(LIBCOMBINE_INCLUDE_DIR ${LIBCOMBINE_LIBRARY_NAME} INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(LIBCOMBINE_LIBRARY ${LIBCOMBINE_LIBRARY_NAME} IMPORTED_LOCATION_RELEASE)

if (NOT LIBCOMBINE_LIBRARY)
  get_target_property(LIBCOMBINE_LIBRARY ${LIBCOMBINE_LIBRARY_NAME} IMPORTED_LOCATION_DEBUG)
endif(NOT LIBCOMBINE_LIBRARY)

if (NOT LIBCOMBINE_LIBRARY)
  set(LIBCOMBINE_LIBRARY)
endif(NOT LIBCOMBINE_LIBRARY)

get_target_property(LIBCOMBINE_INTERFACE_LINK_LIBRARIES ${LIBCOMBINE_LIBRARY_NAME} INTERFACE_LINK_LIBRARIES)

  if (NOT LIBCOMBINE_INTERFACE_LINK_LIBRARIES)
  get_target_property(LIBCOMBINE_INTERFACE_LINK_LIBRARIES ${LIBCOMBINE_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE)
  endif()

  if (NOT LIBCOMBINE_INTERFACE_LINK_LIBRARIES)
  get_target_property(LIBCOMBINE_INTERFACE_LINK_LIBRARIES ${LIBCOMBINE_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG)
  endif()

  if (NOT LIBCOMBINE_INTERFACE_LINK_LIBRARIES)
  get_target_property(LIBCOMBINE_INTERFACE_LINK_LIBRARIES ${LIBCOMBINE_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG)
  endif()

  if (LIBCOMBINE_INTERFACE_LINK_LIBRARIES)
    set(LIBCOMBINE_LIBRARY ${LIBCOMBINE_LIBRARY} ${LIBCOMBINE_INTERFACE_LINK_LIBRARIES})
  endif (LIBCOMBINE_INTERFACE_LINK_LIBRARIES)

  foreach (library ${LIBCOMBINE_INTERFACE_LINK_LIBRARIES})
  
    string(FIND "${library}" "::" index)

    if (${index} GREATER 0)
      # found dependent library
      string(SUBSTRING "${library}" 0 ${index} DEPENDENT_NAME)
      message(VERBOSE "Looking for dependent library: ${DEPENDENT_NAME}")
      find_package(${DEPENDENT_NAME})
      if (NOT ${DEPENDENT_NAME}_FOUND)
      find_package(${DEPENDENT_NAME} CONFIG QUIET
      PATHS $ENV{LIBCOMBINE_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        $ENV{LIBCOMBINE_DIR}/lib/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib64/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
        $ENV{LIBCOMBINE_DIR}/lib/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
        /usr/lib/cmake
        ${CONAN_LIB_DIRS_LIBCOMBINE}/cmake
        CMAKE_FIND_ROOT_PATH_BOTH
      )
      endif()
    endif()
  
  endforeach()

else()
  # Fallback if no CONFIG is found

  find_path(LIBCOMBINE_INCLUDE_DIR combine/combinearchive.h
    PATHS $ENV{LIBCOMBINE_DIR}/include
          $ENV{LIBCOMBINE_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/include
          ${${_PROJECT_DEPENDENCY_DIR}}
          
    NO_DEFAULT_PATH)

  if (NOT LIBCOMBINE_INCLUDE_DIR)
    find_path(LIBCOMBINE_INCLUDE_DIR combine/combinearchive.h
          $ENV{LIBCOMBINE_DIR}/include
          $ENV{LIBCOMBINE_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/include
          ${${_PROJECT_DEPENDENCY_DIR}}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
          CMAKE_FIND_ROOT_PATH_BOTH)
  endif (NOT LIBCOMBINE_INCLUDE_DIR)

  if (NOT LIBCOMBINE_INCLUDE_DIR)
    message(FATAL_ERROR "LIBCOMBINE include dir not found not found!")
  endif (NOT LIBCOMBINE_INCLUDE_DIR)

  find_library(LIBCOMBINE_LIBRARY 
    NAMES ${LIBCOMBINE_LIBRARY_NAME}
    PATHS $ENV{LIBCOMBINE_DIR}/lib
          $ENV{LIBCOMBINE_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/lib
          ${${_PROJECT_DEPENDENCY_DIR}}
          ${CONAN_LIB_DIRS_LIBCOMBINE}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib         Fink
          /opt/local/lib  MacPorts
          /opt/csw/lib    Blastwave
          /opt/lib
          /usr/freeware/lib64
          CMAKE_FIND_ROOT_PATH_BOTH
    NO_DEFAULT_PATH)
    
  if (NOT LIBCOMBINE_LIBRARY)
    find_library(LIBCOMBINE_LIBRARY 
        NAMES ${LIBCOMBINE_LIBRARY_NAME}
        PATHS $ENV{LIBCOMBINE_DIR}/lib
        $ENV{LIBCOMBINE_DIR}
        ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
        ${${_PROJECT_DEPENDENCY_DIR}}/lib
        ${${_PROJECT_DEPENDENCY_DIR}}
        ${CONAN_LIB_DIRS_LIBCOMBINE}
        ~/Library/Frameworks
        /Library/Frameworks
        /sw/lib         Fink
        /opt/local/lib  MacPorts
        /opt/csw/lib    Blastwave
        /opt/lib
        /usr/freeware/lib64
        CMAKE_FIND_ROOT_PATH_BOTH)
  endif (NOT LIBCOMBINE_LIBRARY)
endif(${LIBCOMBINE_LIBRARY_NAME}_FOUND)

if (NOT LIBCOMBINE_LIBRARY)
    message(FATAL_ERROR "LIBCOMBINE library not found!")
endif (NOT LIBCOMBINE_LIBRARY)

if (NOT TARGET ${LIBCOMBINE_LIBRARY_NAME})
add_library(${LIBCOMBINE_LIBRARY_NAME} UNKNOWN IMPORTED)
set_target_properties(${LIBCOMBINE_LIBRARY_NAME} PROPERTIES
  IMPORTED_LOCATION "${LIBCOMBINE_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${LIBCOMBINE_INCLUDE_DIR}")
endif()

set(LIBCOMBINE_FOUND "NO")
if(LIBCOMBINE_LIBRARY)
  if (LIBCOMBINE_INCLUDE_DIR)
    SET(LIBCOMBINE_FOUND "YES")
    
    # # see whether library works and get version
    # SET(ADDITIONAL_DEFS)
    # if ("${LIBCOMBINE_LIBRARY}" MATCHES "static")
    #   SET(ADDITIONAL_DEFS ${ADDITIONAL_DEFS} "-DLIBCOMBINE_STATIC=1")
    # endif()
    # 
    # set(TEST_FILE ${CMAKE_BINARY_DIR}/test_libcombine.cpp)
    # file(WRITE ${TEST_FILE} "#include <omex/common/libcombine-version.h>
    # #include <iostream>
    # 
    # using namespace std;
    # 
    # int main()
    # {
    #   cout << getLibCombineDottedVersion() << endl;
    #   return 0;
    # }
    # ")
    # 
    # try_run(
    #   LIBCOMBINE_VERSIONTEST_EXITCODE
    #   LIBCOMBINE_VERSIONTEST_COMPILE
    #   ${CMAKE_BINARY_DIR}
    #   ${TEST_FILE}
    #   CMAKE_FLAGS -DINCLUDE_DIRECTORIES=${LIBCOMBINE_INCLUDE_DIR}
    #   COMPILE_DEFINITIONS ${ADDITIONAL_DEFS}
    #   LINK_LIBRARIES ${LIBCOMBINE_LIBRARY}
    #   RUN_OUTPUT_VARIABLE LIBCOMBINE_VERSION
    #   COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT
    # )
    # 
    # if (LIBCOMBINE_VERSION)
    #   string(STRIP ${LIBCOMBINE_VERSION} LIBCOMBINE_VERSION)
    #   if (LIBCOMBINE_VERSION)
    #     message("Found libCombine Version: ${LIBCOMBINE_VERSION}")
    #   endif()
    # endif()
    
    
  endif(LIBCOMBINE_INCLUDE_DIR)
endif(LIBCOMBINE_LIBRARY)


if (LIBCOMBINE_INCLUDE_DIR AND EXISTS "${LIBCOMBINE_INCLUDE_DIR}/omex/common/libcombine-version.h")

file(STRINGS "${LIBCOMBINE_INCLUDE_DIR}/omex/common/libcombine-version.h" combine_version_str
REGEX "^#define[\t ]+LIBCOMBINE_DOTTED_VERSION[\t ]+\".*\"")

string(REGEX REPLACE "^#define[\t ]+LIBCOMBINE_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
LIBCOMBINE_VERSION "${combine_version_str}")
unset(combine_version_str)

endif()


# set static on the library on windows
if ((WIN32 AND NOT CYGWIN) AND LIBCOMBINE_FOUND AND LIBCOMBINE_LIBRARY MATCHES "static")
  set_target_properties(${LIBCOMBINE_LIBRARY_NAME} PROPERTIES 
  INTERFACE_COMPILE_DEFINITIONS "LIBCOMBINE_STATIC=1"
)

endif()


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBCOMBINE 
VERSION_VAR LIBCOMBINE_VERSION
REQUIRED_VARS LIBCOMBINE_LIBRARY LIBCOMBINE_INCLUDE_DIR)

mark_as_advanced(LIBCOMBINE_VERSION)
