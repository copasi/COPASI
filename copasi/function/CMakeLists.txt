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
# 
# cmake_minimum_required (VERSION 2.6)
# project (function)
# 
# include_directories(
#   "${PROJECT_SOURCE_DIR}/.." 
#   "${PROJECT_SOURCE_DIR}/../.." 
#   "${PROJECT_SOURCE_DIR}"
# )

if (ENABLE_FLEX_BISON)
  BISON_TARGET(CEvaluationParser function/CEvaluationParser.ypp ${COPASI_SOURCE_DIR}/function/CEvaluationParser_yacc.cpp COMPILE_FLAGS ${BISON_BINARY})
  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/function/CEvaluationParser_yacc.cpp)
  set(COPASI_HEADERS ${COPASI_HEADERS} ${COPASI_SOURCE_DIR}/function/CEvaluationParser_yacc.hpp)
  
  FLEX_TARGET(CEvaluationLexer function/CEvaluationLexer.lpp ${COPASI_SOURCE_DIR}/function/CEvaluationLexer_lex.cpp COMPILE_FLAGS ${FLEX_BINARY})
  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/function/CEvaluationLexer_lex.cpp)
endif (ENABLE_FLEX_BISON)

file(GLOB HEADERS_FUN function/*.h function/*.hpp)
file(GLOB SOURCES_FUN function/*.cpp)

# create source group for IDEs
source_group(function FILES ${SOURCES_FUN} ${HEADERS_FUN})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_FUN})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_FUN})



