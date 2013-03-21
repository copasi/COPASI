# Locate libraptor
# This module defines:
# RAPTOR_INCLUDE_DIR, where to find the headers
#
# RAPTOR_LIBRARY, RAPTOR_LIBRARY_DEBUG
# RAPTOR_FOUND
#
# $RAPTOR_DIR is an environment variable that would
# correspond to the ./configure --prefix=$RAPTOR_DIR
#
# Created by Robert Osfield.
# Modified by Ralph Gauges

find_path(RAPTOR_INCLUDE_DIR raptor.h
    PATHS $ENV{RAPTOR_DIR}/include
          $ENV{RAPTOR_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include/
          /sw/include        # Fink
          /opt/local/include # MacPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
)


find_library(RAPTOR_LIBRARY 
    NAMES raptor 
    PATHS $ENV{RAPTOR_DIR}/lib
          $ENV{RAPTOR_DIR}/lib-dbg
          $ENV{RAPTOR_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          /sw/lib        # Fink
          /opt/local/lib # MacPorts
          /opt/csw/lib   # Blastwave
          /opt/lib
          /usr/freeware/lib64
)

if (NOT RAPTOR_INCLUDE_DIR)
message(FATAL_ERROR "raptor.h not found!")
endif (NOT RAPTOR_INCLUDE_DIR)


if (NOT RAPTOR_LIBRARY)
message(FATAL_ERROR "RAPTOR library not found!")
endif (NOT RAPTOR_LIBRARY)


set(RAPTOR_FOUND "NO")
if(RAPTOR_LIBRARY)
    if (RAPTOR_INCLUDE_DIR)
        set(RAPTOR_FOUND "YES")
    endif(RAPTOR_INCLUDE_DIR)
endif(RAPTOR_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set RAPTOR_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RAPTOR DEFAULT_MSG RAPTOR_LIBRARY RAPTOR_INCLUDE_DIR)

mark_as_advanced(RAPTOR_INCLUDE_DIR RAPTOR_LIBRARY)
