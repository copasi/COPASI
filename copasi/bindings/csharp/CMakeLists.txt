###############################################################################
#
# Description       : CMake build script for COPASI C# bindings
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

find_package(SWIG REQUIRED)

include(${SWIG_USE_FILE})
include (CheckTypeSize)

find_program(CSHARP_COMPILER
        NAMES gmcs csc
        PATHS C:/Windows/Microsoft.NET/Framework/v2.0.50727/ /usr/bin /usr/local/bin
        DOC "The file name of the C# compiler."
        )
    if(UNIX)
    else()
	    if (CMAKE_SIZEOF_VOID_P)
        if(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
            # mark libsbml library as x86
            set(CSHARP_EXTRA_ARGS -platform:x86 )
        elseif(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
            # mark libsbml library as x64
            set(CSHARP_EXTRA_ARGS -platform:x64 )
        endif()
		endif()
    endif()

set(SWIG_EXTRA_FLAGS)

file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/csharp-files COPASI_CS_FILES)
file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp COPASI_NATIVE_WRAPPER)

####################################################################
#
# ensure that LAPACK variables are there for swig
# 
if (APPLE)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DDarwin)
endif(APPLE)

if (CLAPACK_FOUND)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_CLAPACK)
elseif (USE_MKL)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_MKL)
elseif(USE_ACML)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_ACML)
elseif(LAPACK_FOUND)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_LAPACK)
endif()

make_directory(${CMAKE_CURRENT_BINARY_DIR}/csharp-files)
add_custom_command(	
    OUTPUT 	${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
	${CMAKE_CURRENT_BINARY_DIR}/csharp-files
	${CMAKE_CURRENT_BINARY_DIR}/csharp-files/copasi.cs 
    COMMAND "${CMAKE_COMMAND}"
    ARGS  -E remove_directory "${COPASI_CS_FILES}"
    COMMAND "${CMAKE_COMMAND}"
    ARGS  -E make_directory "${COPASI_CS_FILES}"
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
	     -I${CMAKE_CURRENT_SOURCE_DIR}/../../
	     -I${CMAKE_CURRENT_SOURCE_DIR}
	     -c++
	     -csharp
	     -namespace org.COPASI
	     -DSWIG_CSHARP_NO_IMCLASS_STATIC_CONSTRUCTOR
	     -dllimport copasics ${SWIG_EXTRA_ARGS}
	     ${SWIG_EXTRA_FLAGS}		 
	     -outdir ${COPASI_CS_FILES}
	     -o ${COPASI_NATIVE_WRAPPER}
	     ${CMAKE_CURRENT_SOURCE_DIR}/csharp.i

    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/csharp.i 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../swig/copasi.i
	        ${CMAKE_CURRENT_SOURCE_DIR}/local.cpp
    COMMENT "Swig C# source") 

add_custom_target(binding_csharp_swig DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/csharp.i
    ${CMAKE_CURRENT_SOURCE_DIR}/../swig/copasi.i)

	
####################################################################
#
# Build native library
# 

include(../../common.cmake)
include(../../CMakeConsoleApp.cmake)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../swig)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(binding_csharp_native_lib SHARED ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp) 
add_dependencies(binding_csharp_native_lib binding_csharp_swig)
if (UNIX)
set_target_properties (binding_csharp_native_lib PROPERTIES OUTPUT_NAME "copasics")
else()
set_target_properties (binding_csharp_native_lib PROPERTIES OUTPUT_NAME "copasics")
endif()
target_link_libraries(binding_csharp_native_lib ${SE_EXTERNAL_LIBS} ${SE_LIBS} )

INSTALL(TARGETS binding_csharp_native_lib 
        DESTINATION bindings/csharp
  )

####################################################################
#
# build managed library
# 

ADD_CUSTOM_COMMAND(	
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/copasicsP.dll 
		
	COMMAND "${CMAKE_COMMAND}"
	ARGS -DCSHARP_EXTRA_ARGS=\"${CSHARP_EXTRA_ARGS}\"
	     -DCSHARP_COMPILER=\"${CSHARP_COMPILER}\"
	     -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
	     -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"		 
	     -P "${CMAKE_CURRENT_SOURCE_DIR}/compile-native-files.cmake"
		 
	MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/../swig/copasi.i"
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/compile-native-files.cmake
	        ${CMAKE_CURRENT_BINARY_DIR}/csharp-files/copasi.cs
	        ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMMENT "Build csharp files"
	) 

add_custom_target(binding_csharp_managed_lib ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/copasicsP.dll)
add_dependencies(binding_csharp_managed_lib binding_csharp_swig)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/copasicsP.dll DESTINATION bindings/csharp) 
file(GLOB examples ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cs)
INSTALL(FILES ${examples} DESTINATION bindings/csharp/examples) 

# compile cs examples if needed to test whether 
# they still work with the current objectmodel
option (BUILD_CS_EXAMPLES "Build the C# examples." OFF)
mark_as_advanced(BUILD_CS_EXAMPLES)
if (BUILD_CS_EXAMPLES)
add_subdirectory(examples)
endif(BUILD_CS_EXAMPLES)


