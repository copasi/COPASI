######################################################################
# $Revision: 1.2 $ $Author: gauges $ $Date: 2006/10/15 06:25:27 $  
######################################################################

LIB = ssa

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CSSATask.h \
	   CSSAProblem.h \
	   CSSAMethod.h

SOURCES += CSSATask.cpp \
	   CSSAProblem.cpp \
	   CSSAMethod.cpp

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


DISTFILES += ssa.dsp
