# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $ 
#   $Revision: 1.6 $ 
#   $Name:  $ 
#   $Author: aekamal $ 
#   $Date: 2008/03/10 15:49:57 $ 
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
        CMIRIAMModelWidget.h \
        CModifiedWidget.h \
        CReferencesWidget.h \
		CRDFListView.h \
		CRDFListViewItem.h 
		

SOURCES += \
		CBiologicalDescriptionsWidget.cpp \
		CCreatorsWidget.cpp \
        CMIRIAMModelWidget.cpp \
        CModifiedWidget.cpp \
        CReferencesWidget.cpp \
		CRDFListView.cpp \
		CRDFListViewItem.cpp

FORMS    = CQRDFListViewWidget.ui
