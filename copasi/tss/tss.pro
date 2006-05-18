######################################################################
# $Revision: 1.4.10.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:58 $  
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

DISTFILES += tss.dsp
