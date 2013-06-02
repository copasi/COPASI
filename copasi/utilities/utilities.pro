# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.29 $ $Author: shoops $ $Date: 2012/05/11 16:52:15 $
######################################################################

LIB = utilities
DISTFILES = utilities.pro

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
           CLinkMatrix.h \
           CluX.h \
           CMatrix.h \
           CNodeIterator.h \
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
           CLinkMatrix.cpp \
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

copasi_version.target = ../CopasiVersion.h
copasi_version.depends = ../CopasiVersion.h.in
win32:{
    (if exist $${BUILD_ROOT}/gitTools/UpdateCopasiVersion C:/cygwin/bin/bash $${BUILD_ROOT}/gitTools/UpdateCopasiVersion) \
    (if not exist CopasiVersion.h $(COPY_FILE) CopasiVersion.h.in CopasiVersion.h)
} else {
  copasi_version.commands = \
    test -e $${BUILD_ROOT}/gitTools/UpdateCopasiVersion && $${BUILD_ROOT}/gitTools/UpdateCopasiVersion; \
    test -e ../CopasiVersion.h || $(COPY_FILE) ../CopasiVersion.h.in ../CopasiVersion.h
}

QMAKE_EXTRA_TARGETS += copasi_version

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)

