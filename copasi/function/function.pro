######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2005/05/25 18:20:46 $  
######################################################################

LIB = function

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCallParameters.h \
           CEvaluationNode.h \
           CEvaluationNodeConstant.h \
           CEvaluationNodeNumber.h \
           CEvaluationNodeOperator.h \
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
           CEvaluationNodeNumber.cpp \
           CEvaluationNodeOperator.cpp \
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

