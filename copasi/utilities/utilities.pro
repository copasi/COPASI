######################################################################
# $Revision: 1.22 $ $Author: gauges $ $Date: 2006/10/15 06:25:29 $  
######################################################################

LIB = utilities

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CAnnotatedMatrix.h \
           CCopasiException.h \
           CCopasiMessage.h \
           CCopasiMethod.h \
           CCopasiNode.h \
           CCopasiParameter.h \
           CCopasiParameterGroup.h \
           CCopasiProblem.h \
           CCopasiTask.h \
           CCopasiTree.h \
           CCopasiVector.h \
           CDependencyGraph.h \
           CDimension.h \
           CDirEntry.h \
           CIndexedPriorityQueue.h \
           CluX.h \
           CMatrix.h \
           copasimathml.h \
           CopasiTime.h \
           COutputHandler.h \
           CProcessReport.h \
           CReadConfig.h \
           CSlider.h \
           CSparseMatrix.h \
           CSort.h \
           CTableCell.h \
           CVector.h \
           CVersion.h \
           messages.h \
           utility.h

SOURCES += CAnnotatedMatrix.cpp \
           CCopasiException.cpp \
           CCopasiMessage.cpp \
           CCopasiMethod.cpp \
           CCopasiParameter.cpp \
           CCopasiParameterGroup.cpp \
           CCopasiProblem.cpp \
           CCopasiTask.cpp \
           CDependencyGraph.cpp \
           CDimension.cpp \
           CDirEntry.cpp \
           CIndexedPriorityQueue.cpp \
           CluX.cpp \
           CopasiTime.cpp \
           COutputHandler.cpp \
           CProcessReport.cpp \
           CReadConfig.cpp \
           CSlider.cpp \
           CSparseMatrix.cpp \
           CTableCell.cpp \
           CVersion.cpp \
           utility.cpp

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


DISTFILES += utilities.dsp
