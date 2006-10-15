######################################################################
# $Revision: 1.6 $ $Author: gauges $ $Date: 2006/10/15 06:25:24 $  
######################################################################

LIB = randomGenerator

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += Cmt19937.h \
           Cr250.h \
           CRandom.h
           
SOURCES += Cmt19937.cpp \
           Cr250.cpp \
           CRandom.cpp

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


DISTFILES += randomGenerator.dsp
