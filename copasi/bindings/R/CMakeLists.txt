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
# Description       : CMake build script for COPASI R bindings
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
              /usr/include/R /usr/local/include/R /usr/local/${CMAKE_INSTALL_LIBDIR}/R/include/
              /Library/Frameworks/R.framework/Versions/Current/Resources/include
              $ENV{ProgramFiles}/R/R-3.1.0/include
              $ENV{ProgramW6432}/R/R-3.1.0/include
              $ENV{ProgramFiles}/R/R-3.0.3/include
              $ENV{ProgramW6432}/R/R-3.0.3/include
              $ENV{ProgramFiles}/R/R-2.15.3/include
              $ENV{ProgramW6432}/R/R-2.15.3/include
              $ENV{ProgramFiles}/R/R-2.15.2/include
              $ENV{ProgramW6432}/R/R-2.15.2/include
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
      PATHS /usr/${LIB_DIR} /usr/local/${LIB_DIR} 
          /usr/${CMAKE_INSTALL_LIBDIR} /usr/local/${CMAKE_INSTALL_LIBDIR} /usr/${CMAKE_INSTALL_LIBDIR}/R/lib
          /usr/lib /usr/local/lib /usr/lib/R/lib
          $ENV{ProgramFiles}/R/R-3.1.0/bin${R_SUFFIX}
          $ENV{ProgramW6432}/R/R-3.1.0/bin${R_SUFFIX}
          $ENV{ProgramFiles}/R/R-3.0.3/bin${R_SUFFIX}
          $ENV{ProgramW6432}/R/R-3.0.3/bin${R_SUFFIX}
          $ENV{ProgramFiles}/R/R-2.15.3/bin${R_SUFFIX}
          $ENV{ProgramW6432}/R/R-2.15.3/bin${R_SUFFIX}
          $ENV{ProgramFiles}/R/R-2.15.2/bin${R_SUFFIX}
          $ENV{ProgramW6432}/R/R-2.15.2/bin${R_SUFFIX}
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
          $ENV{ProgramFiles}/R/R-3.1.0/bin
          $ENV{ProgramW6432}/R/R-3.1.0/bin
          $ENV{ProgramFiles}/R/R-3.0.3/bin
          $ENV{ProgramW6432}/R/R-3.0.3/bin
          $ENV{ProgramFiles}/R/R-2.15.3/bin
          $ENV{ProgramW6432}/R/R-2.15.3/bin
          $ENV{ProgramFiles}/R/R-2.15.2/bin
          $ENV{ProgramW6432}/R/R-2.15.2/bin
          $ENV{ProgramFiles}/R/R-2.15.1/bin
          $ENV{ProgramW6432}/R/R-2.15.1/bin
          /usr/local/bin
          /usr/bin
          /Library/Frameworks/R.framework/Versions/Current/Resources/bin/
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
       ${CMAKE_CURRENT_BINARY_DIR}/COPASI.R
    COMMAND "${SWIG_EXECUTABLE}"
    ARGS  -I${CMAKE_CURRENT_SOURCE_DIR}/../swig/
          -I${CMAKE_CURRENT_SOURCE_DIR}/../../
          -I${CMAKE_CURRENT_SOURCE_DIR}
          -I${CMAKE_SOURCE_DIR}
          -c++
          -r    
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
          ${CMAKE_CURRENT_SOURCE_DIR}/R.i
    
    COMMAND "${CMAKE_COMMAND}"
      -DSRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}
      -DFILENAME=\"${CMAKE_CURRENT_BINARY_DIR}/COPASI.R\"
      -P "${CMAKE_CURRENT_SOURCE_DIR}/patch-swig-file.cmake"
    
    COMMAND "${CMAKE_COMMAND}"
    ARGS -DBIN_DIRECTORY=\"${CMAKE_CURRENT_BINARY_DIR}\"
         -DSRC_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}\"
         -P "${CMAKE_CURRENT_SOURCE_DIR}/../common/patch-wrapper.cmake"
         
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/R.i
    DEPENDS ${SWIG_DEPENDENCIES}
    COMMENT "Swig R source") 

add_custom_target(binding_r_swig ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/copasi_wrapper.cpp)

  
####################################################################
#
# Build native library
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${R_INCLUDE_DIRS})


if (WIN32)
if (MSVC OR USING_INTEL)
  # the build fails when compiled with packages as the object file is too 
  # big adding the big flag makes it work!
  add_definitions(/bigobj)
endif(MSVC OR USING_INTEL)
endif(WIN32)

add_library(binding_r_lib SHARED copasi_wrapper.cpp ${CMAKE_CURRENT_SOURCE_DIR}/RProcessCallback.cpp)
add_dependencies( binding_r_lib binding_r_swig) 

set_target_properties (binding_r_lib PROPERTIES OUTPUT_NAME "COPASI")
if (UNIX)
  set_target_properties (binding_r_lib PROPERTIES PREFIX "")
  set_target_properties (binding_r_lib PROPERTIES SUFFIX ".so")
endif()


if(APPLE OR UNIX)
  option (R_USE_DYNAMIC_LOOKUP
  "Do not actually link against the r library, instead use the undefined lookup mechanism." OFF)
  mark_as_advanced(R_USE_DYNAMIC_LOOKUP)
endif(APPLE OR UNIX)

if (R_USE_DYNAMIC_LOOKUP)
  if (APPLE)
    set_target_properties (binding_r_lib PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
  endif()
  target_link_libraries(binding_r_lib libCOPASISE-static)
else()
  target_link_libraries(binding_r_lib libCOPASISE-static ${R_LIB})
endif()


####################################################################
#
# create the r package
#

MACRO (TODAY RESULT) 
    IF (WIN32) 
        EXECUTE_PROCESS(COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE ${RESULT} OUTPUT_STRIP_TRAILING_WHITESPACE) 
        string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${RESULT} ${${RESULT}}) 
    ELSEIF(UNIX) 
        EXECUTE_PROCESS(COMMAND "date" "+%Y-%m-%d" OUTPUT_VARIABLE ${RESULT} OUTPUT_STRIP_TRAILING_WHITESPACE) 
        string(REGEX REPLACE "(..)/(..)/..(..).*" "\\1/\\2/\\3" ${RESULT} ${${RESULT}}) 
    ELSE (WIN32) 
        MESSAGE(SEND_ERROR "date not implemented") 
        SET(${RESULT} 000000) 
    ENDIF (WIN32) 
ENDMACRO (TODAY) 

TODAY(CURRENT_DATE) 

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/COPASI")

set(R_LIBRARY_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/COPASI/inst/libs")

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/COPASI/R)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/temp)
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION.in"
  "${CMAKE_CURRENT_BINARY_DIR}/COPASI/DESCRIPTION"
  )
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/NAMESPACE"
  "${CMAKE_CURRENT_BINARY_DIR}/COPASI/NAMESPACE"
)

set(LIBSBML_R_NATIVELIB)
if (${CMAKE_VERSION} VERSION_LESS 3.0.1)
  get_target_property(LIBSBML_R_NATIVELIB binding_r_lib LOCATION)
else()
  set(LIBSBML_R_NATIVELIB $<TARGET_FILE:binding_r_lib>)
endif()

if (APPLE AND ENABLE_UNIVERSAL)

file(MAKE_DIRECTORY ${R_LIBRARY_DESTINATION})
file(MAKE_DIRECTORY ${R_LIBRARY_DESTINATION}/i386)
file(MAKE_DIRECTORY ${R_LIBRARY_DESTINATION}/x86_64)

add_custom_command(  
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/COPASI_${PACKAGE_VERSION}.zip
  COMMAND "${CMAKE_COMMAND}"
      -DFILENAME=\"${CMAKE_CURRENT_BINARY_DIR}/COPASI.R\"
      -P "${CMAKE_CURRENT_SOURCE_DIR}/patch-swig-file.cmake"
  COMMAND "${CMAKE_COMMAND}"
  ARGS  -E copy_if_different 
     ${LIBSBML_R_NATIVELIB}
     ${R_LIBRARY_DESTINATION}/i386
  COMMAND "${CMAKE_COMMAND}"
  ARGS  -E copy_if_different
     ${LIBSBML_R_NATIVELIB}
     ${R_LIBRARY_DESTINATION}/x86_64
  COMMAND "${CMAKE_COMMAND}"
  ARGS  -E copy_if_different 
     ${CMAKE_CURRENT_BINARY_DIR}/COPASI.R
     ${CMAKE_CURRENT_BINARY_DIR}/COPASI/R
    COMMAND "${R_INTERPRETER}"
    ARGS  CMD INSTALL --build 
        --no-libs 
      --no-test-load 
      --no-clean-on-error 
      --no-multiarch 
      COPASI
      -l temp      
  MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/COPASI.R
  DEPENDS ${SWIG_DEPENDENCIES}
    COMMENT "Create R Package") 

else(APPLE AND ENABLE_UNIVERSAL)

if (WIN32)
if (LIBSBML_BUILD_TYPE STREQUAL "32bit")
set(R_LIBRARY_DESTINATION "${R_LIBRARY_DESTINATION}/i386")
else()
set(R_LIBRARY_DESTINATION "${R_LIBRARY_DESTINATION}/x64")
endif()
endif()

if (APPLE)
if (LIBSBML_BUILD_TYPE STREQUAL "32bit")
set(R_LIBRARY_DESTINATION "${R_LIBRARY_DESTINATION}/i386")
else()
set(R_LIBRARY_DESTINATION "${R_LIBRARY_DESTINATION}/x86_64")
endif()
endif(APPLE)


file(MAKE_DIRECTORY ${R_LIBRARY_DESTINATION})

add_custom_command(  
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/COPASI_${PACKAGE_VERSION}.zip
  COMMAND "${CMAKE_COMMAND}"
      -DFILENAME=\"${CMAKE_CURRENT_BINARY_DIR}/COPASI.R\"
      -P "${CMAKE_CURRENT_SOURCE_DIR}/patch-swig-file.cmake"
  COMMAND "${CMAKE_COMMAND}"
  ARGS  -E copy_if_different 
     ${LIBSBML_R_NATIVELIB}
     ${R_LIBRARY_DESTINATION}
  COMMAND "${CMAKE_COMMAND}"
  ARGS  -E copy_if_different 
     ${CMAKE_CURRENT_BINARY_DIR}/COPASI.R
     ${CMAKE_CURRENT_BINARY_DIR}/COPASI/R
  COMMAND "${CMAKE_COMMAND}"
  ARGS -DR_INTERPRETER=\"${R_INTERPRETER}\"
     -P "${CMAKE_CURRENT_SOURCE_DIR}/create-r-package.cmake"
  
  MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/COPASI.R
  DEPENDS ${SWIG_DEPENDENCIES}
    COMMENT "Create R Package") 
endif(APPLE AND ENABLE_UNIVERSAL)
add_custom_target(binding_r_package ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/COPASI_${PACKAGE_VERSION}.zip binding_r_lib)

add_test(NAME test_r_example1
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example1.R
)

add_test(NAME test_r_example2
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example2.R
                                  --args      ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator.cps
)

add_test(NAME test_r_example3
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example3.R
                                  --args      ${CMAKE_SOURCE_DIR}/TestSuite/distribution/brusselator-model.xml
)

add_test(NAME test_r_example4
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example4.R
)

add_test(NAME test_r_example5
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example5.R
)

add_test(NAME test_r_example6
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example6.R
)

add_test(NAME test_r_example7
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example7.R
)

add_test(NAME test_r_example8
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example8.R
)

add_test(NAME test_r_example9
         COMMAND ${R_INTERPRETER} --slave -f  ${CMAKE_SOURCE_DIR}/copasi/bindings/R/examples/example9.R
)

