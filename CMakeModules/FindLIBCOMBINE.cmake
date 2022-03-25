# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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
# Locate libCOMBINE
# This module defines:
# COMBINE_INCLUDE_DIR, where to find the headers
#
# COMBINE_LIBRARY
# COMBINE_FOUND
#
# Created by Robert Osfield.
# Modified by Ralph Gauges

set(COMBINE_LIBRARY_NAME)
if (UNIX)
  set(COMBINE_LIBRARY_NAME Combine-static)
else()
  set(COMBINE_LIBRARY_NAME libCombine-static)
endif()

find_package(${COMBINE_LIBRARY_NAME} CONFIG QUIET)

if (NOT ${COMBINE_LIBRARY_NAME}_FOUND)
  find_package(${COMBINE_LIBRARY_NAME} CONFIG QUIET
  CONFIGS ${COMBINE_LIBRARY_NAME}-config.cmake
  PATHS $ENV{COMBINE_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
        $ENV{COMBINE_DIR}/lib/cmake
        ${COPASI_DEPENDENCY_DIR}/lib/cmake
        /usr/lib/cmake
        ${CONAN_LIB_DIRS_LIBCOMBINE}/cmake
  )
endif()

if (${COMBINE_LIBRARY_NAME}_FOUND)

get_target_property(COMBINE_INCLUDE_DIR ${COMBINE_LIBRARY_NAME} INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(COMBINE_LIBRARY ${COMBINE_LIBRARY_NAME} IMPORTED_LOCATION_RELEASE)

if (NOT COMBINE_LIBRARY)
  get_target_property(COMBINE_LIBRARY ${COMBINE_LIBRARY_NAME} IMPORTED_LOCATION_DEBUG)
endif(NOT COMBINE_LIBRARY)

if (NOT COMBINE_LIBRARY)
  set(COMBINE_LIBRARY)
endif(NOT COMBINE_LIBRARY)

get_target_property(COMBINE_INTERFACE_LINK_LIBRARIES ${COMBINE_LIBRARY_NAME} INTERFACE_LINK_LIBRARIES)

  if (NOT COMBINE_INTERFACE_LINK_LIBRARIES)
  get_target_property(COMBINE_INTERFACE_LINK_LIBRARIES ${COMBINE_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE)
  endif()

  if (NOT COMBINE_INTERFACE_LINK_LIBRARIES)
  get_target_property(COMBINE_INTERFACE_LINK_LIBRARIES ${COMBINE_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG)
  endif()

  if (NOT COMBINE_INTERFACE_LINK_LIBRARIES)
  get_target_property(COMBINE_INTERFACE_LINK_LIBRARIES ${COMBINE_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG)
  endif()

  if (COMBINE_INTERFACE_LINK_LIBRARIES)
    set(COMBINE_LIBRARY ${COMBINE_LIBRARY} ${COMBINE_INTERFACE_LINK_LIBRARIES})
  endif (COMBINE_INTERFACE_LINK_LIBRARIES)

  foreach (library ${COMBINE_INTERFACE_LINK_LIBRARIES})
  
    string(FIND "${library}" "::" index)

    if (${index} GREATER 0)
      # found dependent library
      string(SUBSTRING "${library}" 0 ${index} DEPENDENT_NAME)
      message(STATUS "Looking for dependent library: ${DEPENDENT_NAME}")
      find_package(${DEPENDENT_NAME})
    endif()
  
  endforeach()

else()
  # Fallback if no CONFIG is found

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
    NAMES ${COMBINE_LIBRARY_NAME}
    PATHS $ENV{COMBINE_DIR}/lib
          $ENV{COMBINE_DIR}
          ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}
          ${COPASI_DEPENDENCY_DIR}/lib
          ${COPASI_DEPENDENCY_DIR}
          ${CONAN_LIB_DIRS_LIBCOMBINE}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib         Fink
          /opt/local/lib  MacPorts
          /opt/csw/lib    Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)
    
  if (NOT COMBINE_LIBRARY)
    find_library(COMBINE_LIBRARY 
        NAMES ${COMBINE_LIBRARY_NAME})
  endif (NOT COMBINE_LIBRARY)
endif(${COMBINE_LIBRARY_NAME}_FOUND)

if (NOT COMBINE_LIBRARY)
    message(FATAL_ERROR "COMBINE library not found!")
endif (NOT COMBINE_LIBRARY)

if (NOT TARGET ${COMBINE_LIBRARY_NAME})
add_library(${COMBINE_LIBRARY_NAME} UNKNOWN IMPORTED)
set_target_properties(${COMBINE_LIBRARY_NAME} PROPERTIES
  IMPORTED_LOCATION "${COMBINE_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${COMBINE_INCLUDE_DIR}")
endif()

set(COMBINE_FOUND "NO")
if(COMBINE_LIBRARY)
  if (COMBINE_INCLUDE_DIR)
    SET(COMBINE_FOUND "YES")
    
    # # see whether library works and get version
    # SET(ADDITIONAL_DEFS)
    # if ("${COMBINE_LIBRARY}" MATCHES "static")
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
    #   CMAKE_FLAGS -DINCLUDE_DIRECTORIES=${COMBINE_INCLUDE_DIR}
    #   COMPILE_DEFINITIONS ${ADDITIONAL_DEFS}
    #   LINK_LIBRARIES ${COMBINE_LIBRARY}
    #   RUN_OUTPUT_VARIABLE COMBINE_VERSION
    #   COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT
    # )
    # 
    # if (COMBINE_VERSION)
    #   string(STRIP ${COMBINE_VERSION} COMBINE_VERSION)
    #   if (COMBINE_VERSION)
    #     message("Found libCombine Version: ${COMBINE_VERSION}")
    #   endif()
    # endif()
    
    
  endif(COMBINE_INCLUDE_DIR)
endif(COMBINE_LIBRARY)


if (COMBINE_INCLUDE_DIR AND EXISTS "${COMBINE_INCLUDE_DIR}/omex/common/libcombine-version.h")

file(STRINGS "${COMBINE_INCLUDE_DIR}/omex/common/libcombine-version.h" combine_version_str
REGEX "^#define[\t ]+LIBCOMBINE_DOTTED_VERSION[\t ]+\".*\"")

string(REGEX REPLACE "^#define[\t ]+LIBCOMBINE_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
COMBINE_VERSION "${combine_version_str}")
unset(combine_version_str)

endif()


# set static on the library on windows
if ((WIN32 AND NOT CYGWIN) AND COMBINE_FOUND AND COMBINE_LIBRARY MATCHES "static")
  set_target_properties(${COMBINE_LIBRARY_NAME} PROPERTIES 
  INTERFACE_COMPILE_DEFINITIONS "LIBCOMBINE_STATIC=1"
)

endif()


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBCOMBINE 
VERSION_VAR COMBINE_VERSION
REQUIRED_VARS COMBINE_LIBRARY COMBINE_INCLUDE_DIR)

mark_as_advanced(COMBINE_VERSION)
