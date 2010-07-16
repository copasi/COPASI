# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $
#   $Revision: 1.21 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/07/16 19:01:00 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

LIB = MIRIAMUI

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

include(../lib.pri)

CONFIG += qt

include(../common.pri)

QT += qt3support
