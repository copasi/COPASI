######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Fri May 16 20:04:03 2003
######################################################################

LIB = function
include(../lib.pri)

# Input
HEADERS += CCallParameters.h \
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

# The character # (hex 23) can not be escaped we therefore create a variable containing it
HASH = $$system(echo -e \\x23)

myLex = \
        $(LEX) -t $< | \
        sed -e 's/class istream;/$${HASH}include "copasi.h"/' \
            -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
            -e 's/$${HASH}include <unistd.h>/using namespace std;/' > $@

1.target   = CKinFunctionFlexLexer.cpp
1.depends  = CKinFunctionFlexLexer.lpp 
1.commands = $$myLex
QMAKE_EXTRA_UNIX_TARGETS += 1

