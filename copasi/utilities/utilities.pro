######################################################################
# $Revision: 1.11 $ $Author: shoops $ $Date: 2005/03/30 22:10:16 $  
######################################################################

LIB = utilities

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CAnnotatedMatrix.h \
           CCopasiCallBack.h \
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
           CIndexedPriorityQueue.h \
           CluX.h \
           CMatrix.h \
           COutputHandler.h \
           CReadConfig.h \
           CSlider.h \
#           CSparseMatrix.h \
#           CSparseVector.h \
           CopasiTime.h \
           CVector.h \
           CVersion.h \
           messages.h \
           utility.h

SOURCES += CAnnotatedMatrix.cpp \
           CCopasiCallBack.cpp \
           CCopasiException.cpp \
           CCopasiMessage.cpp \
           CCopasiMethod.cpp \
           CCopasiParameter.cpp \
           CCopasiParameterGroup.cpp \
           CCopasiProblem.cpp \
           CCopasiTask.cpp \
           CDependencyGraph.cpp \
           CIndexedPriorityQueue.cpp \
           COutputHandler.cpp \
           CReadConfig.cpp \
           CSlider.cpp \
#           CSparseMatrix.cpp \
#           CSparseVector.cpp \
           CopasiTime.cpp \
           CVersion.cpp \
           utility.cpp
