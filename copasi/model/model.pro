######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2004/11/04 01:01:43 $  
######################################################################

LIB = model

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += CChemEq.h \
           CChemEqElement.h \
           CChemEqInterface.h \
           CCompartment.h \
           CDeTerm.h \
           CMetab.h \
           CMetabNameInterface.h \
           CModel.h \
           CMoiety.h \
           #CParticleNumberList.h \
           CReaction.h \
           CSpec2Model.h \
           CSpecLine.h \
           CState.h \
           model.h
           
SOURCES += CChemEq.cpp \
           CChemEqElement.cpp \
           CChemEqInterface.cpp \
           CCompartment.cpp \
           CDeTerm.cpp \
           CMetab.cpp \
           CMetabNameInterface.cpp \
           CModel.cpp \
           CMoiety.cpp \
           #CParticleNumberList.cpp \
           CReaction.cpp \
           CScanInputFlexLexer.cpp \
           CSpec2Model.cpp \
           CSpecLine.cpp \
           CState.cpp

1.target = CScanInputFlexLexer.cpp
1.depends = CScanInputFlexLexer.lpp 
1.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 1
