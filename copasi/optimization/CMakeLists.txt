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
# project (optimization)
# 
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )
# 
file(GLOB HEADERS_OPTIMIZATION optimization/*.h)
file(GLOB SOURCES_OPTIMIZATION optimization/*.cpp)

list(REMOVE_ITEM SOURCES_OPTIMIZATION 
   ${CMAKE_CURRENT_SOURCE_DIR}/optimization/CGA.cpp
   #${CMAKE_CURRENT_SOURCE_DIR}/optimization/COptMethodDE.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/optimization/COptMethodEP2.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/optimization/COptMethodHGASA.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/optimization/CRandomSearchMaster.cpp
)


# create source group for IDEs
source_group(optimization FILES ${SOURCES_OPTIMIZATION} ${HEADERS_OPTIMIZATION})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_OPTIMIZATION})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_OPTIMIZATION})


# set(HEADERS ${HEADERS} COptItem.h)
# set(HEADERS ${HEADERS} COptMethod.h)
# set(HEADERS ${HEADERS} COptMethodEP.h)
# set(HEADERS ${HEADERS} COptMethodGA.h)
# set(HEADERS ${HEADERS} COptMethodGASR.h)
# set(HEADERS ${HEADERS} COptMethodHookeJeeves.h)
# set(HEADERS ${HEADERS} COptMethodLevenbergMarquardt.h)
# set(HEADERS ${HEADERS} COptMethodNelderMead.h)
# set(HEADERS ${HEADERS} COptMethodPraxis.h)
# set(HEADERS ${HEADERS} COptMethodPS.h)
# set(HEADERS ${HEADERS} COptMethodSA.h)
# set(HEADERS ${HEADERS} COptMethodSRES.h)
# set(HEADERS ${HEADERS} COptMethodSteepestDescent.h)
# set(HEADERS ${HEADERS} COptMethodStatistics.h)
# set(HEADERS ${HEADERS} COptMethodTruncatedNewton.h)
# set(HEADERS ${HEADERS} COptProblem.h)
# set(HEADERS ${HEADERS} COptTask.h)
# set(HEADERS ${HEADERS} CPraxis.h)
# set(HEADERS ${HEADERS} CRandomSearch.h)
# set(HEADERS ${HEADERS} CTruncatedNewton.h)
# set(HEADERS ${HEADERS} FminBrent.h)
# 
# set(SOURCES ${SOURCES} COptItem.cpp)
# set(SOURCES ${SOURCES} COptMethod.cpp)
# set(SOURCES ${SOURCES} COptMethodEP.cpp)
# set(SOURCES ${SOURCES} COptMethodGA.cpp)
# set(SOURCES ${SOURCES} COptMethodGASR.cpp)
# set(SOURCES ${SOURCES} COptMethodHookeJeeves.cpp)
# set(SOURCES ${SOURCES} COptMethodLevenbergMarquardt.cpp)
# set(SOURCES ${SOURCES} COptMethodNelderMead.cpp)
# set(SOURCES ${SOURCES} COptMethodPraxis.cpp)
# set(SOURCES ${SOURCES} COptMethodPS.cpp)
# set(SOURCES ${SOURCES} COptMethodSA.cpp)
# set(SOURCES ${SOURCES} COptMethodSRES.cpp)
# set(SOURCES ${SOURCES} COptMethodSteepestDescent.cpp)
# set(SOURCES ${SOURCES} COptMethodStatistics.cpp)
# set(SOURCES ${SOURCES} COptMethodTruncatedNewton.cpp)
# set(SOURCES ${SOURCES} COptProblem.cpp)
# set(SOURCES ${SOURCES} COptTask.cpp)
# set(SOURCES ${SOURCES} CPraxis.cpp)
# set(SOURCES ${SOURCES} CRandomSearch.cpp)
# set(SOURCES ${SOURCES} CTruncatedNewton.cpp)
# set(SOURCES ${SOURCES} FminBrent.cpp)
# 

#add_library(optimization STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(optimization fitting)

