######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2003/10/30 17:59:28 $  
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
           CReadConfig.h \
           CVector.h \
           CVersion.h \
           CWriteConfig.h \
           messages.h \
           readwrite.h \
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
           CReadConfig.cpp \
           CVersion.cpp \
           CWriteConfig.cpp \
           utility.cpp
