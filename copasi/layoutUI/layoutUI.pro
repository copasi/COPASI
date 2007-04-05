# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $ 
#   $Revision: 1.4 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/04/05 16:32:38 $ 
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
          CGraphNode.h \
          CQGLNetworkPainter.cpp




