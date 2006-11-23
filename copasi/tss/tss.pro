######################################################################
# $Revision: 1.8 $ $Author: nsimus $ $Date: 2006/11/23 10:33:34 $  
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

HEADERS += ODEExporter.h
HEADERS += _C_ODEExporter.h
HEADERS += _BM_ODEExporter.h
HEADERS += _XPPAUT_ODEExporter.h

SOURCES += ODEExporter.cpp
SOURCES += _C_ODEExporter.cpp
SOURCES += _BM_ODEExporter.cpp
SOURCES += _XPPAUT_ODEExporter.cpp


DISTFILES += tss.dsp
