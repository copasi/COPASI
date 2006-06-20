######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2006/06/20 13:19:52 $  
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
