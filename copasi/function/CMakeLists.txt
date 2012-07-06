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

file(GLOB HEADERS_FUN function/*.h)
file(GLOB SOURCES_FUN function/*.cpp)


# create source group for IDEs
source_group(function FILES ${SOURCES_FUN} ${HEADERS_FUN})

# add files to main COPASI sources
set(COPASI_SOURCES ${COPASI_SOURCES} ${SOURCES_FUN})
set(COPASI_HEADERS ${COPASI_HEADERS} ${HEADERS_FUN})



# set(HEADERS ${HEADERS} CCallParameters.h)
# set(HEADERS ${HEADERS} CDerive.h)
# set(HEADERS ${HEADERS} CEvaluationLexer.h)
# set(HEADERS ${HEADERS} CEvaluationNode.h)
# set(HEADERS ${HEADERS} CEvaluationNodeCall.h)
# set(HEADERS ${HEADERS} CEvaluationNodeChoice.h)
# set(HEADERS ${HEADERS} CEvaluationNodeConstant.h)
# set(HEADERS ${HEADERS} CEvaluationNodeDelay.h)
# set(HEADERS ${HEADERS} CEvaluationNodeFunction.h)
# set(HEADERS ${HEADERS} CEvaluationNodeLogical.h)
# set(HEADERS ${HEADERS} CEvaluationNodeNumber.h)
# set(HEADERS ${HEADERS} CEvaluationNodeObject.h)
# set(HEADERS ${HEADERS} CEvaluationNodeOperator.h)
# set(HEADERS ${HEADERS} CEvaluationNodeStructure.h)
# set(HEADERS ${HEADERS} CEvaluationNodeVariable.h)
# set(HEADERS ${HEADERS} CEvaluationNodeVector.h)
# set(HEADERS ${HEADERS} CEvaluationNodeWhiteSpace.h)
# set(HEADERS ${HEADERS} CEvaluationParser_yacc.h)
# set(HEADERS ${HEADERS} CEvaluationTree.h)
# set(HEADERS ${HEADERS} CExpression.h)
# set(HEADERS ${HEADERS} CFunction.h)
# set(HEADERS ${HEADERS} CFunctionAnalyzer.h)
# set(HEADERS ${HEADERS} CFunctionDB.h)
# set(HEADERS ${HEADERS} FunctionDB.xml.h)
# set(HEADERS ${HEADERS} CFunctionParameter.h)
# set(HEADERS ${HEADERS} CFunctionParameters.h)
# set(HEADERS ${HEADERS} CKinFunction.h)
# set(HEADERS ${HEADERS} CMassAction.h)
# set(HEADERS ${HEADERS} CNodeK.h)
# 
# 
# set(SOURCES ${SOURCES} CCallParameters.cpp)
# set(SOURCES ${SOURCES} CDerive.cpp)
# set(SOURCES ${SOURCES} CEvaluationNode.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeCall.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeChoice.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeConstant.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeDelay.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeFunction.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeLogical.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeNumber.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeObject.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeOperator.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeStructure.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeVariable.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeVector.cpp)
# set(SOURCES ${SOURCES} CEvaluationNodeWhiteSpace.cpp)
# set(SOURCES ${SOURCES} CEvaluationLexer_lex.cpp)
# set(SOURCES ${SOURCES} CEvaluationParser_yacc.cpp)
# set(SOURCES ${SOURCES} CEvaluationTree.cpp)
# set(SOURCES ${SOURCES} CExpression.cpp)
# set(SOURCES ${SOURCES} CFunction.cpp)
# set(SOURCES ${SOURCES} CFunctionAnalyzer.cpp)
# set(SOURCES ${SOURCES} CFunctionDB.cpp)
# set(SOURCES ${SOURCES} CFunctionParameter.cpp)
# set(SOURCES ${SOURCES} CFunctionParameters.cpp)
# set(SOURCES ${SOURCES} CKinFunction.cpp)
# set(SOURCES ${SOURCES} CMassAction.cpp)
# set(SOURCES ${SOURCES} CNodeK.cpp)
# 

# add_library(function STATIC ${SOURCES} ${HEADERS})
# target_link_libraries(function sbmlimport randomGenerator)
# if(CLAPACK_FOUND)
# target_link_libraries(function ${CLAPACK_LIBRARIES})
# endif()
# 
