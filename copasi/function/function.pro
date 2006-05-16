######################################################################
# $Revision: 1.20.4.1 $ $Author: shoops $ $Date: 2006/05/16 20:45:22 $  
######################################################################

LIB = function

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += \
           CCallParameters.h \
           CEvaluationLexer.h \
           CEvaluationNode.h \
           CEvaluationNodeCall.h \
           CEvaluationNodeChoice.h \
           CEvaluationNodeConstant.h \
           CEvaluationNodeFunction.h \
           CEvaluationNodeLogical.h \
           CEvaluationNodeNumber.h \
           CEvaluationNodeObject.h \
           CEvaluationNodeOperator.h \
           CEvaluationNodeStructure.h \
           CEvaluationNodeVariable.h \
           CEvaluationNodeVector.h \
           CEvaluationNodeWhiteSpace.h \
           CEvaluationTree.h \
           CExpression.h \
           CFunction.h \
           CFunctionDB.h \
           FunctionDB.xml.h \
           CFunctionParameter.h \
           CFunctionParameters.h \
           CKinFunction.h \
           CMassAction.h \
           CNodeK.h 

SOURCES += \
           CCallParameters.cpp \
           CEvaluationNode.cpp \
           CEvaluationNodeCall.cpp \
           CEvaluationNodeChoice.cpp \
           CEvaluationNodeConstant.cpp \
           CEvaluationNodeFunction.cpp \
           CEvaluationNodeLogical.cpp \
           CEvaluationNodeNumber.cpp \
           CEvaluationNodeObject.cpp \
           CEvaluationNodeOperator.cpp \
           CEvaluationNodeStructure.cpp \
           CEvaluationNodeVariable.cpp \
           CEvaluationNodeVector.cpp \
           CEvaluationNodeWhiteSpace.cpp \
           CEvaluationTree.cpp \
           CExpression.cpp \
           CFunction.cpp \
           CFunctionDB.cpp \
           CFunctionParameter.cpp \
           CFunctionParameters.cpp \
           CKinFunction.cpp \
           CMassAction.cpp \
           CNodeK.cpp 

contains(BUILD_PARSER, yes) {
  YACCSOURCES += CEvaluationParser.ypp
  LEXSOURCES += CEvaluationLexer.lpp  
}
else {
  HEADERS += CEvaluationParser_yacc.h
  SOURCES += CEvaluationLexer_lex.cpp \
             CEvaluationParser_yacc.cpp
}

DISTFILES += \
             function.dsp \
             CEvaluationParser.ypp \
             CEvaluationLexer.lpp

src_distribution.depends = function  
src_distribution.commands = $$COPY_SRC

QMAKE_EXTRA_UNIX_TARGETS += src_distribution

