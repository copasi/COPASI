# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $
#   $Revision: 1.10 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2009/01/07 18:59:41 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

LIB = MIRIAMUI

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS += \
		CBiologicalDescriptionsWidget.h \
		CCreatorsWidget.h \
        CModifiedWidget.h \
        CReferencesWidget.h \
		CRDFListView.h \
		CRDFListViewItem.h


SOURCES += \
		CBiologicalDescriptionsWidget.cpp \
		CCreatorsWidget.cpp \
        CModifiedWidget.cpp \
        CReferencesWidget.cpp \
		CRDFListView.cpp \
		CRDFListViewItem.cpp

#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3    = CQRDFListViewWidget.ui
#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3   += CQMiriamWidget.ui

DISTFILES += MIRIAMUI.vcproj
#The following line was inserted by qt3to4
QT +=  opengl qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3

