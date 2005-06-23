######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2005/06/23 14:20:45 $  
######################################################################

LIB = tss

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CTSSTask.h \
           CTSSProblem.h \
           CTSSTask.h

SOURCES += CTSSMethod.cpp \
           CTSSProblem.cpp \
           CTSSTask.cpp
