######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2004/11/04 01:01:42 $  
######################################################################

LIB = steadystate

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += CEigen.h \
           CMCAMethod.h \
           CMCAProblem.h \
	   CMCATask.h \
       	   CNewtonMethod.h \
           CSteadyStateMethod.h \
           CSteadyStateProblem.h \
           CSteadyStateTask.h

SOURCES += CEigen.cpp \
           CMCAMethod.cpp \
           CMCAProblem.cpp \
	   CMCATask.cpp \
           CNewtonMethod.cpp \
           CSteadyStateMethod.cpp \
           CSteadyStateProblem.cpp \
           CSteadyStateTask.cpp
