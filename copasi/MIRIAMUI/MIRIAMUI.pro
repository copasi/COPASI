# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: aekamal $ 
#   $Date: 2008/01/29 16:44:16 $ 
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
		CAuthorsWidget.h \
        CMIRIAMModelWidget.h \
		CRDFListView.h \
		CRDFListViewItem.h 
		

SOURCES += \
		CAuthorsWidget.cpp \
        CMIRIAMModelWidget.cpp \
		CRDFListView.cpp \
		CRDFListViewItem.cpp

FORMS    = CQRDFListViewWidget.ui
