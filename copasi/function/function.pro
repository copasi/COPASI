# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/function.pro,v $
#   $Revision: 1.31.2.1 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/11/13 14:53:10 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.31.2.1 $ $Author: shoops $ $Date: 2010/11/13 14:53:10 $
######################################################################

LIB = function

# Input
HEADERS += \
           CCallParameters.h \
           CDerive.h \
           CEvaluationLexer.h \
           CEvaluationNode.h \
           CEvaluationNodeCall.h \
           CEvaluationNodeChoice.h \
           CEvaluationNodeConstant.h \
           CEvaluationNodeDelay.h \
           CEvaluationNodeFunction.h \
           CEvaluationNodeLogical.h \
           CEvaluationNodeNumber.h \
           CEvaluationNodeObject.h \
           CEvaluationNodeOperator.h \
           CEvaluationNodeStructure.h \
           CEvaluationNodeVariable.h \
           CEvaluationNodeVector.h \
           CEvaluationNodeWhiteSpace.h \
           CEvaluationParser_yacc.h \
           CEvaluationTree.h \
           CExpression.h \
           CFunction.h \
           CFunctionAnalyzer.h \
           CFunctionDB.h \
           FunctionDB.xml.h \
           CFunctionParameter.h \
           CFunctionParameters.h \
           CKinFunction.h \
           CMassAction.h \
           CNodeK.h

SOURCES += \
           CCallParameters.cpp \
           CDerive.cpp \
           CEvaluationNode.cpp \
           CEvaluationNodeCall.cpp \
           CEvaluationNodeChoice.cpp \
           CEvaluationNodeConstant.cpp \
           CEvaluationNodeDelay.cpp \
           CEvaluationNodeFunction.cpp \
           CEvaluationNodeLogical.cpp \
           CEvaluationNodeNumber.cpp \
           CEvaluationNodeObject.cpp \
           CEvaluationNodeOperator.cpp \
           CEvaluationNodeStructure.cpp \
           CEvaluationNodeVariable.cpp \
           CEvaluationNodeVector.cpp \
           CEvaluationNodeWhiteSpace.cpp \
           CEvaluationLexer_lex.cpp \
           CEvaluationParser_yacc.cpp \
           CEvaluationTree.cpp \
           CExpression.cpp \
           CFunction.cpp \
           CFunctionAnalyzer.cpp \
           CFunctionDB.cpp \
           CFunctionParameter.cpp \
           CFunctionParameters.cpp \
           CKinFunction.cpp \
           CMassAction.cpp \
           CNodeK.cpp


contains(BUILD_PARSER, yes) {
  YACCSOURCES += CEvaluationParser.ypp
  SOURCES -= CEvaluationParser_yacc.cpp

  LEXSOURCES += CEvaluationLexer.lpp
  SOURCES -= CEvaluationLexer_lex.cpp
}


DISTFILES += CEvaluationParser.ypp \
             CEvaluationLexer.lpp
             
include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
