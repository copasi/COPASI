# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $
#   $Revision: 1.29 $
#   $Name:  $
#   $Author: gauges $
#   $Date: 2010/02/03 13:54:10 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

LIB = layoutUI

include(../lib.pri)
include(../common.pri)

CONFIG += qt

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



FORMS = ParaPanel.ui \
        NodeSizePanel.ui \
        FontChooser.ui


#INCLUDEPATH += $${QWT_PATH}/include/qwt-qt4
INCLUDEPATH += $${QWT_PATH}/include/

DISTFILES += layoutUI.vcproj

QT +=  opengl 

