######################################################################
# $Revision: 1.15 $ $Author: shoops $ $Date: 2006/06/20 13:18:57 $  
######################################################################

LIB = model

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CChemEq.h \
           CChemEqElement.h \
           CChemEqInterface.h \
           CChemEqParser.h \
           CCompartment.h \
           CMetab.h \
           CMetabNameInterface.h \
           CModel.h \
           CModelValue.h \
           CMoiety.h \
           CObjectLists.h \
           CReaction.h \
           CReactionInterface.h \
#           CScanInputFlexLexer.h \
           CState.h \
           model.h
           
SOURCES += CChemEq.cpp \
           CChemEqElement.cpp \
           CChemEqInterface.cpp \
           CChemEqParser.cpp \
           CCompartment.cpp \
           CMetab.cpp \
           CMetabNameInterface.cpp \
           CModel.cpp \
           CModelValue.cpp \
           CMoiety.cpp \
           CObjectLists.cpp \
           CReaction.cpp \
           CReactionInterface.cpp \
#           CScanInputFlexLexer.cpp \
           CState.cpp

contains(BUILD_PARSER, yes) {
  YACCSOURCES += CChemEqParser.ypp
  LEXSOURCES += CChemEqParser.lpp  
}
else {
  HEADERS += CChemEqParser_yacc.h
  SOURCES += CChemEqParser_yacc.cpp \
             CChemEqParser_lex.cpp
}

# 1.target = CScanInputFlexLexer.cpp
# 1.depends = CScanInputFlexLexer.lpp 
# 1.commands = $$myLex
# QMAKE_EXTRA_UNIX_TARGETS += 1

DISTFILES += model.dsp \
             CChemEqParser_lex.cpp \
             CChemEqParser_yacc.cpp
