##############################################################################
#
# Description       : CMake build script for COPASI
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

# we need at least cmake 2.8 for the FindLAPACK functions
cmake_minimum_required (VERSION 2.8)
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 OLD)
endif(POLICY CMP0043)

# add an option to override the version
set(COPASI_OVERRIDE_VERSION "" CACHE STRING "Version String to override the version parsed from the header" )
mark_as_advanced(COPASI_OVERRIDE_VERSION)

# if the header file is not present, then set the override version to this one
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/copasi/CopasiVersion.h" AND NOT COPASI_OVERRIDE_VERSION)
  set(COPASI_OVERRIDE_VERSION "4.12.65")
endif()


set(COPASI_VERSION_MAJOR)
set(COPASI_VERSION_MINOR)
set(COPASI_VERSION_BUILD)
set(COPASI_VERSION_COMMENT)
# if override version is set, parse it and configure the header file with it
if (COPASI_OVERRIDE_VERSION)
  # parse the override string
  string(STRIP "${COPASI_OVERRIDE_VERSION}" VersionString)
  string(REPLACE "." ";" VersionString "${VersionString}" )
  string(REPLACE "-" ";" VersionString "${VersionString}" )
  list(LENGTH VersionString versionLength)
  list(GET VersionString 0 COPASI_VERSION_MAJOR )
  list(GET VersionString 1 COPASI_VERSION_MINOR )
  list(GET VersionString 2 COPASI_VERSION_BUILD )

  if(${versionLength} GREATER 3)
      list(GET VersionString 3 COPASI_VERSION_COMMENT )
  endif()

  # configure file
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/copasi/CopasiVersion.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/copasi/CopasiVersion.h"
  )

endif()

set(COPASI_VERSION)
# the CopasiVersion file only exists when the git tools have been configured
# and used. if that is not the case, we default to the canned version.
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/copasi/CopasiVersion.h")
  file(READ "${CMAKE_CURRENT_SOURCE_DIR}/copasi/CopasiVersion.h" COPASI_VERSION)

endif()
if (COPASI_VERSION)
  string(REGEX REPLACE ".*COPASI_VERSION_MAJOR ([0-9]+).*" "\\1" COPASI_VERSION_MAJOR "${COPASI_VERSION}")
  string(REGEX REPLACE ".*COPASI_VERSION_MINOR ([0-9]+).*" "\\1" COPASI_VERSION_MINOR "${COPASI_VERSION}")
  string(REGEX REPLACE ".*COPASI_VERSION_BUILD ([0-9]+).*" "\\1" COPASI_VERSION_BUILD "${COPASI_VERSION}")
endif()

project (COPASI VERSION "${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD}")


include (CMakeTestCCompiler)
include (CheckCSourceCompiles)
include (CheckCXXSourceCompiles)
include (CheckStructHasMember)
include (CheckLibraryExists)
include (CheckFunctionExists)
include (CheckCCompilerFlag)
include (CheckCSourceRuns)
include (CheckSymbolExists)
include (CheckTypeSize)

# preferably link against the static versions
# as compared to the dynamic ones

option(PREFER_STATIC "Preferably link against the static library versions" ON)

if (NOT WIN32 AND PREFER_STATIC)
 SET(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

if (CMAKE_MAJOR_VERSION LESS 3 OR CMAKE_MINOR_VERSION LESS 1)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
else()
  set(CMAKE_CXX_STANDARD 11)
endif()

CHECK_TYPE_SIZE("void*"  CMAKE_SIZEOF_VOID_P)

set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Full path to the library output directory")
mark_as_advanced(CMAKE_INSTALL_LIBDIR)

set(COPASI_BUILD_TYPE "native")
if (CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(COPASI_BUILD_TYPE "32bit")
else()
  set(COPASI_BUILD_TYPE "64bit")
endif()

# On OSX it is common to build universal binaries to support multiple
# processor architectures. The default behavior is not to build
# multiple architectures, as most users might not need that.
option(ENABLE_UNIVERSAL "Create universal binaries on Mac OS X." OFF)

if (APPLE AND ENABLE_UNIVERSAL)
  set(COPASI_BUILD_TYPE "universal")
endif()

set(COPASI_DEPENDENCY_DIR "" CACHE PATH "Dependency Directory containing, when set dependencies will be overwritten" )
mark_as_advanced(COPASI_DEPENDENCY_DIR)

if (COPASI_DEPENDENCY_DIR AND EXISTS ${COPASI_DEPENDENCY_DIR})
include(cmake-set-dependencies.cmake)
endif(COPASI_DEPENDENCY_DIR AND EXISTS ${COPASI_DEPENDENCY_DIR})



set(CMAKE_MODULE_PATH "${COPASI_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
   "Choose the type of build, options are: Debug or Release."
   FORCE)
ELSE()
   SET(CMAKE_BUILD_TYPE Release CACHE STRING
   "Choose the type of build, options are: Debug or Release."
   FORCE)
ENDIF()

# set test timeout to 3000 as the normal time limit is not sufficient
# for the comp tests
SET(DART_TESTING_TIMEOUT "3000" CACHE STRING "" FORCE)

enable_testing()
if (UNIX)
    # setup valgrind
    set(CMAKE_MEMORYCHECK_COMMAND valgrind)
    set(CMAKE_MEMORYCHECK_COMMAND_OPTIONS
       "--error-exitcode=1 --trace-children=yes --leak-check=full --show-reachable=yes --leak-resolution=high --track-origins=yes --error-limit=no ")

    set(MEMCHECK_COMMAND
       "${CMAKE_MEMORYCHECK_COMMAND} ${CMAKE_MEMORYCHECK_COMMAND_OPTIONS}")
    separate_arguments(MEMCHECK_COMMAND)
endif()

include(CTest)

if (BUILD_TESTS)
find_path(CPPUNIT_INCLUDE_DIR cppunit/Test.h )
find_library(CPPUNIT_LIBRARY NAMES cppunit)
endif(BUILD_TESTS)

set (DEFAULT_EXTUNIT ON)
# set (DEFAULT_NONLIN OFF)
set (DEFAULT_DEBUG_TRACING OFF)
set (DEFAULT_HYBRIDODE45 OFF)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # for the debug version we need to enable
  # COPASI_DEBUG
  add_definitions(-D_DEBUG)
  add_definitions(-DCOPASI_DEBUG)
  set (DEFAULT_HYBRIDODE45 ON)
  set (DEFAULT_EXTUNIT ON)
  set (DEFAULT_NONLIN ON)
  set (DEFAULT_DEBUG_TRACING ON)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

# there should be an option to disable the debug flag, as it litters the
# file system with trace files all over the place (or rather everywhere the
# program is started)

if (NOT WIN32)
option(ENABLE_COPASI_DEBUG_TRACE "Enable COPASI Debug Tracing" ${DEFAULT_DEBUG_TRACING})
if(ENABLE_COPASI_DEBUG_TRACE)
  add_definitions(-DCOPASI_DEBUG_TRACE)
endif(ENABLE_COPASI_DEBUG_TRACE)
mark_as_advanced(ENABLE_COPASI_DEBUG_TRACE)
endif()

# another option to create the COPASI SE library directly from the files, instead of first building an
# object library (necessary sometimes as the object library messes up debugging on VS2013)
option(DISABLE_CORE_OBJECT_LIBRARY "Disable creation of libCOPASISE-core object library and just create libCOPASISE-static" OFF)
mark_as_advanced(DISABLE_CORE_OBJECT_LIBRARY)


# Sven developed an option of scaling the residuals in the parameter estimation
# by the current simulation value (instead of 0) this removes the bias when
# using value scaled experimental data.
option(ENABLE_COPASI_PARAMETERFITTING_RESIDUAL_SCALING "Scale parameter estimation residuals with the simulation value" OFF)
if (ENABLE_COPASI_PARAMETERFITTING_RESIDUAL_SCALING)
  add_definitions(-DCOPASI_PARAMETERFITTING_RESIDUAL_SCALING)
endif(ENABLE_COPASI_PARAMETERFITTING_RESIDUAL_SCALING)

option(ENABLE_COPASI_BANDED_GRAPH "Enable the banded graph widget" OFF)
if (ENABLE_COPASI_BANDED_GRAPH)
  add_definitions(-DCOPASI_BANDED_GRAPH)
endif(ENABLE_COPASI_BANDED_GRAPH)

option(ENABLE_COPASI_NONLIN_DYN_OSCILLATION "Oscillation Widget" OFF)
if (ENABLE_COPASI_NONLIN_DYN_OSCILLATION)
  add_definitions(-DCOPASI_NONLIN_DYN_OSCILLATION)
endif()

option(ENABLE_COPASI_EXTUNIT "Extended Unit Support" ${DEFAULT_EXTUNIT})
if (ENABLE_COPASI_EXTUNIT)
  add_definitions(-DCOPASI_EXTUNIT)
endif(ENABLE_COPASI_EXTUNIT)

option(ENABLE_WITH_MERGEMODEL "Enable Model Merging" ON)
if (ENABLE_WITH_MERGEMODEL)
  add_definitions(-DWITH_MERGEMODEL)
endif(ENABLE_WITH_MERGEMODEL)

option(ENABLE_ANALYTICS "Enable Analytics Task" OFF)
if (ENABLE_ANALYTICS)
add_definitions(-DWITH_ANALYTICS)
endif(ENABLE_ANALYTICS)

option(ENABLE_PE_EVENT_CREATION "Enable Event Creation out of time series data" ON)
if (ENABLE_PE_EVENT_CREATION)
  add_definitions(-DWITH_PE_EVENT_CREATION)
endif(ENABLE_PE_EVENT_CREATION)

option(ENABLE_COMBINE_ARCHIVE "Enable COMBINE Archive support" ON)
if (ENABLE_COMBINE_ARCHIVE)
  add_definitions(-DWITH_COMBINE_ARCHIVE)

  if (WIN32)
    add_definitions(-DLIBCOMBINE_STATIC=1)
  endif()

  find_package(LIBCOMBINE REQUIRED)
  include_directories(BEFORE ${COMBINE_INCLUDE_DIR})
endif(ENABLE_COMBINE_ARCHIVE)

option(ENABLE_SDE_SUPPORT "Enable the support of Stochastic Differential Equations" ON)
if (ENABLE_SDE_SUPPORT)
  add_definitions(-DWITH_SDE_SUPPORT)
endif(ENABLE_SDE_SUPPORT)

option(COPASI_INSTALL_C_API "Enable this option to also install the COPASI C API" OFF)

option (BUILD_GUI "Disable this if you do not want to build the COPASI GUI (CopasiUI)." ON)

option(ENABLE_FLEX_BISON "Enable the use of flex and bison to create parsers." OFF)
if (ENABLE_FLEX_BISON)
  find_package(FLEX REQUIRED)
  find_package(BISON REQUIRED) 
  set(FLEX_BINARY ${FLEX_EXECUTABLE})
  set(FLEX_EXECUTABLE "${COPASI_SOURCE_DIR}/admin/flex.sh")
  set(BISON_BINARY ${BISON_EXECUTABLE})
  set(BISON_EXECUTABLE "${COPASI_SOURCE_DIR}/admin/yacc.sh")
endif (ENABLE_FLEX_BISON)

option(ENABLE_GPROF "Enable comiling and linking for gprof analysis." OFF)
if (ENABLE_GPROF)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pg")
  set(CMAKE_EXE_LINKER_FLAGS "-pg")
endif (ENABLE_GPROF)

if ( NOT CLAPACK_FOUND )
  find_package(CLAPACK REQUIRED)
endif ()


IF(DEFINED F2C_INTEGER)
  add_definitions(-DF2C_INTEGER=${F2C_INTEGER})
ENDIF()

IF(DEFINED F2C_LOGICAL)
  add_definitions(-DF2C_LOGICAL=${F2C_LOGICAL})
ENDIF()

option(CLAPACK_NO_BLASWRAP "If defined the NO_BLASWRAP compile option will be added" OFF)
if (CLAPACK_NO_BLASWRAP)
  add_definitions(-DNO_BLAS_WRAP)
endif(CLAPACK_NO_BLASWRAP)

if(DEFINED F2C_HAVE_H)
  add_definitions(-DHAVE_F2C_H)
endif()

include_directories(BEFORE ${CLAPACK_INCLUDE_DIR})
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LAPACK_CFLAGS}")

find_package(EXPAT REQUIRED)
include_directories(BEFORE ${EXPAT_INCLUDE_DIR})

# TODO find raptor
# TODO raptor should be restricted to a version which is at least
# 1.4.18, but lower then 2.0
find_package(RAPTOR REQUIRED)
include_directories(BEFORE ${RAPTOR_INCLUDE_DIR})

#TODO find libsbml, version should be 4.1 or 4.2
# we need to make sure libsbml has the render extension
find_package(LIBSBML REQUIRED)
include_directories(BEFORE ${LIBSBML_INCLUDE_DIR})

set(EXTRA_DEFS "" CACHE STRING
"additional definitions to be used." )
set(EXTRA_LIBS "" CACHE STRING
"List of additional libraries to link against.  Separate multiple names using semicolons." )
set(EXTRA_INCLUDE_DIRS "" CACHE STRING
"List of additional include directories to use during compilation. Separate multiple directories using semicolons." )

if(EXTRA_DEFS)
add_definitions(${EXTRA_DEFS})
endif(EXTRA_DEFS)


if(EXTRA_INCLUDE_DIRS)
foreach(dir ${EXTRA_INCLUDE_DIRS})
include_directories(BEFORE ${dir})
endforeach()
endif()


# TODO find libsedml, version
# Option for the COPASI support for SEDML
option (ENABLE_COPASI_SEDML "Enables SEDML support." ON)
mark_as_advanced(ENABLE_COPASI_SEDML)
if(ENABLE_COPASI_SEDML)
  add_definitions(-DCOPASI_SEDML)
  if (WIN32)
  add_definitions(-DLIBSEDML_STATIC)
  endif()

  find_package(LIBSEDML REQUIRED)
  include_directories(BEFORE ${LIBSEDML_INCLUDE_DIR})
endif(ENABLE_COPASI_SEDML)

# actually iconv is only needed on BSD like systems
find_package(ICONV)

if (ICONV_SECOND_ARGUMENT_IS_CONST)
  add_definitions(-DCOPASI_ICONV_CONST_CHAR)
endif (ICONV_SECOND_ARGUMENT_IS_CONST)


#platform specific defines

if(UNIX)
  if(APPLE)
    add_definitions(-DDarwin)
    if(CMAKE_GENERATOR AND XCODE_VERSION)
      option (COPASI_OVERWRITE_XCODE_GENERATOR "If true, will default to llvmgcc42 rather than clang." OFF)
      if(COPASI_OVERWRITE_XCODE_GENERATOR AND CMAKE_GENERATOR MATCHES "Xcode" AND (${XCODE_VERSION} VERSION_EQUAL 4 OR ${XCODE_VERSION} VERSION_GREATER 4))
        # Xcode 4 defaults to the Apple LLVM Compiler.
        set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvmgcc42")
      endif()
    endif()

    # Since we are encountering errors with the use of libc++ on OSX
    # this option allows to override which stdlib to use (needed for R
    # bindings on mavericks / yosemite ...)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      option(CLANG_USE_STDLIB "Use libstdc++ rather than libc++" OFF)
      if (CLANG_USE_STDLIB)
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++" )
      endif()
    endif()


    set(CMAKE_OSX_ARCHITECTURES "${CMAKE_OSX_ARCHITECTURES}" CACHE STRING
      "A semicolon-separated list of build architectures to be used.")
    if(ENABLE_UNIVERSAL)
      # if universal binaries are requested and none defined so far
      # overwrite them with all three common architectures. If the user
      # specified their own list of architectures do not touch!
      if(CMAKE_OSX_ARCHITECTURES STREQUAL "")
        STRING(REGEX REPLACE "^.*MacOSX([0-9]*\\.[0-9]*)\\.sdk$" "\\1"
               OSX_SDK_VERSION "${CMAKE_OSX_SYSROOT}")
        if(OSX_SDK_VERSION  VERSION_EQUAL "10.7" OR OSX_SDK_VERSION  VERSION_EQUAL "10.8")
          # OSX Lion no longer supports ppc architecture
          set(CMAKE_OSX_ARCHITECTURES "i386;x86_64" CACHE STRING
            "A semicolon-separated list of build architectures to be used." FORCE)
          else()
            set(CMAKE_OSX_ARCHITECTURES "i386;ppc;x86_64" CACHE STRING
              "A semicolon-separated list of build architectures to be used." FORCE)
        endif()
      endif()
    endif(ENABLE_UNIVERSAL)
  else()
    option(ENABLE_LIBCOPASISE_SHARED "Enable building of libCOPASISE as shared object." OFF)

    add_definitions(-DLinux)
    if(NOT CYGWIN)
      # on cygwin all code is position independent so -fPIC is not needed
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -fPIC")
      set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -fPIC")
    endif()
  endif()
else()
  if (CYGWIN)
    add_definitions(-DCygwin)
  else()
    add_definitions(-DWIN32)
  endif()
endif()

IF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
  add_definitions(-DFreeBSD)
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
endif()

if (WIN32 AND NOT CYGWIN)
  add_definitions(-DLIBSBML_EXPORTS -DLIBLAX_EXPORTS)
  add_definitions(-DRAPTOR_STATIC)
endif()

if(BUILD_GUI)
  if (UNIX AND NOT APPLE)
    FIND_LIBRARY(OPENGL_gl_LIBRARY NAMES GL PATHS /usr/lib/x86_64-linux-gnu/mesa)
  endif (UNIX AND NOT APPLE)

  find_package(OpenGL REQUIRED)

  include(${CMAKE_CURRENT_SOURCE_DIR}/ChooseQtVersion.cmake)

  # first try to find whether Qt5 is present
  option(QT_USE_TEXTBROWSER "Use QTextBrowser instead of Webkit / WebEngine for display of notes" ON)
  if (QT_USE_TEXTBROSWSER)
    set(QT_USE_TEXTBROWSER ON)
  endif()
  
  if (${SELECT_QT} MATCHES "Qt5" OR
      ${SELECT_QT} MATCHES "Any")
    # then narrow down the precise modules we need
    option(QT5_USE_WEBENGINE "Use QWebEngine instead of the deprecated QtWebKit for notes" OFF)
    
    if (QT_USE_TEXTBROWSER)
      QT_FIND_MODULES( Concurrent
                       Core
                       Gui
                       Widgets
                       Network
                       OpenGL
                       PrintSupport
                       Svg 
                       Xml
      )
    elseif (QT5_USE_WEBENGINE)
      QT_FIND_MODULES( Concurrent
                       Core
                       Gui
                       Widgets
                       Network
                       OpenGL
                       PrintSupport
                       Svg
                       WebEngine
                       WebEngineWidgets
                       Xml
      )
    else()
      QT_FIND_MODULES( Concurrent
                       Core
                       Gui
                       Widgets
                       Network
                       OpenGL
                       PrintSupport
                       Svg
                       WebKit
                       WebKitWidgets
                       Xml
      )
    endif()
    set(QTVERSION 5)
  else()
    # using qt 4.8
    if (QT_USE_TEXTBROWSER)
      QT_FIND_MODULES(Core Gui Network OpenGL Svg Xml)
    else(QT_USE_TEXTBROWSER)
      QT_FIND_MODULES(Core Gui Network OpenGL Svg WebKit Xml)
    endif(QT_USE_TEXTBROWSER)
  endif()

  # find Qt4
  #find_package(Qt4 4.7.0 REQUIRED QtCore QtOpenGL QtGui QtXml QtWebKit QtNetwork)
  # check for qwt, TODO check if the version is OK
  find_package(QwtQt4 REQUIRED)
  # check for qwtplot3d
  find_package(Qwtplot3dQt4 REQUIRED)

  # if the MML widget is available, we need to enable "HAVE_MML"

  option(ENABLE_MML "Enable the MML widget" ON)

  if(ENABLE_MML)
    find_package(QtMmlQt4 REQUIRED)
    add_definitions(-DHAVE_MML)
  endif(ENABLE_MML)

  # check for sbw
  option(ENABLE_SBW_INTEGRATION "Enable SBW Integration" ON)
  if (ENABLE_SBW_INTEGRATION)
  find_package(SBW REQUIRED)
  include_directories(${SBW_INCLUDE_DIR})
  add_definitions(-DCOPASI_SBW_INTEGRATION)

  # set up definitions for SBW
  if(UNIX)
  if(APPLE)
  add_definitions(-DDARWIN)
  endif()
  add_definitions(-DLINUX)
  endif()

  endif(ENABLE_SBW_INTEGRATION)

  if (APPLE)
    # TODO Carbon is only needed for the GUI
    include_directories(BEFORE /System/Library/Frameworks/Carbon.framework/Headers)

    find_library(CARBON_LIBRARY Carbon)
    find_library(QUICKTIME_LIBRARY QuickTime)
    find_package(ZLIB)
  endif (APPLE)

endif(BUILD_GUI)


# define what shall be build
option (BUILD_CXX_EXAMPLES "Build the C++ examples." OFF)

include(CMakeDependentOption)

# for the language bindings we need swig
option (ENABLE_CSHARP "Enable language bindings for the C# language." OFF)
option (ENABLE_JAVA "Enable language bindings for the Java language." OFF)
option (ENABLE_PYTHON "Enable language bindings for the Python language." OFF)
option (ENABLE_PERL "Enable language bindings for the Perl language." OFF)
option (ENABLE_OCTAVE "Enable language bindings for the Octave language." OFF)
option (ENABLE_R "Enable language bindings for the R language." OFF)

# we need swig for the language bindings. Only if SWIG was found, the options to
# build the different language bindings are enabled
# TODO test the SWIG version
if (ENABLE_CSHARP OR ENABLE_JAVA OR ENABLE_PYTHON OR ENABLE_PERL OR ENABLE_OCTAVE OR ENABLE_R)
  if (EXISTS "$ENV{SWIG_DIR}")
    SET (SWIG_DIR "$ENV{SWIG_DIR}")
    SET (SWIG_EXECUTABLE "$ENV{SWIG_DIR}/bin/swig")
  endif ()

  find_package(SWIG REQUIRED)
  
endif ()

option (ENABLE_USE_SBMLUNIT "Enables extended unit support." OFF)
mark_as_advanced(ENABLE_USE_SBMLUNIT)
if(ENABLE_USE_SBMLUNIT)
add_definitions(-DUSE_SBMLUNIT)
endif(ENABLE_USE_SBMLUNIT)

#Option for the COPASI support for SEDML currently being developed by Joseph
option (ENABLE_COPASI_SEDML "Enables SEDML support." ON)
mark_as_advanced(ENABLE_COPASI_SEDML)
if(ENABLE_COPASI_SEDML)
  add_definitions(-DCOPASI_SEDML)
endif(ENABLE_COPASI_SEDML)

#Option for the COPASI support for Provenance Framework currently being developed by Peyman
option (ENABLE_PROVENANCE "Enables Provenance support." OFF)
mark_as_advanced(ENABLE_PROVENANCE)

#Option for the COPASI support for Versioning Framework currently being developed by Peyman
option (ENABLE_VERSIONING "Enables Versioning support." OFF)
mark_as_advanced(ENABLE_VERSIONING)

#Option for the COPASI support for UNDO Framework currently being developed by Joseph
option (ENABLE_COPASI_UNDO "Enables UNDO support." ON)
mark_as_advanced(ENABLE_COPASI_UNDO)

if(ENABLE_PROVENANCE)
  set(ENABLE_VERSIONING ON)
  add_definitions(-DCOPASI_Provenance)
endif(ENABLE_PROVENANCE)

if(ENABLE_VERSIONING)
  add_definitions(-DCOPASI_Versioning)
endif(ENABLE_VERSIONING)

if(ENABLE_COPASI_UNDO)
  add_definitions(-DCOPASI_UNDO)
endif(ENABLE_COPASI_UNDO)

option (BUILD_SEMANTIC_TESTSUITE "Build the program to run the SBML semantic testsuite." OFF)
option (BUILD_STEADY_STATE_RUNNER "Build the program to run the comparisons on steady state results." OFF)
option (BUILD_MCA_RUNNER "Build the program to run the comparisons on MCA results." OFF)
option (BUILD_SBML_TESTSUITE "Build the program to run the new SBML testsuite." OFF)
option (BUILD_STOCHASTIC_TESTSUITE "Build the program to run the SBML stochastic testsuite." OFF)
option (BUILD_FRANKS_TESTSUITE "Build the program to run the Frank Bergmann's SBML tests." OFF)

option (BUILD_TESTS "Compiles CPPUNIT Testrunners." OFF)
mark_as_advanced(BUILD_TESTS)

mark_as_advanced(BUILD_SEMANTIC_TESTSUITE)
mark_as_advanced(BUILD_STEADY_STATE_RUNNER)
mark_as_advanced(BUILD_MCA_RUNNER)
mark_as_advanced(BUILD_SBML_TESTSUITE)
mark_as_advanced(BUILD_STOCHASTIC_TESTSUITE)
mark_as_advanced(BUILD_FRANKS_TESTSUITE)

option (BUILD_HYB_ODE_TESTS "Hybrid ODE Test." ON)
mark_as_advanced(BUILD_HYB_ODE_TESTS)

option (BUILD_HYB_TESTS "Hybrid Test." ON)
mark_as_advanced(BUILD_HYB_TESTS)


set(FILE_SEP)
set(PATH_SEP)
if(UNIX OR CYGWIN)
    set(PATH_SEP "/")
    set(FILE_SEP ":")
else()
    set(PATH_SEP "\\")
    set(FILE_SEP ";")
endif()

# we need to be able to set the paths to some files
# java headers, java compiler
# python headers and library
# perl binary
# mkoctfile
# R binary

#if we link statically, which is the default under windows, we need the following defines
# XML_STATIC
# LIBSBML_STATIC
# LIBLAX_STATIC
# RAPTOR_STATIC
# SBW_STATIC

# we need to define the following paths

# for the backend
# to expat
# to raptor
# to libsbml
# to clapack, lapack or mkl
# for clapack we need to define whether we use BLASWRAP or not

# for the frontend
# to sbw
# to qwt
# to qwtplot3d

# windows needs the following define
#DEFINES -= UNICODE
#DEFINES += _CRT_SECURE_NO_WARNINGS


# are we using the intel compiler
set(USING_INTEL)
if ((WIN32 OR (UNIX AND NOT APPLE))
    AND CMAKE_C_COMPILER
    AND ${CMAKE_C_COMPILER} MATCHES ".*ic[cl].*$")
  message(STATUS "Detected Intel Compiler")
  set(USING_INTEL TRUE)
endif ()

# if using msvc or intel windows compiler allow for the use of the static runtime
if(MSVC OR USING_INTEL)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE -DWIN32_LEAN_AND_MEAN)
    set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -D_CRT_SECURE_NO_WARNINGS")
    option(WITH_STATIC_RUNTIME "Compile using the static MSVC Runtime." OFF)
    if(WITH_STATIC_RUNTIME)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    add_definitions( -D_MT)
    endif(WITH_STATIC_RUNTIME)

    # on VS enable multiprocessor build
    if (MSVC)
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    endif()

    option(COPASI_USE_VLD "When running debug builds with MSVC use Visual Leak Detector." OFF)
    mark_as_advanced(COPASI_USE_VLD)

    if (COPASI_USE_VLD)

      add_definitions( -DCOPASI_USE_VLD)

    endif (COPASI_USE_VLD)

    # CMake no longer creates PDB files for static libraries after 2.8.11
    # so we store debug information in the object files instead
    if (${CMAKE_VERSION} VERSION_GREATER "2.8.11")
            foreach(flag_var
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
                CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
                CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

                if(${flag_var} MATCHES "/Zi")
            STRING(REPLACE "/Zi"  "/Z7" "${flag_var}" "${${flag_var}}")
                endif(${flag_var} MATCHES "/Zi")

            endforeach(flag_var)
    endif()

endif(MSVC OR USING_INTEL)



set(APPS "" CACHE INTERNAL "")
set(DIRS "${COPASI_DEPENDENCY_DIR}/bin;${COPASI_DEPENDENCY_DIR}/lib" CACHE INTERNAL "")
if (QT_BINARY_DIR)
  set(DIRS ${DIRS} ${QT_BINARY_DIR} CACHE INTERNAL "")
endif()
if (QT_LIBRARY_DIR)
  set(DIRS ${DIRS} ${QT_LIBRARY_DIR} CACHE INTERNAL "")
endif()



set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "COPASI is a software application for simulation and analysis of biochemical networks and their dynamics..")
set(CPACK_PACKAGE_NAME "COPASI")
set(CPACK_PACKAGE_VENDOR "copasi.org")
set(CPACK_PACKAGE_CONTACT "COPASI Support <support@copasi.org>")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/copasi/ArtisticLicense.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${COPASI_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${COPASI_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${COPASI_VERSION_BUILD}")
set(CPACK_RPM_PACKAGE_LICENSE "Artistic License")
set(CPACK_RPM_PACKAGE_GROUP "Applications/Engineering")
set(CPACK_DEBIAN_PACKAGE_SECTION "Applications")
set(CPACK_SOURCE_GENERATOR "TGZ")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if (${COPASI_BUILD_TYPE} MATCHES "64bit")
        set(CPACK_SYSTEM_NAME "Linux-64bit")
    else ()
        set(CPACK_SYSTEM_NAME "Linux-32bit")
    endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if (${COPASI_BUILD_TYPE} MATCHES "64bit")
        set(CPACK_SYSTEM_NAME "Windows-64bit")
    else ()
        set(CPACK_SYSTEM_NAME "Windows-32bit")
    endif ()
endif ()

set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_BINARY_DIR};/.git/;/.svn/;/.libs/;/.deps/;/.bzr/;/.o$/;/.lo$/;/.la$/;${CPACK_SOURCE_IGNORE_FILES};/.DS_Store;/.svnignore;blib;libsbml-dist;/gps/;CopasiWS;userdocs;docs")

if(UNIX)
    set(CPACK_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
    set(CPACK_SET_DESTDIR "ON")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "i386")
else()
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
endif()

include(CPack)

add_subdirectory(copasi)

if(BUILD_SEMANTIC_TESTSUITE)
add_subdirectory(semantic-test-suite)
endif (BUILD_SEMANTIC_TESTSUITE)

if(BUILD_SBML_TESTSUITE)
add_subdirectory(sbml-testsuite)
endif (BUILD_SBML_TESTSUITE)

if(BUILD_STOCHASTIC_TESTSUITE)
add_subdirectory(stochastic-testsuite)
endif (BUILD_STOCHASTIC_TESTSUITE)

if(BUILD_FRANKS_TESTSUITE)
add_subdirectory(franks_testsuite)
endif (BUILD_FRANKS_TESTSUITE)

if(BUILD_STEADY_STATE_RUNNER)
add_subdirectory(steady_state_test_wrapper)
endif (BUILD_STEADY_STATE_RUNNER)

if(BUILD_MCA_RUNNER)
add_subdirectory(mca_test_wrapper)
endif (BUILD_MCA_RUNNER)


if(BUILD_HYB_ODE_TESTS)
if (EXISTS ${CMAKE_SOURCE_DIR}/hyb-ode-test-suite)
add_subdirectory(hyb-ode-test-suite)
endif()
endif (BUILD_HYB_ODE_TESTS)

if(BUILD_HYB_TESTS)
if (EXISTS ${CMAKE_SOURCE_DIR}/hyb-test-suite)
add_subdirectory(hyb-test-suite)
endif()

endif (BUILD_HYB_TESTS)


# also install additional files and examples
file(GLOB_RECURSE WIZARD_HELP_FILES "${PROJECT_SOURCE_DIR}/copasi/wizard/help_html" copasi/wizard/help_html/*.html)
file(GLOB_RECURSE WIZARD_IMAGE_FILES "${PROJECT_SOURCE_DIR}/copasi/wizard/help_html/figures" copasi/wizard/help_html/figures/*.png)
file(GLOB_RECURSE EXAMPLE_FILES "${PROJECT_SOURCE_DIR}/TestSuite/distribution" TestSuite/distribution/*.*)
install(FILES ${WIZARD_HELP_FILES} DESTINATION share/copasi/doc/html)
install(FILES ${WIZARD_IMAGE_FILES} DESTINATION share/copasi/doc/html/figures)
install(FILES ${EXAMPLE_FILES} DESTINATION share/copasi/examples)
install(FILES
    "${PROJECT_SOURCE_DIR}/copasi/UI/icons/Copasi.ico"
    "${PROJECT_SOURCE_DIR}/copasi/UI/icons/CopasiDoc.ico"
        DESTINATION share/copasi/icons)
install(FILES
    "${PROJECT_SOURCE_DIR}/copasi/MIRIAM/MIRIAMResources.xml"
        DESTINATION share/copasi/config)

# set up variables for cpack
include(InstallRequiredSystemLibraries)

get_directory_property(DirDefs COMPILE_DEFINITIONS)

message(STATUS "-----------------------------------------------------------
 Building COPASI ${COPASI_VERSION_MAJOR}.${COPASI_VERSION_MINOR}.${COPASI_VERSION_BUILD} (${CMAKE_BUILD_TYPE})

   Source Dir        = ${CMAKE_SOURCE_DIR}
   Binary Dir        = ${CMAKE_BINARY_DIR}
   Install Prefix    = ${CMAKE_INSTALL_PREFIX}

 Dependencies:
   Vendor            = ${BLA_VENDOR}
   LAPACK Libs       = ${CLAPACK_LIBRARIES}
   LAPACK LDFLAGS    = ${CLAPACK_LINKER_FLAGS}

   Expat Libs        = ${EXPAT_LIBRARY}
   Expat include     = ${EXPAT_INCLUDE_DIR}

   Raptor Libs       = ${RAPTOR_LIBRARY}
   Raptor include    = ${RAPTOR_INCLUDE_DIR}

   libSBML lib       = ${LIBSBML_LIBRARY}
   libSBML include   = ${LIBSBML_INCLUDE_DIR}

   QWT lib           = ${QWT_LIBRARY}
   QWT include       = ${QWT_INCLUDE_DIR}
   QWT version       = ${QWT_VERSION_STRING} (0x${QWT_VERSION_NUMERIC})

   qwtplot3d lib     = ${QWTPLOT3D_LIBRARY}
   qwtplot3d include = ${QWTPLOT3D_INCLUDE_DIR}

   qtmml lib         = ${MML_LIBRARY}
   qtmml include     = ${MML_INCLUDE_DIR}

   SBW lib           = ${SBW_LIBRARIES}
   SBW include       = ${SBW_INCLUDE_DIR}

   libSEDML lib       = ${LIBSEDML_LIBRARY}
   libSEDML include   = ${LIBSEDML_INCLUDE_DIR}


 Options:

   COPASI_EXTUNIT           = ${ENABLE_COPASI_EXTUNIT}
   SBW integration          = ${ENABLE_SBW_INTEGRATION}
   SBML Unit                = ${ENABLE_USE_SBMLUNIT}
   Model Merging            = ${ENABLE_WITH_MERGEMODEL}
   SEDML support            = ${ENABLE_COPASI_SEDML}
   Combine Archive support  = ${ENABLE_COMBINE_ARCHIVE}
   SDE support              = ${ENABLE_SDE_SUPPORT}
   GPROF support            = ${ENABLE_GPROF}
   UNDO framework           = ${ENABLE_COPASI_UNDO}
   Versioning framework     = ${ENABLE_VERSIONING}
   Provenance framework     = ${ENABLE_PROVENANCE}
   Analytics Task           = ${ENABLE_ANALYTICS}
   Additional Defines       = ${DirDefs}

  Language Bindings:

   SWIG                     = ${SWIG_EXECUTABLE}
   .NET Bindings            = ${ENABLE_CSHARP}
   Java Bindings            = ${ENABLE_JAVA}
   Python Bindings          = ${ENABLE_PYTHON}
   Perl Bindings            = ${ENABLE_PERL}
   Octave Bindings          = ${ENABLE_OCTAVE}
   R Bindings               = ${ENABLE_R}

  Building:

   COPASI SE               = ${BUILD_SE}
   COPASI UI               = ${BUILD_GUI}

   C++ Examples            = ${BUILD_CXX_EXAMPLES}

   SBML TestRunner         = ${BUILD_SBML_TESTSUITE}
   Franks TestRunner       = ${BUILD_FRANKS_TESTSUITE}
   Semantic Testsuite      = ${BUILD_SEMANTIC_TESTSUITE}
   Stochastic Testsuite    = ${BUILD_STOCHASTIC_TESTSUITE}
   Steady State TestRunner = ${BUILD_STEADY_STATE_RUNNER}
   MCA TestRunner          = ${BUILD_MCA_RUNNER}

-----------------------------------------------------------
")
