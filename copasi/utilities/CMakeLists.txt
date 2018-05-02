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

file(GLOB HEADERS_UTILITIES utilities/*.h)
file(GLOB SOURCES_UTILITIES utilities/*.cpp)

if (ENABLE_FLEX_BISON)
  BISON_TARGET(CUnitParser utilities/CUnitParser.ypp ${COPASI_SOURCE_DIR}/utilities/CUnitParser_yacc.cpp COMPILE_FLAGS ${BISON_BINARY})
  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/utilities/CUnitParser_yacc.cpp)
  set(COPASI_HEADERS ${COPASI_HEADERS} ${COPASI_SOURCE_DIR}/utilities/CUnitParser_yacc.hpp)

  get_filename_component(COPASI_FLEX_SOURCE ${COPASI_SOURCE_DIR}/utilities/CUnitParser.lpp ABSOLUTE)
  get_filename_component(COPASI_FLEX_TARGET ${COPASI_SOURCE_DIR}/utilities/CUnitParser_lex.cpp ABSOLUTE)
  FLEX_TARGET(CUnitParser ${COPASI_FLEX_SOURCE} ${COPASI_FLEX_TARGET} COMPILE_FLAGS ${FLEX_BINARY})
  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/utilities/CUnitParser_lex.cpp)
endif (ENABLE_FLEX_BISON)

# create source group for IDEs
source_group(utilities FILES ${SOURCES_UTILITIES} ${HEADERS_UTILITIES})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_UTILITIES})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_UTILITIES})
