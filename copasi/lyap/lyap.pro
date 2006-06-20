######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2006/06/20 13:18:41 $  
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
