######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sat May 17 20:57:42 2003
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

# The character # (hex 23) can not be escaped we therefore create a variable containing it
HASH = $$system(echo -e \\x23)

myLex = \
        $(LEX) -t $< | \
        sed -e 's/class istream;/$${HASH}include "copasi.h"/' \
            -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
            -e 's/$${HASH}include <unistd.h>/using namespace std;/' > $@

1.target = CScanInputFlexLexer.cpp
1.depends = CScanInputFlexLexer.lpp 
1.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 1
