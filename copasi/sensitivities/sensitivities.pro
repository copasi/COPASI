######################################################################
# $Revision: 1.3 $ $Author: gauges $ $Date: 2006/10/15 06:25:26 $  
######################################################################

LIB = sensitivities

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CSensMethod.h \
           CSensProblem.h \
           CSensTask.h

SOURCES += CSensMethod.cpp \
           CSensProblem.cpp \
           CSensTask.cpp

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


DISTFILES += sensitivities.dsp
