# Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Locate library providing nativejit
# This module defines:
# CPUFEATURES_INCLUDE_DIR, where to find the headers
#
# CPUFEATURES, CPUFEATURES_DEBUG
# CPUFEATURES_FOUND
#
# $CPUFEATURES_DIR is an environment variable that would
# correspond to the ./configure --prefix=$CPUFEATURES_DIR

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

find_package(CPUFEATURES CONFIG REQUIRED
  CONFIGS CpuFeaturesConfig.cmake
  PATHS $ENV{CPUFEATURES_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
        ${CONAN_LIB_DIRS_CPUFEATURES}/cmake
  PATH_SUFFIXES CpuFeatures
)

if (NOT CPUFEATURES_FOUND)
  message(VERBOSE "cpu_features Fallback $ENV{CPUFEATURES_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake")
  # Fallback if no CONFIG is found

  find_path(CPUFEATURES_INCLUDE_DIR cpu_features/cpuinfo_x86.h
    PATHS $ENV{CPUFEATURES_DIR}/include
          $ENV{CPUFEATURES_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/include
          ${${_PROJECT_DEPENDENCY_DIR}}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    NO_DEFAULT_PATH)

  if (NOT CPUFEATURES_INCLUDE_DIR)
    find_path(CPUFEATURES_INCLUDE_DIR cpu_features/cpuinfo_x86.h)
  endif (NOT CPUFEATURES_INCLUDE_DIR)

  find_library(CPUFEATURES_LIBRARY 
    NAMES cpu_features
    PATHS $ENV{CPUFEATURES_DIR}/lib
          $ENV{CPUFEATURES_DIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
          ${${_PROJECT_DEPENDENCY_DIR}}/lib
          ${${_PROJECT_DEPENDENCY_DIR}}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib         # Fink
          /opt/local/lib  # MacPorts
          /opt/csw/lib    # Blastwave
          /opt/lib
          /usr/freeware/lib64
          ${CONAN_LIB_DIRS_CPUFEATURES}
    NO_DEFAULT_PATH)
    
  if (NOT CPUFEATURES_LIBRARY)
    find_library(CPUFEATURES_LIBRARY 
        NAMES cpu_features)
  endif (NOT CPUFEATURES_LIBRARY)
  
  set(CPUFEATURES_FOUND ${CPUFEATURES_LIBRARY})

else ()

  get_target_property(CPUFEATURES_INCLUDE_DIR CpuFeatures::cpu_features INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(CPUFEATURES_COMPILE_OPTIONS CpuFeatures::cpu_features INTERFACE_COMPILE_OPTIONS)

  get_target_property(CPUFEATURES_LIBRARY CpuFeatures::cpu_features IMPORTED_LOCATION_RELEASE)
  
  if (NOT CPUFEATURES_LIBRARY)
    get_target_property(CPUFEATURES_LIBRARY CpuFeatures::cpu_features IMPORTED_LOCATION_DEBUG)
  endif()

  if (NOT CPUFEATURES_LIBRARY)
    get_target_property(CPUFEATURES_LIBRARY CpuFeatures::cpu_features IMPORTED_LOCATION_NOCONFIG)
  endif()

  get_target_property(CPUFEATURES_INTERFACE_LINK_LIBRARIES CpuFeatures::cpu_features INTERFACE_LINK_LIBRARIES)
  
  if (CPUFEATURES_INTERFACE_LINK_LIBRARIES)
    set(CPUFEATURES_LIBRARY ${CPUFEATURES_LIBRARY} ${CPUFEATURES_INTERFACE_LINK_LIBRARIES})
  endif (CPUFEATURES_INTERFACE_LINK_LIBRARIES)
endif()


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPUFEATURES REQUIRED CPUFEATURES_INCLUDE_DIR CPUFEATURES_LIBRARY)

mark_as_advanced(CPUFEATURES_INCLUDE_DIR CPUFEATURES_LIBRARY)

