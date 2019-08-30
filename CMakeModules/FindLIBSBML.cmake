# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
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

if (EXISTS ${COPASI_BINARY_DIR}/Findlibsbml.cmake)
#find_package(libsbml QUIET)
include (${COPASI_BINARY_DIR}/Findlibsbml.cmake)
endif()

if (libsbml_FOUND AND NOT ${CMAKE_VERSION} VERSION_LESS "3.0")


  # provided by conan, so just copy information
  if (NOT TARGET ${LIBSBML_LIBRARY_NAME})
  add_library(${LIBSBML_LIBRARY_NAME} UNKNOWN IMPORTED)
  set_target_properties(${LIBSBML_LIBRARY_NAME} PROPERTIES IMPORTED_LOCATION ${libcombine_LIBS})
  get_target_property(tmp libsbml::libsbml INTERFACE_LINK_LIBRARIES)
  set_property(TARGET ${LIBSBML_LIBRARY_NAME} APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${tmp})
  get_target_property(tmp libsbml::libsbml INTERFACE_COMPILE_DEFINITIONS)
  set_property(TARGET ${LIBSBML_LIBRARY_NAME} APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS ${tmp})
  get_target_property(tmp libsbml::libsbml INTERFACE_INCLUDE_DIRECTORIES)
  set_property(TARGET ${LIBSBML_LIBRARY_NAME} APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${tmp})
  endif()
  
  set(LIBSBML_LIBRARY ${libsbml_LIBS})
  set(LIBSBML_INCLUDE_DIR ${libsbml_INCLUDE_DIRS})  
  set(LIBSBML_VERSION ${libsbml_VERSION})
  set(${LIBSBML_LIBRARY_NAME}_FOUND ON)
  message(STATUS "Found libSBML ${libsbml_VERSION}")

else()

message (STATUS "Looking for ${LIBSBML_LIBRARY_NAME}")

find_package(${LIBSBML_LIBRARY_NAME} CONFIG QUIET)

if (NOT ${LIBSBML_LIBRARY_NAME}_FOUND)
  find_package(${LIBSBML_LIBRARY_NAME} CONFIG QUIET
    PATHS /usr/lib/cmake
          /usr/local/lib/cmake
          /opt/lib/cmake
          /opt/local/lib/cmake
          /sw/lib/cmake
          ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
          ${CONAN_LIB_DIRS_LIBSBML}/cmake
  )
endif()

if (${LIBSBML_LIBRARY_NAME}_FOUND)

  get_target_property(LIBSBML_LIBRARY ${LIBSBML_LIBRARY_NAME} LOCATION)
  get_filename_component(LIB_PATH ${LIBSBML_LIBRARY} DIRECTORY)
  file(TO_CMAKE_PATH ${LIB_PATH}/../include LIBSBML_INCLUDE_DIR)  
  get_filename_component (LIBSBML_INCLUDE_DIR ${LIBSBML_INCLUDE_DIR} REALPATH)
  get_target_property(LIBSBML_VERSION ${LIBSBML_LIBRARY_NAME} VERSION)

else()

find_path(LIBSBML_INCLUDE_DIR sbml/SBase.h
    PATHS $ENV{LIBSBML_DIR}/include
          $ENV{LIBSBML_DIR}
          ${COPASI_DEPENDENCY_DIR}
          ${COPASI_DEPENDENCY_DIR}/include
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
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
          ${COPASI_DEPENDENCY_DIR}
          ${COPASI_DEPENDENCY_DIR}/${CMAKE_INSTALL_LIBDIR}
          ${COPASI_DEPENDENCY_DIR}/lib
          ${CONAN_LIB_DIRS_LIBSBML}
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

  add_library(${LIBSBML_LIBRARY_NAME} UNKNOWN IMPORTED)
  set_target_properties(${LIBSBML_LIBRARY_NAME} PROPERTIES IMPORTED_LOCATION ${LIBSBML_LIBRARY})

endif()
endif (libsbml_FOUND AND NOT ${CMAKE_VERSION} VERSION_LESS "3.0")


set(LIBSBML_FOUND "NO")
if(LIBSBML_LIBRARY)
    if (LIBSBML_INCLUDE_DIR)
        SET(LIBSBML_FOUND "YES")
    endif(LIBSBML_INCLUDE_DIR)
endif(LIBSBML_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set LIBSBML_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBSBML DEFAULT_MSG LIBSBML_LIBRARY_NAME LIBSBML_LIBRARY LIBSBML_INCLUDE_DIR)

mark_as_advanced(LIBSBML_INCLUDE_DIR LIBSBML_LIBRARY LIBSBML_LIBRARY_NAME)

