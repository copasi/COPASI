######################################################################
# $Revision: 1.3 $ $Author: gauges $ $Date: 2004/10/21 15:29:58 $  
######################################################################

LIB = steadystate
include(../lib.pri)

# Input
HEADERS += CEigen.h \
           CMCAMethod.h \
#          CMCAProblem.h \
#	   CMCATask.h \
       	   CNewtonMethod.h \
           CSteadyStateMethod.h \
           CSteadyStateProblem.h \
           CSteadyStateTask.h

SOURCES += CEigen.cpp \
           CMCAMethod.cpp \
#          CMCAProblem.cpp \
#	   CMCATask.cpp \
           CNewtonMethod.cpp \
           CSteadyStateMethod.cpp \
           CSteadyStateProblem.cpp \
           CSteadyStateTask.cpp
