######################################################################
# $Revision: 1.5 $ $Author: ssahle $ $Date: 2004/08/31 12:21:14 $  
######################################################################

LIB = utilities
include(../lib.pri)

# Input
HEADERS += CCopasiException.h \
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
           CGlobals.h \
           CIndexedPriorityQueue.h \
           CluX.h \
           CMatrix.h \
           COutputHandler.h \
           CReadConfig.h \
           CopasiTime.h \
           CVector.h \
           CVersion.h \
           messages.h \
           utility.h

SOURCES += CCopasiException.cpp \
           CCopasiMessage.cpp \
           CCopasiMethod.cpp \
           CCopasiParameter.cpp \
           CCopasiParameterGroup.cpp \
           CCopasiProblem.cpp \
           CCopasiTask.cpp \
           CDependencyGraph.cpp \
           CGlobals.cpp \
           CIndexedPriorityQueue.cpp \
           COutputHandler.cpp \
           CReadConfig.cpp \
           CopasiTime.cpp \
           CVersion.cpp \
           utility.cpp
