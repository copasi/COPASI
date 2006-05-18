######################################################################
# $Revision: 1.3.12.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:57 $  
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
