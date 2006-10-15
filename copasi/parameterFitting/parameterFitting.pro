######################################################################
# $Revision: 1.5 $ $Author: gauges $ $Date: 2006/10/15 06:25:23 $  
######################################################################

LIB = fitting
SRC_TARGET = parameterFitting

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CExperiment.h \
           CExperimentSet.h \
           CExperimentObjectMap.h \
           CExperimentFileInfo.h \
           CFitItem.h \
           CFitMethod.h \
           CFitProblem.h \
           CFitTask.h
           
SOURCES += CExperiment.cpp \
           CExperimentSet.cpp  \
           CExperimentObjectMap.cpp \
           CExperimentFileInfo.cpp \
           CFitItem.cpp \
           CFitMethod.cpp \
           CFitProblem.cpp \
           CFitTask.cpp

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


DISTFILES += fitting.dsp
