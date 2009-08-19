# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/elementaryFluxModes.pro,v $
#   $Revision: 1.12 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2009/08/19 01:44:12 $
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
HEADERS += CEFMAlgorithm.h
SOURCES += CEFMAlgorithm.cpp

HEADERS += CEFMMethod.h
SOURCES += CEFMMethod.cpp

HEADERS += CEFMProblem.h
SOURCES += CEFMProblem.cpp

HEADERS += CEFMTask.h
SOURCES += CEFMTask.cpp

HEADERS += CFluxMode.h
SOURCES += CFluxMode.cpp

HEADERS += CFluxScore.h
SOURCES += CFluxScore.cpp

contains(DEFINES, COPASI_SSA) {
   HEADERS += CSSAMethod.h
   SOURCES += CSSAMethod.cpp
}

HEADERS += CTableauLine.h
SOURCES += CTableauLine.cpp

HEADERS += CTableauMatrix.h
SOURCES += CTableauMatrix.cpp

HEADERS += CZeroSet.h
SOURCES += CZeroSet.cpp


DISTFILES += elementaryFluxModes.vcproj
#The following line was inserted by qt3to4
QT +=  qt3support 
