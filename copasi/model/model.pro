######################################################################
# $Revision: 1.16 $ $Author: gauges $ $Date: 2006/10/15 06:25:22 $  
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

contains(BUILD_OS, Linux){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)   
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
     
}

contains(BUILD_OS, Darwin){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)  
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
        
}   


DISTFILES += model.dsp \
             CChemEqParser_lex.cpp \
             CChemEqParser_yacc.cpp
