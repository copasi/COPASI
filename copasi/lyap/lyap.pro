######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2006/10/30 21:12:18 $  
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
