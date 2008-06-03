# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $ 
#   $Revision: 1.7 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/06/03 13:21:21 $ 
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

FORMS    = CQRDFListViewWidget.ui
FORMS   += CQMiriamWidget.ui
