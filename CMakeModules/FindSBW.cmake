# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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

# Try to find the Systems Biology Workbench (SBW) library
# Once done this will define
#
#  SBW_FOUND - system has BZip2
#  SBW_INCLUDE_DIR - the BZip2 include directory
#  SBW_LIBRARY - Link these to use BZip2

find_path(SBW_INCLUDE_DIR SBW/SBW.h
    PATHS $ENV{SBW_DIR}/include
          $ENV{SBW_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
    NO_DEFAULT_PATH)

if (NOT SBW_INCLUDE_DIR)
    find_path(SBW_INCLUDE_DIR SBW/SBW.h)
endif ()

find_library(SBW_LIBRARY
    NAMES SBW-static
          SBW
          sbw 
          libSBW 
          libsbw
    PATHS $ENV{SBW_DIR}/${CMAKE_INSTALL_LIBDIR}
          $ENV{SBW_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH)

if (NOT SBW_LIBRARY)
    find_library(SBW_LIBRARY
        NAMES SBW-static
              SBW
              sbw 
              libSBW 
              libsbw)
endif ()

if(NOT TARGET SBW::SBW)
  add_library(SBW::SBW UNKNOWN IMPORTED)
  set_target_properties(SBW::SBW PROPERTIES
    IMPORTED_LOCATION "${SBW_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${SBW_INCLUDE_DIR}")
endif()

if (WIN32)
    set_target_properties(SBW::SBW PROPERTIES
    INTERFACE_COMPILE_DEFINITIONS "WIN32"
    INTERFACE_LINK_LIBRARIES "ws2_32.lib"
  )
endif (WIN32)

if (SBW_LIBRARY AND SBW_LIBRARY MATCHES "static")
  get_target_property(current_defs SBW::SBW INTERFACE_COMPILE_DEFINITIONS)

  if (NOT current_defs)
    set_target_properties(SBW::SBW PROPERTIES
      INTERFACE_COMPILE_DEFINITIONS "SBW_STATIC=1"
    )
  else ()
    set_target_properties(SBW::SBW PROPERTIES
      INTERFACE_COMPILE_DEFINITIONS ${current_defs}
    )
  endif ()
endif ()

if (SBW_INCLUDE_DIR AND SBW_LIBRARY)
    set(TEST_FILE ${CMAKE_BINARY_DIR}/test_sbw_version.cpp)
    file(WRITE ${TEST_FILE} "
    #include <stdio.h>
    #include <SBW/SBW.h>
    #include <SBW/SBWC.h>
    
    int main()
    {
      printf(SBWGetVersion());
      return 0;
    }
    
    ")
    
    try_run(
      SBW_VERSIONTEST_EXITCODE
      SBW_VERSIONTEST_COMPILE
      ${CMAKE_BINARY_DIR}
      ${TEST_FILE}
      LINK_LIBRARIES SBW::SBW
      RUN_OUTPUT_VARIABLE SBW_VERSION
      COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT
    )

endif()

# handle the QUIETLY and REQUIRED arguments and set SBW_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SBW 
  VERSION_VAR SBW_VERSION
  REQUIRED_VARS SBW_LIBRARY SBW_INCLUDE_DIR)

mark_as_advanced(SBW_INCLUDE_DIR SBW_LIBRARY)

set(SBW_FOUND "NO")

if(SBW_LIBRARY AND SBW_INCLUDE_DIR)
        SET(SBW_FOUND "YES")
endif(SBW_LIBRARY AND SBW_INCLUDE_DIR)
