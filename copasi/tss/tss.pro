######################################################################
# $Revision: 1.6 $ $Author: gauges $ $Date: 2006/10/15 06:25:29 $  
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

contains(BUILD_OS, Linux){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)   
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
     
}

contains(BUILD_OS, Darwin){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)  
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
        
}   


DISTFILES += tss.dsp
