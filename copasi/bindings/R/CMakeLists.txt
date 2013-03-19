###############################################################################
#
# Description       : CMake build script for COPASI R bindings
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


SET(R_INCLUDE_DIRS)
SET(R_LIB)
SET(R_INTERPRETER)
SET(R_ADITIONAL_PATH_ENTRIES "" CACHE STRING "Additional paths to the RTOOLS / GCC binary directories to build package")
SET(CMAKE_FIND_FRAMEWORK NEVER)
# first lets search for the include/lib/interpreter if a user did not specify them
if (NOT R_INCLUDE_DIRS)
    find_path(R_INCLUDE_DIRS
        NAMES R.h
        PATHS /usr/include /usr/local/include /usr/share/R/include
		      /Library/Frameworks/R.framework/Versions/Current/Resources/include
			  $ENV{ProgramFiles}/R/R-2.15.1/include
			  $ENV{ProgramW6432}/R/R-2.15.1/include
              ${CMAKE_SOURCE_DIR}/include
              ${LIBSBML_DEPENDENCY_DIR}/include
        DOC "The directory containing the R include files."
        )
endif()
if (NOT R_LIB)
    SET(R_SUFFIX)
	if (WIN32)
		if (COPASI_BUILD_TYPE STREQUAL "32bit")
		SET(R_SUFFIX "/i386")
		else()
		SET(R_SUFFIX "/x64")
		endif()
	endif()
	find_library(R_LIB
			NAMES Rlib.lib R
			PATHS /usr/lib /usr/local/lib /usr/lib/R/lib
			    $ENV{ProgramFiles}/R/R-2.15.1/bin${R_SUFFIX}
			    $ENV{ProgramW6432}/R/R-2.15.1/bin${R_SUFFIX}
				  /Library/Frameworks/R.framework/Versions/Current/Resources/lib
          ${CMAKE_SOURCE_DIR}
				  ${LIBSBML_DEPENDENCY_DIR}/lib
			DOC "The file name of the R library."
			)
endif()
if (NOT R_INTERPRETER)
	find_program(R_INTERPRETER
        NAMES R
        PATHS 
		      $ENV{ProgramFiles}/R/R-2.15.1/bin
		      $ENV{ProgramW6432}/R/R-2.15.1/bin
			  /Library/Frameworks/R.framework/Versions/Current/Resources/R
              /usr/local/bin
              /usr/bin
        DOC "The file name of the R interpreter."
        )
endif()

# message(
# "
#              R_INCLUDE_DIRS = ${R_INCLUDE_DIRS}
#                       R_LIB = ${R_LIB}
#               R_INTERPRETER = ${R_INTERPRETER}
#    R_ADITIONAL_PATH_ENTRIES = ${R_ADITIONAL_PATH_ENTRIES}
# 
# ")

# if we have not found something, stop here to ask for it
if (NOT R_INTERPRETER)
	message(FATAL_ERROR "Need the R interpreter in order to create an R package") 
endif()
if (NOT R_LIB)
	message(FATAL_ERROR "Need the R library, please specify R_LIB")
endif()
if (NOT R_INCLUDE_DIRS)
	message(FATAL_ERROR "Need the R include directory, please specify R_INCLUDE_DIRS")
endif()


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


ADD_CUSTOM_COMMAND(	
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp
		   ${CMAKE_CURRENT_BINARY_DIR}/COPASI.R
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS	-I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
	        -I${CMAKE_CURRENT_SOURCE_DIR}/../../
            -I${CMAKE_CURRENT_SOURCE_DIR}
			-c++
			-r		
			${SWIG_EXTRA_ARGS}		 
			-o ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/R.i
	COMMAND "${CMAKE_COMMAND}"
	        -DSRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}
			-DFILENAME=\"${CMAKE_CURRENT_BINARY_DIR}/COPASI.R\"
			-P "${CMAKE_CURRENT_SOURCE_DIR}/patch-swig-file.cmake"
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/R.i
	DEPENDS ${SWIG_DEPENDENCIES}
    COMMENT "Swig R source") 

add_custom_target(binding_r_swig ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp)

	
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
include_directories(${R_INCLUDE_DIRS})


if (WIN32)
if (MSVC OR USING_INTEL)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC OR USING_INTEL)
endif(WIN32)

add_library(binding_r_lib SHARED copasi_wrapper.cpp)
add_dependencies( binding_r_lib binding_python_swig) 

set_target_properties (binding_r_lib PROPERTIES OUTPUT_NAME "COPASI")
if (UNIX)
	set_target_properties (binding_r_lib PROPERTIES PREFIX "")
	set_target_properties (binding_r_lib PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(binding_r_lib ${SE_EXTERNAL_LIBS} ${SE_LIBS}   ${R_LIB})
