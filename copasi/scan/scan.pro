######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2004/11/04 01:01:42 $  
######################################################################

LIB = scan

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += CScanMethod.h \
           CScanProblem.h \
           CScanTask.h

SOURCES += CScanMethod.cpp \
           CScanProblem.cpp \
           CScanTask.cpp
