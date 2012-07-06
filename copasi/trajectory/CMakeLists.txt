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
# project (trajectory)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

file(GLOB HEADERS_TRAJECTORY trajectory/*.h)
file(GLOB SOURCES_TRAJECTORY trajectory/*.cpp)


# create source group for IDEs
source_group(trajectory FILES ${SOURCES_TRAJECTORY} ${HEADERS_TRAJECTORY})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_TRAJECTORY})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_TRAJECTORY})



# 
# set(HEADERS ${HEADERS} CHybridMethod.h)
# set(HEADERS ${HEADERS} CHybridMethodLSODA.h)
# set(HEADERS ${HEADERS} CHybridNextReactionRKMethod.h)
# set(HEADERS ${HEADERS} CHybridNextReactionLSODAMethod.h)
# set(HEADERS ${HEADERS} CLsodaMethod.h)
# set(HEADERS ${HEADERS} CStochDirectMethod.h)
# set(HEADERS ${HEADERS} CStochMethod.h)
# set(HEADERS ${HEADERS} CStochNextReactionMethod.h)
# set(HEADERS ${HEADERS} CTauLeapMethod.h)
# set(HEADERS ${HEADERS} CTimeSeries.h)
# set(HEADERS ${HEADERS} CTrajAdaptiveSA.h)
# set(HEADERS ${HEADERS} CTrajectoryMethod.h)
# set(HEADERS ${HEADERS} CTrajectoryMethodDsaLsodar.h)
# set(HEADERS ${HEADERS} CTrajectoryProblem.h)
# set(HEADERS ${HEADERS} CTrajectoryTask.h)
# 
# set(SOURCES ${SOURCES} CHybridMethod.cpp)
# set(SOURCES ${SOURCES} CHybridMethodLSODA.cpp)
# set(SOURCES ${SOURCES} CHybridNextReactionRKMethod.cpp)
# set(SOURCES ${SOURCES} CHybridNextReactionLSODAMethod.cpp)
# set(SOURCES ${SOURCES} CLsodaMethod.cpp)
# set(SOURCES ${SOURCES} CStochDirectMethod.cpp)
# set(SOURCES ${SOURCES} CStochMethod.cpp)
# set(SOURCES ${SOURCES} CStochNextReactionMethod.cpp)
# set(SOURCES ${SOURCES} CTauLeapMethod.cpp)
# set(SOURCES ${SOURCES} CTimeSeries.cpp)
# set(SOURCES ${SOURCES} CTrajAdaptiveSA.cpp)
# set(SOURCES ${SOURCES} CTrajectoryMethod.cpp)
# set(SOURCES ${SOURCES} CTrajectoryMethodDsaLsodar.cpp)
# set(SOURCES ${SOURCES} CTrajectoryProblem.cpp)
# set(SOURCES ${SOURCES} CTrajectoryTask.cpp)
# 

#add_library(trajectory STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(trajectory odepack++ math ${LIBSBML_LIBRARY})

