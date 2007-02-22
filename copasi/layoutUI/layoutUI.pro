# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/layoutUI.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: urost $ 
#   $Date: 2007/02/22 17:30:44 $ 
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


INCLUDEPATH += /usr/local/include/freetype2
INCLUDEPATH += /usr/local/include/freetype2/freetype
INCLUDEPATH += /usr/local/include/freetype2/freetype/config
LIBS += -L /usr/lib -L/usr/local/lib  -lfreetype -lglut


CONFIG += qt opengl freetype
DEFINES += GL_GLEXT_PROTOTYPES


