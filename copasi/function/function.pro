######################################################################
# $Revision: 1.15 $ $Author: shoops $ $Date: 2005/06/15 19:09:28 $  
######################################################################

LIB = function

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCallParameters.h \
           CEvaluationParser_yacc.h \
           CEvaluationLexer.h \
           CEvaluationNode.h \
           CEvaluationNodeConstant.h \
           CEvaluationNodeFunction.h \
           CEvaluationNodeNumber.h \
           CEvaluationNodeObject.h \
           CEvaluationNodeOperator.h \
           CEvaluationNodeStructure.h \
           CEvaluationNodeVariable.h \
           CEvaluationNodeWhiteSpace.h \
           CEvaluationTree.h \
           CExpression.h \
           CFunction.h \
           CFunctionDB.h \
           CFunctionParameter.h \
           CFunctionParameters.h \
           CKinFunction.h \
           CMassAction.h \
           CNodeK.h \
           CRange.h \
           CUsageRange.h

SOURCES += CCallParameters.cpp \
           CEvaluationNode.cpp \
           CEvaluationNodeConstant.cpp \
           CEvaluationNodeFunction.cpp \
           CEvaluationNodeNumber.cpp \
           CEvaluationNodeObject.cpp \
           CEvaluationNodeOperator.cpp \
           CEvaluationNodeStructure.cpp \
           CEvaluationNodeVariable.cpp \
           CEvaluationNodeWhiteSpace.cpp \
           CEvaluationTree.cpp \
           CExpression.cpp \
           CFunction.cpp \
           CFunctionDB.cpp \
           CFunctionParameter.cpp \
           CFunctionParameters.cpp \
           CKinFunction.cpp \
           CKinFunctionFlexLexer.cpp \
           CMassAction.cpp \
           CNodeK.cpp \
           CRange.cpp \
           CUsageRange.cpp

YACCSOURCES += CEvaluationParser.ypp

LEXSOURCES += CEvaluationLexer.lpp  

1.target   = CKinFunctionFlexLexer.cpp
1.depends  = CKinFunctionFlexLexer.lpp 
1.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 1


