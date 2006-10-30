######################################################################
# $Revision: 1.9 $ $Author: shoops $ $Date: 2006/10/30 21:12:12 $  
######################################################################

LIB = steadystate

include(../lib.pri)
include(../common.pri)

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


DISTFILES +=steadystate.dsp
