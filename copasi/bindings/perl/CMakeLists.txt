###############################################################################
#
# Description       : CMake build script for COPASI PERL bindings
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
include(FindPerlLibs)



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
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS	-I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
	        -I${CMAKE_CURRENT_SOURCE_DIR}/../../
            -I${CMAKE_CURRENT_SOURCE_DIR}
			-c++
			-perl5
			#-proxy		
			${SWIG_EXTRA_ARGS}		 
			-o ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
			${CMAKE_CURRENT_SOURCE_DIR}/perl.i

    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/perl.i
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
	        ${SWIG_DEPENDENCIES}
    COMMENT "Swig Perl source") 

add_custom_target(binding_perl_swig ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp)

	
####################################################################
#
# Build native library
#

include(../../common.cmake)
include(../../CMakeConsoleApp.cmake)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../swig)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(BEFORE ${PERL_INCLUDE_PATH})

 
file(WRITE  "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "#ifdef WIN32\n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "// do not include MFC\n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "#define WIN32_LEAN_AND_MEAN \n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "// do not include GDI by default\n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "#define NOGDI\n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "#include <EXTERN.h>\n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "#endif\n\n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "#include \"copasi_wrapper.cpp\"\n")
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp" "\n\n")


if (NOT UNIX)
	add_definitions(-DWIN32SCK_IS_STDSCK -DWIN32IO_IS_STDIO)
endif ()

if (MSVC)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC)

add_library(binding_perl_lib MODULE ${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/COPASI.cpp 
      PROPERTIES OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp)
add_dependencies( binding_perl_lib binding_perl_swig) 

# 
# Determine the perl installation directory
#
set(PERL_PACKAGE_INSTALL_DIR)
set(PERL_PACKAGE_INSTALL_BIN_DIR)
if (UNIX OR CYGWIN) 
  execute_process(COMMAND "${PERL_EXECUTABLE}" -V:version
    OUTPUT_VARIABLE PERL_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REPLACE "'" "" PERL_VERSION ${PERL_VERSION})
  string(REPLACE ";" "" PERL_VERSION ${PERL_VERSION})
  string(REPLACE "version=" "" PERL_VERSION ${PERL_VERSION})
  string(REPLACE " " "" PERL_VERSION ${PERL_VERSION})
  execute_process(COMMAND "${PERL_EXECUTABLE}" -V:archname
    OUTPUT_VARIABLE PERL_PLATFORM OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REPLACE " " "" PERL_PLATFORM ${PERL_PLATFORM})
  string(REPLACE "'" "" PERL_PLATFORM ${PERL_PLATFORM})
  string(REPLACE ";" "" PERL_PLATFORM ${PERL_PLATFORM})
  string(REPLACE "archname=" "" PERL_PLATFORM ${PERL_PLATFORM})
  set(PERL_PACKAGE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/perl5/site-perl/${PERL_VERSION}/${PERL_PLATFORM})
  set(PERL_PACKAGE_INSTALL_BIN_DIR ${PERL_PACKAGE_INSTALL_DIR}/auto/COPASI)
else()
  set(PERL_PACKAGE_INSTALL_DIR ${MISC_PREFIX}bindings/perl)
  set(PERL_PACKAGE_INSTALL_BIN_DIR ${PERL_PACKAGE_INSTALL_DIR})
endif()


target_link_libraries(binding_perl_lib ${SE_EXTERNAL_LIBS} ${SE_LIBS}  ${PERL_LIBRARY})

set_target_properties(binding_perl_lib PROPERTIES  OUTPUT_NAME COPASI)
set_target_properties(binding_perl_lib PROPERTIES  PREFIX "")

if(APPLE)
	set_target_properties(binding_perl_lib PROPERTIES  SUFFIX ".bundle")
endif()

INSTALL(TARGETS binding_perl_lib  DESTINATION ${PERL_PACKAGE_INSTALL_BIN_DIR} )

