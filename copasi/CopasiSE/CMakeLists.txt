###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., University of Heidelberg, and The University
# of Manchester.
# All rights reserved.
# 
# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.
# 
# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.
#
###############################################################################


set(COPSISE_SOURCES CopasiSE.cpp)

include(../CMakeConsoleApp.cmake)

if (BUILD_STATIC_COPASISE) 
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static") 
    # set(CMAKE_FIND_LIBRARY_SUFFIXES .a) 
    set(CMAKE_EXE_LINK_DYNAMIC_C_FLAGS)       # remove -Wl,-Bdynamic 
    set(CMAKE_EXE_LINK_DYNAMIC_CXX_FLAGS) 
    set(CMAKE_SHARED_LIBRARY_C_FLAGS)         # remove -fPIC 
    set(CMAKE_SHARED_LIBRARY_CXX_FLAGS) 
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)    # remove -rdynamic 
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS) 
    # Maybe this works as well, haven't tried yet. 
    # set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE) 
endif (BUILD_STATIC_EXECUTABLES) 

add_executable(CopasiSE ${COPSISE_SOURCES})
target_link_libraries(CopasiSE libCOPASI ${SE_EXTERNAL_LIBS} ${SE_LIBS})

install(TARGETS CopasiSE DESTINATION bin)
