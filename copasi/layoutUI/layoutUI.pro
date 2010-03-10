# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $
#   $Revision: 1.32 $
#   $Name:  $
#   $Author: gauges $
#   $Date: 2010/03/10 12:33:51 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

LIB = layoutUI

include(../lib.pri)
# qt has to be set after lib.pri is included because lib.pri unsets it 

# qt has to be set before common.pri is included,
# otherwise the qwt includes will not be set correctly

CONFIG += qt
include(../common.pri)


QT +=  opengl 

HEADERS = CQGLNetworkPainter.h \
          CArrow.h \
          CCompartmentGraphNode.h \
          CGraphNode.h \
          CGraphCurve.h \
          CQGLViewport.h \
          CQLayoutMainWindow.h \
          CQPlayerControlWidget.h \
          CSimSummaryInfo.h \
          CDataEntity.h \
          CVisParameters.h \
          CQCurrentValueTable.h \
          BezierCurve.h \
          FontChooser.h \
          ParaPanel.h \
          NodeSizePanel.h \
          RGTextureSpec.h \
          CLabel.h

contains(DEFINES,USE_CRENDER_EXTENSION) {           
HEADERS += CQFontRenderer.h \
           CQGLLayoutPainter.h \
	   CQGLLayoutViewer.h \
	   CQNewMainWindow.h \
           CQQtImageTexturizer.h \
           CQScreenshotOptionsDialog.h
}

SOURCES = CQLayoutMainWindow.cpp \
          CArrow.cpp \
          CCompartmentGraphNode.cpp \
          CGraphNode.cpp \
          CGraphCurve.cpp \
          CQGLNetworkPainter.cpp \
          CQPlayerControlWidget.cpp \
          CSimSummaryInfo.cpp \
          CDataEntity.cpp \
          CVisParameters.cpp \
          CQCurrentValueTable.cpp \
          CQGLViewport.cpp \
          BezierCurve.cpp \
          FontChooser.cpp \
          ParaPanel.cpp \
          NodeSizePanel.cpp \
          RGTextureSpec.cpp \
          CLabel.cpp

contains(DEFINES,USE_CRENDER_EXTENSION) {           
SOURCES += CQFontRenderer.cpp \
           CQGLLayoutPainter.cpp \
	   CQGLLayoutViewer.cpp \
	   CQNewMainWindow.cpp \
           CQQtImageTexturizer.cpp \
           CQScreenshotOptionsDialog.cpp
}



FORMS = ParaPanel.ui \
        NodeSizePanel.ui \
        FontChooser.ui


contains(DEFINES,USE_CRENDER_EXTENSION) {           
FORMS += CQScreenshotDialog.ui 
}



#INCLUDEPATH += $${QWT_PATH}/include/qwt-qt4
INCLUDEPATH += $${QWT_PATH}/include/

DISTFILES += layoutUI.vcproj

