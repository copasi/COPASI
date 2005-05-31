######################################################################
# $Revision: 1.12 $ $Author: shoops $ $Date: 2005/05/31 17:53:33 $  
######################################################################

LIB = function

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCallParameters.h \
           CEvaluationFlexLexer.h \
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
           CEvaluationFlexLexer.cpp \
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

1.target   = CKinFunctionFlexLexer.cpp
1.depends  = CKinFunctionFlexLexer.lpp 
1.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 1

2.target   = CEvaluationFlexLexer.cpp
2.depends  = CEvaluationFlexLexer.lpp 
2.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 2

