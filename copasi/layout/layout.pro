# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/layout.pro,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2007/02/16 00:10:13 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = layout

include(../lib.pri)
include(../common.pri)

contains(BUILD_OS, WIN32) {
  DEFINES += LIBSBML_STATIC
}

# Input
HEADERS += CLayout.h \
           CLayoutInitializer.h \
           CLBase.h \
           CLCurve.h \
           CLGraphicalObject.h \
           CLGlyphs.h \
           CListOfLayouts.h \
           CLReactionGlyph.h \
           SBMLDocumentLoader.h


SOURCES += CLayout.cpp \
           CLayoutInitializer.cpp \
           CLBase.cpp \
           CLCurve.cpp \
           CLGraphicalObject.cpp \
           CLGlyphs.cpp \
           CListOfLayouts.cpp \
           CLReactionGlyph.cpp \
           SBMLDocumentLoader.cpp


DISTFILES += layout.dsp

