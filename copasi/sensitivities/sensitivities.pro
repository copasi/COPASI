######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2006/06/20 13:19:53 $  
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
