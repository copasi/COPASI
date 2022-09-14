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

###############################################################################
#
# Description       : CMake build script for COPASI C# bindings
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

include(${SWIG_USE_FILE})
include (CheckTypeSize)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/AssemblyInfo.cs"
  "${CMAKE_CURRENT_BINARY_DIR}/AssemblyInfo.cs"
  )


find_program(CSHARP_COMPILER
        NAMES gmcs csc mcs
        PATHS $ENV{CSHARP_DIR}/bin
              /Library/Frameworks/Mono.framework/Commands/
              C:/Windows/Microsoft.NET/Framework/v2.0.50727/ 
              /usr/bin 
              /usr/local/bin
        DOC "The file name of the C# compiler."
        )

if (${CSHARP_COMPILER} STREQUAL CSHARP_COMPILER-NOTFOUND)
  message(FATAL_ERROR "No C# compiler found! 
  Please set the environment variable CSHARP_DIR to point 
  to the installation directory.")
else ()
  message(STATUS "Found C# Compiler:  ${CSHARP_COMPILER}")
endif()

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

if (ENABLE_JIT)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DUSE_JIT=1)
endif()

file(GLOB SWIG_DEPENDENCIES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.i 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.i
	${CMAKE_CURRENT_SOURCE_DIR}/../swig/*.h
)

make_directory(${CMAKE_CURRENT_BINARY_DIR}/csharp-files)
add_custom_command(	
    OUTPUT 	${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
	${CMAKE_CURRENT_BINARY_DIR}/csharp-files
	${CMAKE_CURRENT_BINARY_DIR}/csharp-files/COPASI.cs 
    COMMAND "${CMAKE_COMMAND}"
    ARGS  -E remove_directory "${COPASI_CS_FILES}"
    COMMAND "${CMAKE_COMMAND}"
    ARGS  -E make_directory "${COPASI_CS_FILES}"
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
         -I${CMAKE_CURRENT_SOURCE_DIR}/../../
         -I${CMAKE_CURRENT_SOURCE_DIR}
         -I${CMAKE_SOURCE_DIR}
         -c++
         -csharp
         -namespace org.COPASI
         -DSWIG_CSHARP_NO_IMCLASS_STATIC_CONSTRUCTOR
         -DLIBSBML_CPP_NAMESPACE_USE=
         -DLIBSBML_CPP_NAMESPACE_BEGIN=
         -DLIBSBML_CPP_NAMESPACE_END=
         -DLIBSEDML_CPP_NAMESPACE_USE=
         -DLIBSEDML_CPP_NAMESPACE_BEGIN=
         -DLIBSEDML_CPP_NAMESPACE_END=
         -DLIBSEDML_CPP_NAMESPACE_QUALIFIER=
         -DLIBCOMBINE_CPP_NAMESPACE_USE=
         -DLIBCOMBINE_CPP_NAMESPACE_BEGIN=
         -DLIBCOMBINE_CPP_NAMESPACE_END=
         -DLIBCOMBINE_CPP_NAMESPACE_QUALIFIER=
         -dllimport copasics ${SWIG_EXTRA_ARGS}
         ${SWIG_EXTRA_FLAGS}		 
         -outdir ${COPASI_CS_FILES}     
         -o ${COPASI_NATIVE_WRAPPER}
         ${CMAKE_CURRENT_SOURCE_DIR}/csharp.i
         
    COMMAND "${CMAKE_COMMAND}"
    ARGS -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
         -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
         -P "${CMAKE_CURRENT_SOURCE_DIR}/../common/patch-wrapper.cmake"

    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/csharp.i 
    DEPENDS ${SWIG_DEPENDENCIES}
    COMMENT "Swig C# source") 

add_custom_target(binding_csharp_swig DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/csharp.i
    ${CMAKE_CURRENT_SOURCE_DIR}/../swig/copasi.i)

	
####################################################################
#
# Build native library
# 

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(binding_csharp_native_lib SHARED ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp) 
add_dependencies(binding_csharp_native_lib binding_csharp_swig)

set_target_properties (binding_csharp_native_lib PROPERTIES OUTPUT_NAME "copasics")

target_link_libraries(binding_csharp_native_lib libCOPASISE-static)

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
	        ${CMAKE_CURRENT_BINARY_DIR}/csharp-files/COPASI.cs
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


