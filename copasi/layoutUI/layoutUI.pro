# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/02/26 18:13:10 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = layoutUI

include(../lib.pri)
include(../common.pri)

HEADERS += CQGLNetworkPainter.h
HEADERS += CArrow.h
HEADERS += CQLayoutMainWindow.h


SOURCES = CQLayoutMainWindow.cpp \
 CArrow.cpp \
 CQGLNetworkPainter.cpp


CONFIG += qt


