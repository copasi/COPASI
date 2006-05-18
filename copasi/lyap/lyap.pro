######################################################################
# $Revision: 1.1.2.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:53 $  
######################################################################

LIB = lyap

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CLyapWolfMethod.h \
           #CTimeSeries.h \
           CLyapMethod.h \
           CLyapProblem.h \
           CLyapTask.h

SOURCES += CLyapWolfMethod.cpp \
           #CTimeSeries.cpp \
           CLyapMethod.cpp \
           CLyapProblem.cpp \
           CLyapTask.cpp

DISTFILES += lyaponov.dsp
