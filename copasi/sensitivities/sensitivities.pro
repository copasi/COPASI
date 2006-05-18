######################################################################
# $Revision: 1.1.4.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:57 $  
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

DISTFILES += sensitivities.dsp
