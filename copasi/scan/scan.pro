######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2006/10/30 21:12:13 $  
######################################################################

LIB = scan

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CScanMethod.h \
           CScanProblem.h \
           CScanTask.h

SOURCES += CScanMethod.cpp \
           CScanProblem.cpp \
           CScanTask.cpp


DISTFILES += scan.dsp
