# Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Locate libsbml
# This module defines:
# LIBSBML_INCLUDE_DIR, where to find the headers
#
# LIBSBML_LIBRARY, LIBSBML_LIBRARY_DEBUG
# LIBSBML_FOUND, LIBSBML_LIBRARY_NAME


if(UNIX OR CYGWIN OR MINGW)
  set(LIBSBML_LIBRARY_NAME sbml)
else()
  set(LIBSBML_LIBRARY_NAME libsbml)
endif()

if (NOT LIBSBML_SHARED)
  set(LIBSBML_LIBRARY_NAME "${LIBSBML_LIBRARY_NAME}-static")
endif()

message (VERBOSE "Looking for ${LIBSBML_LIBRARY_NAME}")


string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

find_package(${LIBSBML_LIBRARY_NAME} CONFIG QUIET
  PATHS ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib64/cmake
        ${CONAN_LIB_DIRS_LIBSBML}/cmake
        CMAKE_FIND_ROOT_PATH_BOTH
        NO_DEFAULT_PATH)

if (NOT ${LIBSBML_LIBRARY_NAME}_FOUND)        
  find_package(${LIBSBML_LIBRARY_NAME} CONFIG QUIET)
endif()

if (NOT ${LIBSBML_LIBRARY_NAME}_FOUND)
  find_package(${LIBSBML_LIBRARY_NAME} CONFIG QUIET
    PATHS /usr/lib/cmake
          /usr/local/lib/cmake
          /opt/lib/cmake
          /opt/local/lib/cmake
          /sw/lib/cmake
          ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
          ${${_PROJECT_DEPENDENCY_DIR}}/lib64/cmake
          ${CONAN_LIB_DIRS_LIBSBML}/cmake
          CMAKE_FIND_ROOT_PATH_BOTH
  )
endif()

if (${LIBSBML_LIBRARY_NAME}_FOUND)

  get_target_property(LIBSBML_LIBRARY ${LIBSBML_LIBRARY_NAME} LOCATION)
  get_target_property(LIBSBML_INCLUDE_DIR ${LIBSBML_LIBRARY_NAME} INTERFACE_INCLUDE_DIRECTORIES)
  if (NOT LIBSBML_INCLUDE_DIR)
    get_filename_component(LIB_PATH ${LIBSBML_LIBRARY} DIRECTORY)
    file(TO_CMAKE_PATH ${LIB_PATH}/../include LIBSBML_INCLUDE_DIR)  
    get_filename_component (LIBSBML_INCLUDE_DIR ${LIBSBML_INCLUDE_DIR} REALPATH)
  endif()
  get_target_property(LIBSBML_VERSION ${LIBSBML_LIBRARY_NAME} VERSION)


  get_target_property(LIBSBML_INTERFACE_LINK_LIBRARIES ${LIBSBML_LIBRARY_NAME} INTERFACE_LINK_LIBRARIES)

  if (NOT LIBSBML_INTERFACE_LINK_LIBRARIES)
  get_target_property(LIBSBML_INTERFACE_LINK_LIBRARIES ${LIBSBML_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE)
  endif()

  if (NOT LIBSBML_INTERFACE_LINK_LIBRARIES)
  get_target_property(LIBSBML_INTERFACE_LINK_LIBRARIES ${LIBSBML_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG)
  endif()

  if (NOT LIBSBML_INTERFACE_LINK_LIBRARIES)
  get_target_property(LIBSBML_INTERFACE_LINK_LIBRARIES ${LIBSBML_LIBRARY_NAME} IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG)
  endif()

  if (LIBSBML_INTERFACE_LINK_LIBRARIES)
    set(LIBSBML_LIBRARY ${LIBSBML_LIBRARY} ${LIBSBML_INTERFACE_LINK_LIBRARIES})
  endif (LIBSBML_INTERFACE_LINK_LIBRARIES)

  
  foreach (library ${LIBSBML_INTERFACE_LINK_LIBRARIES})
  
    string(FIND "${library}" "::" index)

    if (${index} GREATER 0)
      # found dependent library
      string(SUBSTRING "${library}" 0 ${index} DEPENDENT_NAME)
      message(VERBOSE "Looking for dependent library: ${DEPENDENT_NAME}")
      find_package(${DEPENDENT_NAME})
    endif()
  
  endforeach()
  
  

else()

find_path(LIBSBML_INCLUDE_DIR sbml/SBase.h
    PATHS $ENV{LIBSBML_DIR}/include
          $ENV{LIBSBML_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}
          ${${_PROJECT_DEPENDENCY_DIR}}/include
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
          CMAKE_FIND_ROOT_PATH_BOTH
    NO_DEFAULT_PATH)

if (NOT LIBSBML_INCLUDE_DIR)
    find_path(LIBSBML_INCLUDE_DIR sbml/SBase.h)
endif (NOT LIBSBML_INCLUDE_DIR)


if (NOT LIBSBML_INCLUDE_DIR)
    message(FATAL_ERROR "libsbml include dir not found not found!")
endif (NOT LIBSBML_INCLUDE_DIR)


find_library(LIBSBML_LIBRARY 
    NAMES sbml-static 
          sbml
          libsbml-static 
          libsbml
    PATHS $ENV{LIBSBML_DIR}/lib
          $ENV{LIBSBML_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
          ${CONAN_LIB_DIRS_LIBSBML}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
          CMAKE_FIND_ROOT_PATH_BOTH
    NO_DEFAULT_PATH)

if (NOT LIBSBML_LIBRARY)
    find_library(LIBSBML_LIBRARY 
        NAMES sbml-static 
              sbml)
endif (NOT LIBSBML_LIBRARY)

if (NOT LIBSBML_LIBRARY)
    message(FATAL_ERROR "LIBSBML library not found!")
endif (NOT LIBSBML_LIBRARY)

add_library(${LIBSBML_LIBRARY_NAME} UNKNOWN IMPORTED)
set_target_properties(${LIBSBML_LIBRARY_NAME} 
  PROPERTIES
    IMPORTED_LOCATION ${LIBSBML_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${LIBSBML_INCLUDE_DIR}
)

endif()

if (LIBSBML_INCLUDE_DIR AND EXISTS "${LIBSBML_INCLUDE_DIR}/sbml/common/libsbml-version.h")

file(STRINGS "${LIBSBML_INCLUDE_DIR}/sbml/common/libsbml-version.h" sbml_version_str
REGEX "^#define[\t ]+LIBSBML_DOTTED_VERSION[\t ]+\".*\"")

string(REGEX REPLACE "^#define[\t ]+LIBSBML_DOTTED_VERSION[\t ]+\"([^\"]*)\".*" "\\1"
LIBSBML_VERSION "${sbml_version_str}")
unset(sbml_version_str)


endif()


set(LIBSBML_FOUND "NO")
if(LIBSBML_LIBRARY)
    if (LIBSBML_INCLUDE_DIR)
        SET(LIBSBML_FOUND "YES")
    endif(LIBSBML_INCLUDE_DIR)
endif(LIBSBML_LIBRARY)

# set static on the library on windows
if ((WIN32 AND NOT CYGWIN) AND LIBSBML_FOUND AND LIBSBML_LIBRARY MATCHES "static")
  set_target_properties(${LIBSBML_LIBRARY_NAME} PROPERTIES 
  INTERFACE_COMPILE_DEFINITIONS "LIBSBML_STATIC=1;LIBLAX_STATIC=1;LIBSBML_EXPORTS;LIBLAX_EXPORTS"
)

endif()

# handle the QUIETLY and REQUIRED arguments and set LIBSBML_FOUND to TRUE if 
# all listed variables are TRUE

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBSBML 
  VERSION_VAR LIBSBML_VERSION
  REQUIRED_VARS LIBSBML_LIBRARY_NAME LIBSBML_LIBRARY LIBSBML_INCLUDE_DIR)

mark_as_advanced(LIBSBML_INCLUDE_DIR LIBSBML_LIBRARY LIBSBML_LIBRARY_NAME)
