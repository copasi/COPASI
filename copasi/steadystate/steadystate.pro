######################################################################
# $Revision: 1.2 $ $Author: gauges $ $Date: 2004/10/21 14:43:17 $  
######################################################################

LIB = steadystate
include(../lib.pri)

# Input
HEADERS += CEigen.h \
           CMCAMethod.h \
           CNewtonMethod.h \
           CSteadyStateMethod.h \
           CSteadyStateProblem.h \
           CSteadyStateTask.h

SOURCES += CEigen.cpp \
           CMCAMethod.cpp \
           CNewtonMethod.cpp \
           CSteadyStateMethod.cpp \
           CSteadyStateProblem.cpp \
           CSteadyStateTask.cpp
