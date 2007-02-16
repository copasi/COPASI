# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/layout.pro,v $ 
#   $Revision: 1.4 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/02/16 16:56:07 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = layout

include(../lib.pri)
include(../common.pri)

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

