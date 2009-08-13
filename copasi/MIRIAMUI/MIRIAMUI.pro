# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $
#   $Revision: 1.19 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2009/08/13 01:40:02 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

LIB = MIRIAMUI

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS += CQMiriamWidget.h
HEADERS += CQCreatorDM.h
HEADERS += CQReferenceDM.h
HEADERS += CQBiologicalDescriptionDM.h
HEADERS += CQModifiedDM.h
HEADERS += CQRDFTreeView.h
HEADERS += CQRDFTreeViewItem.h


SOURCES += CQMiriamWidget.cpp
SOURCES += CQCreatorDM.cpp
SOURCES += CQReferenceDM.cpp
SOURCES += CQBiologicalDescriptionDM.cpp
SOURCES += CQModifiedDM.cpp
SOURCES += CQRDFTreeView.cpp
SOURCES += CQRDFTreeViewItem.cpp
		
FORMS   += CQMiriamWidget.ui
FORMS   += CQRDFTreeView.ui

DISTFILES += MIRIAMUI.vcproj

#The following line was inserted by qt3to4
QT +=  opengl qt3support 


