######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2005/02/08 16:33:05 $  
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
