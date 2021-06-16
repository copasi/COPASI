# Copyright (C) 2021 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# BEGIN: Copyright 
# END: Copyright 

# BEGIN: License 
# Licensed under the Artistic License 2.0 (the "License"); 
# you may not use this file except in compliance with the License. 
# You may obtain a copy of the License at 
#   https://opensource.org/licenses/Artistic-2.0 
# END: License 

project (TESTS VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

set(TEST_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

include_directories(BEFORE ${CMAKE_BINARY_DIR})

if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
add_executable(test_api ${TEST_FILES})
set_target_properties(test_api PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_link_libraries(test_api libCOPASISE-static)
add_test(NAME test_api_run COMMAND "$<TARGET_FILE:test_api>")
set_tests_properties(test_api_run PROPERTIES ENVIRONMENT 
	"srcdir=${CMAKE_CURRENT_SOURCE_DIR}")
