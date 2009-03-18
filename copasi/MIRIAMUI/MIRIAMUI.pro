# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $
#   $Revision: 1.15 $
#   $Name:  $
#   $Author: pwilly $
#   $Date: 2009/03/18 12:26:31 $
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
		CQMiriamWidget.h \
                ui_CQMiriamWidget.h \
		CQCreatorDM.h \
		CQReferenceDM.h \
		CQBiologicalDescriptionDM.h \		
		CQModifiedDM.h \
		CQDateTimeEditDelegate.h \
		CQComboDelegate.h \		
		CRDFListView.h \
		CRDFListViewItem.h


SOURCES += \
		CQMiriamWidget.cpp \
		CQCreatorDM.cpp \
		CQReferenceDM.cpp \
		CQBiologicalDescriptionDM.cpp \
		CQModifiedDM.cpp \
		CQDateTimeEditDelegate.cpp \
		CQComboDelegate.cpp \
		CRDFListView.cpp \
		CRDFListViewItem.cpp
		
#FORMS   += CQMiriamWidget.ui

#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3    = CQRDFListViewWidget.ui

DISTFILES += MIRIAMUI.vcproj
#The following line was inserted by qt3to4
QT +=  opengl qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3


