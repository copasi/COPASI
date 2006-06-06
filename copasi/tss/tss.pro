######################################################################
# $Revision: 1.4.10.3 $ $Author: shoops $ $Date: 2006/06/06 22:42:01 $  
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
