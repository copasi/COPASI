# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = layoutUI
DISTFILES = layoutUI.pro

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
          CQLayoutThread.h \
          BezierCurve.h \
          FontChooser.h \
          ParaPanel.h \
          NodeSizePanel.h \
          RGTextureSpec.h \
          CLabel.h

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
          CQLayoutThread.cpp \
          CQGLViewport.cpp \
          BezierCurve.cpp \
          FontChooser.cpp \
          ParaPanel.cpp \
          NodeSizePanel.cpp \
          RGTextureSpec.cpp \
          CLabel.cpp


FORMS = ParaPanel.ui \
        NodeSizePanel.ui \
        FontChooser.ui

DISTFILES += load_data.xpm \
             play.xpm \
             stop.xpm \
             pause.xpm \
             forward.xpm \
             backward.xpm \
             forward_single.xpm \
             backward_single.xpm \
             revert_curve.xpm  \
             film_strip.xpm \
             graph.xpm

include(../lib.pri)

CONFIG += qt

include(../common.pri)

contains(DEFINES,USE_CRENDER_EXTENSION) {           
HEADERS += CQFontRenderer.h \
           CQGLLayoutPainter.h \
	   CQGLLayoutViewer.h \
	   CQNewMainWindow.h \
           CQQtImageTexturizer.h \
           CQScreenshotOptionsDialog.h
}

contains(DEFINES,COPASI_AUTOLAYOUT) {
HEADERS += CQAutolayoutWizard.h \
           CQSpringLayoutParameterWindow.h


DISTFILES += layout_start.xpm
DISTFILES += layout_stop.xpm
}


contains(DEFINES,USE_CRENDER_EXTENSION) {           
SOURCES += CQFontRenderer.cpp \
           CQGLLayoutPainter.cpp \
	   CQGLLayoutViewer.cpp \
	   CQNewMainWindow.cpp \
           CQQtImageTexturizer.cpp \
           CQScreenshotOptionsDialog.cpp
}

contains(DEFINES,COPASI_AUTOLAYOUT) {
SOURCES += CQAutolayoutWizard.cpp \
           CQSpringLayoutParameterWindow.cpp

}



contains(DEFINES,USE_CRENDER_EXTENSION) {           
FORMS += CQScreenshotDialog.ui 
}

include(../srcDistribution.pri)
