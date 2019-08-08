# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
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
# Description       : CMake build script for COPASI
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

file(GLOB HEADERS_TSS tss/*.h)
file(GLOB SOURCES_TSS tss/*.cpp)

if(NOT ENABLE_COPASI_TSS)
  list(REMOVE_ITEM SOURCES_TSS
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSMethod.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSProblem.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSTask.cpp
  )
  list(REMOVE_ITEM HEADERS_TSS
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSMethod.h
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSProblem.h
     ${CMAKE_CURRENT_SOURCE_DIR}/tss/CTSSTask.h
  )
endif(NOT ENABLE_COPASI_TSS)

# create source group for IDEs
source_group(tss FILES ${SOURCES_TSS} ${HEADERS_TSS})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_TSS})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_TSS})

