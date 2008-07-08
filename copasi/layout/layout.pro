# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/layout.pro,v $
#   $Revision: 1.5 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/07/08 16:06:26 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
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


DISTFILES += layout.vcproj

