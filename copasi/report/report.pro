######################################################################
# $Revision: 1.15 $ $Author: gauges $ $Date: 2006/10/15 06:25:24 $  
######################################################################

LIB = report

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiObjectReference.h \
           CCopasiStaticString.h \
           CCopasiTimer.h \
           CKeyFactory.h \
           COutputAssistant.h \  
           CRenameHandler.h \
           CReportDefinition.h \
           CReportDefinitionVector.h \
           CReport.h 

SOURCES += CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
           CCopasiStaticString.cpp \
           CCopasiTimer.cpp \
           CKeyFactory.cpp \
           COutputAssistant.cpp \  
           CReportDefinition.cpp \
           CReportDefinitionVector.cpp \
           CReport.cpp 

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


DISTFILES += report.dsp
