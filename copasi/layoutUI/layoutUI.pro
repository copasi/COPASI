# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $ 
#   $Revision: 1.17 $ 
#   $Name:  $ 
#   $Author: urost $ 
#   $Date: 2007/10/04 17:21:41 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = layoutUI

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS = CQGLNetworkPainter.h \
          CArrow.h \
          CGraphNode.h \
          CGraphCurve.h \
          CQLayoutMainWindow.h \
          CSimSummaryInfo.h \
          CDataEntity.h \
          CVisParameters.h \
          CQCopasiLayoutWidget.h \
          BezierCurve.h \ 
          RGTextureSpec.h


SOURCES = CQLayoutMainWindow.cpp \
          CArrow.cpp \
          CGraphNode.cpp \
          CGraphCurve.cpp \
          CQGLNetworkPainter.cpp \
          CSimSummaryInfo.cpp \
          CDataEntity.cpp \
          CVisParameters.cpp \
          CQCopasiLayoutWidget.cpp \
          BezierCurve.cpp \
          RGTextureSpec.cpp



FORMS = ParaPanel.ui \
        NodeSizePanel.ui

       # CQCopasiLayoutWidget.ui

INCLUDEPATH += $${QWT_PATH}/include
