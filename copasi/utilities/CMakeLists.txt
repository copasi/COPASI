# Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the 
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

file(GLOB HEADERS_UTILITIES utilities/*.h)
file(GLOB SOURCES_UTILITIES utilities/*.cpp)

if (ENABLE_FLEX_BISON)
  get_filename_component(COPASI_FLEX_SOURCE ${COPASI_SOURCE_DIR}/utilities/CUnitParser.lpp ABSOLUTE)
  get_filename_component(COPASI_FLEX_TARGET ${COPASI_SOURCE_DIR}/utilities/CUnitParser_lex.cpp ABSOLUTE)

  if (${CMAKE_VERSION} VERSION_LESS 4.0.0)
    BISON_TARGET(CUnitParser utilities/CUnitParser.ypp ${COPASI_SOURCE_DIR}/utilities/CUnitParser_yacc.cpp COMPILE_FLAGS ${BISON_BINARY})
    FLEX_TARGET(CUnitParser ${COPASI_FLEX_SOURCE} ${COPASI_FLEX_TARGET} COMPILE_FLAGS ${FLEX_BINARY})
  else ()
    bison_target(CUnitParser utilities/CUnitParser.ypp ${COPASI_SOURCE_DIR}/utilities/CUnitParser_yacc.cpp COMPILE_FLAGS ${BISON_BINARY})
    flex_target(CUnitParser ${COPASI_FLEX_SOURCE} ${COPASI_FLEX_TARGET} COMPILE_FLAGS ${FLEX_BINARY})
  endif (${CMAKE_VERSION} VERSION_LESS 4.0.0)

  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/utilities/CUnitParser_yacc.cpp)
  set(COPASI_HEADERS ${COPASI_HEADERS} ${COPASI_SOURCE_DIR}/utilities/CUnitParser_yacc.hpp)
  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/utilities/CUnitParser_lex.cpp)
endif (ENABLE_FLEX_BISON)

# create source group for IDEs
source_group(utilities FILES ${SOURCES_UTILITIES} ${HEADERS_UTILITIES})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_UTILITIES})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_UTILITIES})
