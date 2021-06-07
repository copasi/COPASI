# Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
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

file(GLOB HEADERS_MATH math/*.h)
file(GLOB SOURCES_MATH math/*.cpp)

if (NOT ENABLE_JIT)
  list(REMOVE_ITEM SOURCES_MATH 
    ${CMAKE_CURRENT_SOURCE_DIR}/math/CJitExpression.cpp)
  list(REMOVE_ITEM HEADERS_MATH 
    ${CMAKE_CURRENT_SOURCE_DIR}/math/CJitExpression.h)
endif(NOT ENABLE_JIT)

if (SOURCES_MATH)
# create source group for IDEs
source_group(math FILES ${SOURCES_MATH} ${HEADERS_MATH})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_MATH})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_MATH})


endif(SOURCES_MATH)
