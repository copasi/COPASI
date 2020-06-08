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

if (ENABLE_FLEX_BISON)
  BISON_TARGET(CEvaluationParser function/CEvaluationParser.ypp ${COPASI_SOURCE_DIR}/function/CEvaluationParser_yacc.cpp COMPILE_FLAGS ${BISON_BINARY})
  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/function/CEvaluationParser_yacc.cpp)
  set(COPASI_HEADERS ${COPASI_HEADERS} ${COPASI_SOURCE_DIR}/function/CEvaluationParser_yacc.hpp)
  
  get_filename_component(COPASI_FLEX_SOURCE ${COPASI_SOURCE_DIR}/function/CEvaluationLexer.lpp ABSOLUTE)
  get_filename_component(COPASI_FLEX_TARGET ${COPASI_SOURCE_DIR}/function/CEvaluationLexer_lex.cpp ABSOLUTE)
  FLEX_TARGET(CEvaluationLexer ${COPASI_FLEX_SOURCE} ${COPASI_FLEX_TARGET} COMPILE_FLAGS ${FLEX_BINARY})
  set(COPASI_SOURCES ${COPASI_SOURCES} ${COPASI_SOURCE_DIR}/function/CEvaluationLexer_lex.cpp)
endif (ENABLE_FLEX_BISON)

file(GLOB HEADERS_FUN function/*.h function/*.hpp)
file(GLOB SOURCES_FUN function/*.cpp)

# create source group for IDEs
source_group(function FILES ${SOURCES_FUN} ${HEADERS_FUN})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_FUN})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_FUN})

