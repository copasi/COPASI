######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2006/10/30 21:12:10 $  
######################################################################

LIB = tss

include(../lib.pri)
include(../common.pri)

# Input
contains(DEFINES, COPASI_TSS) {
  HEADERS += CTSSMethod.h
  HEADERS += CTSSProblem.h
  HEADERS += CTSSTask.h

  SOURCES += CTSSMethod.cpp
  SOURCES += CTSSProblem.cpp
  SOURCES += CTSSTask.cpp
}

HEADERS += MMASCIIExporter.h

SOURCES += MMASCIIExporter.cpp


DISTFILES += tss.dsp
