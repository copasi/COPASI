######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2003/05/19 00:39:49 $  
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
