######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2003/05/19 00:39:51 $  
######################################################################

LIB = utilities
include(../lib.pri)

# Input
HEADERS += CCopasiException.h \
           CCopasiMessage.h \
           CCopasiNode.h \
           CCopasiTree.h \
           CCopasiVector.h \
           CDependencyGraph.h \
           CGlobals.h \
           CIndexedPriorityQueue.h \
           CluX.h \
           CMatrix.h \
           CMethodParameter.h \
           CMethodParameterList.h \
           CReadConfig.h \
           CVector.h \
           CVersion.h \
           CWriteConfig.h \
           messages.h \
           readwrite.h \
           utility.h

SOURCES += CCopasiException.cpp \
           CCopasiMessage.cpp \
           CDependencyGraph.cpp \
           CGlobals.cpp \
           CIndexedPriorityQueue.cpp \
           CMethodParameter.cpp \
           CMethodParameterList.cpp \
           CReadConfig.cpp \
           CVersion.cpp \
           CWriteConfig.cpp \
           utility.cpp
