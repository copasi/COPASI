# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: urost $ 
#   $Date: 2007/04/12 17:33:49 $ 
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
          CQLayoutMainWindow.h


SOURCES = CQLayoutMainWindow.cpp \
          CArrow.cpp \
          CGraphNode.cpp \
          CQGLNetworkPainter.cpp




