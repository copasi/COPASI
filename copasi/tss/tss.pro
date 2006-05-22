######################################################################
# $Revision: 1.4.10.2 $ $Author: shoops $ $Date: 2006/05/22 13:28:34 $  
######################################################################

LIB = tss

include(../lib.pri)
include(../common.pri)

# Input
debug {
  HEADERS += CTSSMethod.h
  HEADERS += CTSSProblem.h
  HEADERS += CTSSTask.h
}
HEADERS += MMASCIIExporter.h

debug {
  SOURCES += CTSSMethod.cpp
  SOURCES += CTSSProblem.cpp
  SOURCES += CTSSTask.cpp
}
SOURCES += MMASCIIExporter.cpp

DISTFILES += tss.dsp
