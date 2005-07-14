######################################################################
# $Revision: 1.4 $ $Author: nsimus $ $Date: 2005/07/14 10:57:26 $  
######################################################################

LIB = tss

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CTSSMethod.h \
           CTSSProblem.h \
           CTSSTask.h \
	   MMASCIIExporter.h

SOURCES += CTSSMethod.cpp \
           CTSSProblem.cpp \
           CTSSTask.cpp \
	   MMASCIIExporter.cpp
