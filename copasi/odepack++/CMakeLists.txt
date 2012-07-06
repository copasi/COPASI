###############################################################################
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

# cmake_minimum_required (VERSION 2.6)
# project (odepack++)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )
# 
file(GLOB HEADERS_ODEPACK odepack++/*.h)
file(GLOB SOURCES_ODEPACK odepack++/*.cpp)

# create source group for IDEs
source_group(odepack++ FILES ${SOURCES_ODEPACK} ${HEADERS_ODEPACK})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_ODEPACK})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_ODEPACK})

# set(HEADERS ${HEADERS} common.h)
# set(SOURCES ${SOURCES} common.cpp)
# 
# # Main routines
# set(HEADERS ${HEADERS} CLSODA.h)
# set(SOURCES ${SOURCES} CLSODA.cpp)
# set(HEADERS ${HEADERS} CLSODAR.h)
# set(SOURCES ${SOURCES} CLSODAR.cpp)
# 
# # These files represent the code for the class CInternalSolver
# set(HEADERS ${HEADERS} CInternalSolver.h)
# set(SOURCES ${SOURCES} dintdy.cpp)
# set(SOURCES ${SOURCES} dprja.cpp)
# set(SOURCES ${SOURCES} drcheck.cpp)
# set(SOURCES ${SOURCES} dsolsy.cpp)
# set(SOURCES ${SOURCES} dstoda.cpp)
# 
# # Support routines
# set(HEADERS ${HEADERS}  dbnorm.h)
# set(HEADERS ${HEADERS}  dcfode.h)
# set(HEADERS ${HEADERS}  dewset.h)
# set(HEADERS ${HEADERS}  dfnorm.h)
# set(HEADERS ${HEADERS}  dgbfa.h)   # wrapper for dgbtrf
# set(HEADERS ${HEADERS}  dgbsl.h)   # wrapper for dgbtrs
# set(HEADERS ${HEADERS}  dgefa.h)   # wrapper for dgetrf
# set(HEADERS ${HEADERS}  dgesl.h)   # wrapper for dgetrs
# set(HEADERS ${HEADERS}  dmnorm.h)
# 
# set(SOURCES ${SOURCES}  dbnorm.cpp)
# set(SOURCES ${SOURCES}  dcfode.cpp)
# set(SOURCES ${SOURCES}  dewset.cpp)
# set(SOURCES ${SOURCES}  dfnorm.cpp)
# set(SOURCES ${SOURCES}  dmnorm.cpp)
# 
# # Error reporting
# set(HEADERS ${HEADERS}  Cxerrwd.h)
# set(SOURCES ${SOURCES}  Cxerrwd.cpp)
# 
# include_directories(BEFORE ${CMAKE_SOURCE_DIR}/copasi)
# add_library(odepack++ STATIC ${SOURCES} ${HEADERS})
# if(CLAPACK_FOUND)
# target_link_libraries(odepack++ ${CLAPACK_LIBRARIES})
# endif()
# 

