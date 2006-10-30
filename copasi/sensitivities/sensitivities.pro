######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2006/10/30 21:12:12 $  
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
