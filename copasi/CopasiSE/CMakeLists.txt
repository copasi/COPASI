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

###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################

find_package (Python COMPONENTS Interpreter)

set(COPSISE_SOURCES CopasiSE.cpp)

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
endif (BUILD_STATIC_COPASISE) 

add_executable(CopasiSE ${COPSISE_SOURCES})
target_link_libraries(CopasiSE libCOPASISE-static)

install(TARGETS CopasiSE DESTINATION bin)

if (PYTHONINTERP_FOUND)

# call python test script 
add_test(NAME CopasiTestsuite
         COMMAND ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Tools/RunTests.py "$<TARGET_FILE:CopasiSE>"  ${CMAKE_CURRENT_BINARY_DIR}/CURRENT_BUILD ${CMAKE_SOURCE_DIR}/COPASI_TestSuite/Tests
         
)
set_tests_properties(CopasiTestsuite PROPERTIES FAIL_REGULAR_EXPRESSION "ifferent")	
# reduce precision, as the test comparison code uses truncated data
set_tests_properties(CopasiTestsuite PROPERTIES ENVIRONMENT "ABSOLUTE_ERROR=1e-04;RELATIVE_ERROR=1e-04")	

endif()

