######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:18:02 $  
######################################################################

LIB = steadystate
include(../lib.pri)

# Input
HEADERS += CEigen.h \
           CMca.h \
           CNewtonMethod.h \
           CSteadyStateMethod.h \
           CSteadyStateProblem.h \
           CSteadyStateTask.h

SOURCES += CEigen.cpp \
           CMca.cpp \
           CNewtonMethod.cpp \
           CSteadyStateMethod.cpp \
           CSteadyStateProblem.cpp \
           CSteadyStateTask.cpp
