######################################################################
# $Revision: 1.3 $ $Author: ssahle $ $Date: 2005/06/24 09:01:40 $  
######################################################################

LIB = tss

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CTSSMethod.h \
           CTSSProblem.h \
           CTSSTask.h

SOURCES += CTSSMethod.cpp \
           CTSSProblem.cpp \
           CTSSTask.cpp
