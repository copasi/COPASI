# Try to find the Systems Biology Workbench (SBW) library
# Once done this will define
#
#  SBW_FOUND - system has BZip2
#  SBW_INCLUDE_DIR - the BZip2 include directory
#  SBW_LIBRARIES - Link these to use BZip2

find_path(SBW_INCLUDE_DIR SBW/SBW.h
    $ENV{SBW_DIR}/include
    $ENV{SBW_DIR}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include/
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    /usr/freeware/include
)

find_library(SBW_LIBRARIES
    NAMES SBW 
          SBW-static 
          sbw 
          libSBW 
          libsbw
    PATHS $ENV{SBW_DIR}/lib
          $ENV{SBW_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          /sw/lib # Fink
          /opt/local/lib # DarwinPorts
          /opt/csw/lib # Blastwave
          /opt/lib
          /usr/freeware/lib64
    NO_DEFAULT_PATH
)

# handle the QUIETLY and REQUIRED arguments and set SBW_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SBW DEFAULT_MSG SBW_LIBRARIES SBW_INCLUDE_DIR)

mark_as_advanced(SBW_INCLUDE_DIR SBW_LIBRARIES)

set(SBW_FOUND "NO")

if(SBW_LIBRARIES AND SBW_INCLUDE_DIR)
        SET(SBW_FOUND "YES")
endif(SBW_LIBRARIES AND SBW_INCLUDE_DIR)