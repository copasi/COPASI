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
# Description       : CMake build script for COPASI Python bindings
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

find_package(PythonInterp REQUIRED)

# specify that the same python library should be found 
# as the one the selected interpreter uses
set (Python_ADDITIONAL_VERSIONS ${PYTHON_VERSION_STRING})
if (NOT PYTHON_USE_DYNAMIC_LOOKUP)
set (LIBS_REQUIRED REQUIRED)
endif()
find_package(PythonLibs ${LIBS_REQUIRED})

####################################################################
#
# ensure that LAPACK variables are there for swig
# 
if (APPLE)
  set(SWIG_EXTRA_ARGS ${SWIG_EXTRA_ARGS} -DDarwin -DF2C_INTEGER=int)
endif(APPLE)

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
           ${CMAKE_CURRENT_BINARY_DIR}/COPASI.py
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS  -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
          -I${CMAKE_CURRENT_SOURCE_DIR}/../../
          -I${CMAKE_CURRENT_SOURCE_DIR}
          -I${CMAKE_SOURCE_DIR}
          -c++
          -python
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
          -features autodoc,1
          -o ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp 
          ${CMAKE_CURRENT_SOURCE_DIR}/python.i
          
    COMMAND "${CMAKE_COMMAND}"
    ARGS -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
         -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
         -P "${CMAKE_CURRENT_SOURCE_DIR}/../common/patch-wrapper.cmake"
    COMMAND "${CMAKE_COMMAND}"
    ARGS -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
         -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
         -DVERSION=${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}
         -P "${CMAKE_CURRENT_SOURCE_DIR}/patch-python.cmake"

    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/python.i
    DEPENDS ${SWIG_DEPENDENCIES}
    COMMENT "Swig Python source") 

add_custom_target(binding_python_swig ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/python.i)

	
####################################################################
#
# Build native library
#


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})

if (WIN32)
if (MSVC OR USING_INTEL)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC OR USING_INTEL)
endif(WIN32)

add_library(binding_python_lib SHARED copasi_wrapper.cpp)
add_dependencies( binding_python_lib binding_python_swig) 

set_target_properties (binding_python_lib PROPERTIES OUTPUT_NAME "_COPASI")
if (UNIX)
	set_target_properties (binding_python_lib PROPERTIES PREFIX "")
	set_target_properties (binding_python_lib PROPERTIES SUFFIX ".so")
else()		
	if (CYGWIN)
		set_target_properties (binding_python_lib PROPERTIES PREFIX "")
		set_target_properties (binding_python_lib PROPERTIES SUFFIX ".dll")
	else()
		set_target_properties (binding_python_lib PROPERTIES SUFFIX ".pyd")	
	endif()
endif()


if(APPLE OR UNIX)
  option (PYTHON_USE_DYNAMIC_LOOKUP
  "Do not actually link against the python library, instead use the undefined lookup mechanism." OFF)
  mark_as_advanced(PYTHON_USE_DYNAMIC_LOOKUP)
endif(APPLE OR UNIX)

if (PYTHON_USE_DYNAMIC_LOOKUP)
  if (APPLE)
    set_target_properties (binding_python_lib PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
  endif()
  target_link_libraries(binding_python_lib libCOPASISE-static)
else()
  target_link_libraries(binding_python_lib libCOPASISE-static ${PYTHON_LIBRARIES})
endif()

# 
# Determine the python installation directory
#
set(PYTHON_PACKAGE_INSTALL_DIR)
if (UNIX OR CYGWIN) 
  execute_process(COMMAND "${PYTHON_EXECUTABLE}" -c "import sys; sys.stdout.write('{}.{}'.format(*sys.version_info[:2]))"
    OUTPUT_VARIABLE PYTHON_VERSION)
  set(PYTHON_PACKAGE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/python${PYTHON_VERSION}/site-packages)
else()
  set(PYTHON_PACKAGE_INSTALL_DIR ${MISC_PREFIX}bindings/python)
endif()

INSTALL(TARGETS binding_python_lib DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/copasi )

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/copasi.pth" "copasi\n")
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/copasi.pth  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR})
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/COPASI.py  DESTINATION ${PYTHON_PACKAGE_INSTALL_DIR}/copasi )
file(GLOB examples ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.py)
INSTALL(FILES ${examples} DESTINATION ${MISC_PREFIX}bindings/python) 

macro(ADJUST_PYTHONPATH target)

if (UNIX)
set_tests_properties(${target} PROPERTIES ENVIRONMENT PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}:$<TARGET_FILE_DIR:binding_python_lib>:$ENV{PYTHONPATH})
else()
# need to creatively replace the semicolons
SET (NEW_PYTHON_PATH "${CMAKE_CURRENT_BINARY_DIR}\\;$<TARGET_FILE_DIR:binding_python_lib>\\;$ENV{PYTHONPATH}")
STRING(REPLACE "\\;" ";" NEW_PYTHON_PATH "${NEW_PYTHON_PATH}")
STRING(REPLACE ";" "\\;" NEW_PYTHON_PATH "${NEW_PYTHON_PATH}")
set_tests_properties(${target} PROPERTIES ENVIRONMENT PYTHONPATH=${NEW_PYTHON_PATH})
endif()

endmacro()

add_test(NAME test_python_checkModel
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/checkModel.py
                                      ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator-model.xml
)
ADJUST_PYTHONPATH(test_python_checkModel)

add_test(NAME test_python_example1
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example1.py         
)
ADJUST_PYTHONPATH(test_python_example1)

add_test(NAME test_python_example2
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example2.py 
                                      ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator.cps
)
ADJUST_PYTHONPATH(test_python_example2)

add_test(NAME test_python_example3
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example3.py
                                      ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator-model.xml
)
ADJUST_PYTHONPATH(test_python_example3)

add_test(NAME test_python_example4
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example4.py
)
ADJUST_PYTHONPATH(test_python_example4)

add_test(NAME test_python_example5
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example5.py
)
ADJUST_PYTHONPATH(test_python_example5)

add_test(NAME test_python_example6
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example6.py
)
ADJUST_PYTHONPATH(test_python_example6)

add_test(NAME test_python_example7
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example7.py
)
ADJUST_PYTHONPATH(test_python_example7)

add_test(NAME test_python_example8
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example8.py
)
ADJUST_PYTHONPATH(test_python_example8)

add_test(NAME test_python_example9
         COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/copasi/bindings/python/examples/example9.py
)
ADJUST_PYTHONPATH(test_python_example9)
