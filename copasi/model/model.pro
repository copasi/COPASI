######################################################################
# $RCSfile: model.pro,v $ $Revision: 1.2 $ 
# Commited by: $Author: shoops $ ($Date: 2003/05/18 20:07:28 $) 
######################################################################

LIB = model
include(../lib.pri)

# Input
HEADERS += CChemEq.h \
           CChemEqElement.h \
           CCompartment.h \
           CDeTerm.h \
           CMetab.h \
           CModel.h \
           CMoiety.h \
           CParticleNumberList.h \
           CReaction.h \
           CSpec2Model.h \
           CSpecLine.h \
           CState.h \
           model.h
           
SOURCES += CChemEq.cpp \
           CChemEqElement.cpp \
           CCompartment.cpp \
           CDeTerm.cpp \
           CMetab.cpp \
           CModel.cpp \
           CMoiety.cpp \
           CParticleNumberList.cpp \
           CReaction.cpp \
           CScanInputFlexLexer.cpp \
           CSpec2Model.cpp \
           CSpecLine.cpp \
           CState.cpp

1.target = CScanInputFlexLexer.cpp
1.depends = CScanInputFlexLexer.lpp 
1.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 1
