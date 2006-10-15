######################################################################
# $Revision: 1.5 $ $Author: gauges $ $Date: 2006/10/15 06:25:20 $  
######################################################################

LIB = mathmodel

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CMathConstant.h \
           CMathEq.h \
           CMathModel.h \
           CMathNode.h \
           CMathSymbol.h \
           CMathVariable.h
           
SOURCES += CMathConstant.cpp \
           CMathEq.cpp \
           CMathModel.cpp \
           CMathNode.cpp \
           CMathSymbol.cpp \
           CMathVariable.cpp


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

           
