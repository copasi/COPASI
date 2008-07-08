# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/utilities.pro,v $ 
#   $Revision: 1.24 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/07/08 16:06:25 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.24 $ $Author: shoops $ $Date: 2008/07/08 16:06:25 $
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


DISTFILES += utilities.vcproj
