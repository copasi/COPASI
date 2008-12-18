# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $
#   $Revision: 1.26 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/12/18 17:41:15 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
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
          RGTextureSpec.cpp \
          CLabel.cpp



#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3 = ParaPanel.ui \
        NodeSizePanel.ui \
        FontChooser.ui

       # CQCopasiLayoutWidget.ui

INCLUDEPATH += $${QWT_PATH}/include/

DISTFILES += layoutUI.vcproj
#The following line was inserted by qt3to4
QT +=  opengl qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3

