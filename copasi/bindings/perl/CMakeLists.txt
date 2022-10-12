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
# Description       : CMake build script for COPASI PERL bindings
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

ADD_CUSTOM_COMMAND(  
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS  -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
          -I${CMAKE_CURRENT_SOURCE_DIR}/../../
          -I${CMAKE_CURRENT_SOURCE_DIR}
          -I${CMAKE_SOURCE_DIR}
          -c++
          -perl5
          #-proxy    
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
          ${SWIG_EXTRA_ARGS}
          -o ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
          ${CMAKE_CURRENT_SOURCE_DIR}/perl.i
    COMMAND "${CMAKE_COMMAND}"
      -DSRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}
      -DFILENAME=\"${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp\"
      -P "${CMAKE_CURRENT_SOURCE_DIR}/patch-swig-file.cmake"
      
    COMMAND "${CMAKE_COMMAND}"
    ARGS -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
         -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
         -P "${CMAKE_CURRENT_SOURCE_DIR}/../common/patch-wrapper.cmake"

    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/perl.i
    DEPENDS ${SWIG_DEPENDENCIES}
    COMMENT "Swig Perl source") 

add_custom_target(binding_perl_swig ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/perl.i)

####################################################################
#
# Build native library
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

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

if (WIN32)
if (MSVC OR USING_INTEL)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC OR USING_INTEL)
endif(WIN32)

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


target_link_libraries(binding_perl_lib libCOPASISE-static ${PERL_LIBRARY})

set_target_properties(binding_perl_lib PROPERTIES  OUTPUT_NAME COPASI)
set_target_properties(binding_perl_lib PROPERTIES  PREFIX "")

if(APPLE)
	set_target_properties(binding_perl_lib PROPERTIES  SUFFIX ".bundle")
endif()

INSTALL(TARGETS binding_perl_lib  DESTINATION ${PERL_PACKAGE_INSTALL_BIN_DIR} )

