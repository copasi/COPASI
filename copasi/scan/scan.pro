######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:18:02 $  
######################################################################

LIB = scan
include(../lib.pri)

# Input
HEADERS += CScanMethod.h \
           CScanProblem.h \
           CScanTask.h

SOURCES += CScanMethod.cpp \
           CScanProblem.cpp \
           CScanTask.cpp
