# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/elementaryFluxModes.pro,v $
#   $Revision: 1.11 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/12/18 17:30:00 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sat May 17 20:42:30 2003
######################################################################

LIB = elementaryFluxModes

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CEFMAlgorithm.h \
           CEFMMethod.h \
           CEFMProblem.h \
           CEFMTask.h \
           CFluxMode.h \
           CFluxScore.h \
           CTableauLine.h \
           CTableauMatrix.h

contains(DEFINES, COPASI_SSA) {
   HEADERS += CSSAMethod.h
}

SOURCES += CEFMAlgorithm.cpp \
           CEFMMethod.cpp \
           CEFMProblem.cpp \
           CEFMTask.cpp \
           CFluxMode.cpp \
           CFluxScore.cpp \
           CTableauLine.cpp \
           CTableauMatrix.cpp

contains(DEFINES, COPASI_SSA) {
   SOURCES += CSSAMethod.cpp
}

DISTFILES += elementaryFluxModes.vcproj
#The following line was inserted by qt3to4
QT +=  qt3support 
