######################################################################
# $Revision: 1.1 $ $Author: ssahle $ $Date: 2005/06/22 09:26:09 $  
######################################################################

LIB = tss

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CTSS.h \
           CTSSProblem.h \
           CTSSTask.h

SOURCES += CTSSMethod.cpp \
           CTSSProblem.cpp \
           CTSSTask.cpp
