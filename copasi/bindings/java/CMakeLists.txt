###############################################################################
#
# Description       : CMake build script for COASI Java bindings
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
find_package(JNI)
find_package(Java COMPONENTS Development REQUIRED)
include(${SWIG_USE_FILE})


####################################################################
#
# ensure that javac and jar are available
# 

if (NOT EXISTS "${Java_JAVAC_EXECUTABLE}")
	if (NOT EXISTS "${JAVA_COMPILE}")
		message(FATAL_ERROR "The java language bindings require Java_JAVAC_EXECUTABLE to be set to the javac command.")
	else()
		SET(Java_JAVAC_EXECUTABLE "${JAVA_COMPILE}" CACHE STRING "Javac compiler" FORCE)
	endif()
endif()


if (NOT EXISTS "${Java_JAR_EXECUTABLE}")
	if (NOT EXISTS "${JAVA_ARCHIVE}")	
		message(FATAL_ERROR "The java language bindings require Java_JAR_EXECUTABLE to be set to the jar command.")
	else()
        set (Java_JAR_EXECUTABLE "${JAVA_ARCHIVE}" CACHE STRING "jar command" FORCE)
	endif()
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

if (ENABLE_COPASI_CROSSVALIDATION)
set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DCOPASI_CROSSVALIDATION)
endif(ENABLE_COPASI_CROSSVALIDATION)


####################################################################
#
# Swig bindings
#
#
add_custom_command(	
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 	       
         ${CMAKE_CURRENT_BINARY_DIR}/java-files
         ${CMAKE_CURRENT_BINARY_DIR}/gui
         ${CMAKE_CURRENT_BINARY_DIR}/java-files/org/COPASI/COPASIJNI.java
    COMMAND "${CMAKE_COMMAND}"
    ARGS    -E make_directory  ${CMAKE_CURRENT_BINARY_DIR}/java-files/org/COPASI
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
         -I${CMAKE_CURRENT_SOURCE_DIR}/../../
         -I${CMAKE_CURRENT_SOURCE_DIR}
         -I${CMAKE_SOURCE_DIR}
         -I${LIBSBML_INCLUDE_DIR}
         -c++
         -java
         -package org.COPASI
         ${SWIG_EXTRA_ARGS}
         -outdir ${CMAKE_CURRENT_BINARY_DIR}/java-files/org/COPASI
         -o ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
         ${CMAKE_CURRENT_SOURCE_DIR}/java.i
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/java.i
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
         ${SWIG_DEPENDENCIES}
    COMMENT "Swig Java source") 
	
add_custom_target(binding_java_swig DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/java.i)

	
include(../../common.cmake)
include(../../CMakeConsoleApp.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../swig)
include_directories(${CMAKE_SOURCE_DIR}/include)

# if additional directories are set be sure to include them
if (JNI_INCLUDE_DIRS)
include_directories(${JNI_INCLUDE_DIRS})
endif(JNI_INCLUDE_DIRS)
if (JAVA_INCLUDE_PATH)
include_directories(${JAVA_INCLUDE_PATH})
endif(JAVA_INCLUDE_PATH)
if (JAVA_INCLUDE_PATH2)
include_directories(${JAVA_INCLUDE_PATH2})
endif(JAVA_INCLUDE_PATH2)


add_library(binding_java_lib SHARED ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp )
add_dependencies( binding_java_lib binding_java_swig) 
set_target_properties (binding_java_lib PROPERTIES OUTPUT_NAME "CopasiJava")


if(APPLE)
	set_target_properties (binding_java_lib PROPERTIES SUFFIX ".jnilib")
endif()

install(TARGETS binding_java_lib DESTINATION bindings/java )

target_link_libraries(binding_java_lib ${SE_EXTERNAL_LIBS} ${SE_LIBS} )

add_custom_command(	
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/copasi.jar
	       ${CMAKE_CURRENT_BINARY_DIR}/copasi-gui.jar
	COMMAND "${CMAKE_COMMAND}"
	ARGS -DJava_JAVAC_EXECUTABLE=\"${Java_JAVAC_EXECUTABLE}\"
		 -DJava_JAR_EXECUTABLE=\"${Java_JAR_EXECUTABLE}\"
		 -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
		 -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
		 -DFILE_SEP=\"${FILE_SEP}\"
		 -DPATH_SEP=${PATH_SEP}
		 -P "${CMAKE_CURRENT_SOURCE_DIR}/compile-native-files.cmake"
	
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/java-files
    COMMENT "Building: copasi.jar"
	) 

add_custom_target(binding_java_jar ALL DEPENDS 
	${CMAKE_CURRENT_BINARY_DIR}/copasi.jar	
	)
	
add_dependencies(binding_java_jar binding_java_swig)
	
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/copasi.jar 
	  ${CMAKE_CURRENT_BINARY_DIR}/copasi-gui.jar 
        DESTINATION bindings/java) 
file(GLOB examples ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.java)
install(FILES ${examples} DESTINATION bindings/java/examples) 

# compile java examples if needed to test whether 
# they still work with the current objectmodel
option (BUILD_JAVA_EXAMPLES "Build the Java examples." OFF)
mark_as_advanced(BUILD_JAVA_EXAMPLES)
if (BUILD_JAVA_EXAMPLES)
add_subdirectory(examples)
endif(BUILD_JAVA_EXAMPLES)

