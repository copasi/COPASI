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
# Description       : CMake build script for COPASI octave bindings
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
include(FindPythonLibs)
include(FindPythonInterp)
find_package(Octave REQUIRED)

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

    ARGS -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
         -I${CMAKE_CURRENT_SOURCE_DIR}/../../
         -I${CMAKE_CURRENT_SOURCE_DIR}
         -I${CMAKE_SOURCE_DIR}
         -c++
         -octave
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
         ${CMAKE_CURRENT_SOURCE_DIR}/octave.i

    COMMAND "${CMAKE_COMMAND}"

      -DSRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}
      -DFILENAME=\"${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp\"
      -P "${CMAKE_CURRENT_SOURCE_DIR}/patch-swig-file.cmake"
      
      
    COMMAND "${CMAKE_COMMAND}"
    ARGS -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
         -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
         -P "${CMAKE_CURRENT_SOURCE_DIR}/../common/patch-wrapper.cmake"

    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/octave.i

    DEPENDS         ${SWIG_DEPENDENCIES}
                    ${CMAKE_CURRENT_SOURCE_DIR}/patch-swig-file.cmake

    COMMENT "Swig Octave source"

) 

add_custom_target(binding_octave_swig ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp)

	
####################################################################
#
# Build native library
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${OCTAVE_INCLUDE_DIR})
include_directories(${OCTAVE_INCLUDE_DIR}/octave)

if (WIN32)
if (MSVC OR USING_INTEL)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC OR USING_INTEL)
endif(WIN32)

add_library(binding_octave_lib SHARED copasi_wrapper.cpp)
add_dependencies( binding_octave_lib binding_octave_swig) 

set_target_properties (binding_octave_lib PROPERTIES OUTPUT_NAME "COPASI")
if (UNIX)
	set_target_properties (binding_octave_lib PROPERTIES PREFIX "")
	set_target_properties (binding_octave_lib PROPERTIES SUFFIX ".oct")
else()		
	if (CYGWIN)
		set_target_properties (binding_octave_lib PROPERTIES PREFIX "")
		set_target_properties (binding_octave_lib PROPERTIES SUFFIX ".oct")
	else()
		set_target_properties (binding_octave_lib PROPERTIES SUFFIX ".oct")	
	endif()
endif()

target_link_libraries(binding_octave_lib libCOPASISE-static ${OCTAVE_OCTAVE_LIBRARY})

# 
# Determine the python installation directory
#
set(OCTAVE_PACKAGE_INSTALL_DIR)
if (UNIX OR CYGWIN) 
  set(OCTAVE_PACKAGE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR})
else()
  set(OCTAVE_PACKAGE_INSTALL_DIR ${MISC_PREFIX}bindings/octave)
endif()

INSTALL(TARGETS binding_octave_lib DESTINATION ${OCTAVE_PACKAGE_INSTALL_DIR} )

set(OCTAVE_INTERPRETER "octave" CACHE STRING "full path to the octave interpreter to be used for running tests." )

add_test(NAME octave_test_version
         COMMAND ${OCTAVE_INTERPRETER} --no-gui --eval "COPASI;display(COPASI.CVersion.VERSION.getVersion())"
)
set_tests_properties(octave_test_version PROPERTIES PASS_REGULAR_EXPRESSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")

add_test(NAME test_octave_example1
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example1.oct
)

add_test(NAME test_octave_example2
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example2.oct
                                 ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator.cps
)

add_test(NAME test_octave_example3
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example3.oct
                                 ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator-model.xml
)

add_test(NAME test_octave_example4
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example4.oct
)

add_test(NAME test_octave_example5
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example5.oct
)

add_test(NAME test_octave_example6
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example6.oct
)

add_test(NAME test_octave_example7
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example7.oct
)

add_test(NAME test_octave_example8
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example8.oct
)

add_test(NAME test_octave_example9
         COMMAND ${OCTAVE_INTERPRETER} --no-gui ${CMAKE_SOURCE_DIR}/copasi/bindings/octave/examples/example9.oct
)

