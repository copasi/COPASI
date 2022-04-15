# Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Locate library providing nativejit
# This module defines:
# NATIVEJIT_INCLUDE_DIR, where to find the headers
#
# NATIVEJIT, NATIVEJIT_DEBUG
# NATIVEJIT_FOUND
#
# $NATIVEJIT_DIR is an environment variable that would
# correspond to the ./configure --prefix=$NATIVEJIT_DIR

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

find_package(NATIVEJIT CONFIG REQUIRED
  CONFIGS nativejit-config.cmake
  PATHS $ENV{NATIVEJIT_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}/cmake
        ${${_PROJECT_DEPENDENCY_DIR}}/lib/cmake
        /usr/${CMAKE_INSTALL_LIBDIR}/cmake
        ${CONAN_LIB_DIRS_NATIVEJIT}/cmake
  )

if (NOT NATIVEJIT_FOUND)
  message(VERBOSE "NativeJIT Fallback $ENV{NATIVEJIT_DIR}/${CMAKE_INSTALL_LIBDIR}/cmake")
  # Fallback if no CONFIG is found

  find_path(NATIVEJIT_INCLUDE_DIR NativeJIT/ExpressionTree.h
    PATHS $ENV{NATIVEJIT_DIR}/include
          $ENV{NATIVEJIT_DIR}
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

  if (NOT NATIVEJIT_INCLUDE_DIR)
    find_path(NATIVEJIT_INCLUDE_DIR NativeJIT/ExpressionTree.h)
  endif (NOT NATIVEJIT_INCLUDE_DIR)

  find_library(NATIVEJIT_LIBRARY 
    NAMES NativeJIT
    PATHS $ENV{NATIVEJIT_DIR}/lib
          $ENV{NATIVEJIT_DIR}
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
          ${CONAN_LIB_DIRS_NATIVEJIT}
    NO_DEFAULT_PATH)
    
  if (NOT NATIVEJIT_LIBRARY)
    find_library(NATIVEJIT_LIBRARY 
        NAMES NativeJIT)
  endif (NOT NATIVEJIT_LIBRARY)
  
  set(NATIVEJIT_FOUND ${NATIVEJIT_LIBRARY})

  if (NATIVEJIT_FOUND)
    find_library(CODEGEN_LIBRARY 
      NAMES CodeGen
      PATHS $ENV{NATIVEJIT_DIR}/lib
            $ENV{NATIVEJIT_DIR}
            ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
            ${${_PROJECT_DEPENDENCY_DIR}}/lib
            ${${_PROJECT_DEPENDENCY_DIR}}
            ~/Library/Frameworks
            /Library/Frameworks
            /sw/lib         Fink
            /opt/local/lib  MacPorts
            /opt/csw/lib    Blastwave
            /opt/lib
            /usr/freeware/lib64
            ${CONAN_LIB_DIRS_NATIVEJIT}
      NO_DEFAULT_PATH)
      
    if (NOT CODEGEN_LIBRARY)
      find_library(CODEGEN_LIBRARY 
          NAMES CodeGen)
    endif (NOT CODEGEN_LIBRARY)
    
    if (CODEGEN_LIBRARY)
      set(NATIVEJIT_LIBRARY ${NATIVEJIT_LIBRARY} ${CODEGEN_LIBRARY})
      set(NATIVEJIT_COMPILE_OPTIONS "-msse4")
    else (CODEGEN_LIBRARY)
      set(NATIVEJIT_FOUND ${CODEGEN_LIBRARY})
    endif (CODEGEN_LIBRARY)
  endif (NATIVEJIT_FOUND)

else ()

  get_target_property(NATIVEJIT_INCLUDE_DIR NativeJIT INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(NATIVEJIT_COMPILE_OPTIONS NativeJIT INTERFACE_COMPILE_OPTIONS)

  get_target_property(NATIVEJIT_LIBRARY NativeJIT IMPORTED_LOCATION_RELEASE)
  
  if (NOT NATIVEJIT_LIBRARY)
    get_target_property(NATIVEJIT_LIBRARY NativeJIT IMPORTED_LOCATION_DEBUG)
  endif()

  if (NOT NATIVEJIT_LIBRARY)
    get_target_property(NATIVEJIT_LIBRARY NativeJIT IMPORTED_LOCATION_NOCONFIG)
  endif()

  get_target_property(NATIVEJIT_INTERFACE_LINK_LIBRARIES NativeJIT INTERFACE_LINK_LIBRARIES)
  
  if (NATIVEJIT_INTERFACE_LINK_LIBRARIES)
    set(NATIVEJIT_LIBRARY ${NATIVEJIT_LIBRARY} ${NATIVEJIT_INTERFACE_LINK_LIBRARIES})
  endif (NATIVEJIT_INTERFACE_LINK_LIBRARIES)

  get_target_property(CODEGEN_LIBRARY CodeGen IMPORTED_LOCATION_RELEASE)
  
  if (NOT CODEGEN_LIBRARY)
    get_target_property(CODEGEN_LIBRARY CodeGen IMPORTED_LOCATION_DEBUG)
  endif()

  if (NOT CODEGEN_LIBRARY)
    get_target_property(CODEGEN_LIBRARY CodeGen IMPORTED_LOCATION_NOCONFIG)
  endif()  

  if (CODEGEN_LIBRARY)
    set(NATIVEJIT_LIBRARY ${NATIVEJIT_LIBRARY} ${CODEGEN_LIBRARY})
  endif (CODEGEN_LIBRARY)

  get_target_property(CODEGEN_INTERFACE_LINK_LIBRARIES CodeGen INTERFACE_LINK_LIBRARIES)

  if (CODEGEN_INTERFACE_LINK_LIBRARIES)
    set(NATIVEJIT_LIBRARY ${NATIVEJIT_LIBRARY} ${CODEGEN_INTERFACE_LINK_LIBRARIES})
  endif (CODEGEN_INTERFACE_LINK_LIBRARIES)

endif()


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(NATIVEJIT REQUIRED NATIVEJIT_INCLUDE_DIR NATIVEJIT_LIBRARY)

mark_as_advanced(NATIVEJIT_INCLUDE_DIR NATIVEJIT_LIBRARY)

