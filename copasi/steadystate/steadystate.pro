######################################################################
# $Revision: 1.8 $ $Author: gauges $ $Date: 2006/10/15 06:25:28 $  
######################################################################

LIB = steadystate

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CEigen.h \
           CMCAMethod.h \
           CMCAProblem.h \
	   CMCATask.h \
       	   CNewtonMethod.h \
           CSteadyStateMethod.h \
           CSteadyStateProblem.h \
           CSteadyStateTask.h

SOURCES += CEigen.cpp \
           CMCAMethod.cpp \
           CMCAProblem.cpp \
	   CMCATask.cpp \
           CNewtonMethod.cpp \
           CSteadyStateMethod.cpp \
           CSteadyStateProblem.cpp \
           CSteadyStateTask.cpp

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


DISTFILES +=steadystate.dsp
