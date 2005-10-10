######################################################################
# $Revision: 1.1 $ $Author: ssahle $ $Date: 2005/10/10 16:13:43 $  
######################################################################

LIB = sensitivities

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CSensMethod.h \
           CSensProblem.h \
           CSensTask.h

SOURCES += CSensMethod.cpp \
           CSensProblem.cpp \
           CSensTask.cpp
