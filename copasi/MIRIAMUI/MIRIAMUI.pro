# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/MIRIAMUI.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/01/22 16:57:34 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

LIB = MIRIAMUI

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS  = CRDFListView.h
HEADERS += CRDFListViewItem.h

SOURCES  = CRDFListView.cpp
SOURCES += CRDFListViewItem.cpp

FORMS    = CQRDFListViewWidget.ui
