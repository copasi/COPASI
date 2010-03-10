# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/layout.pro,v $
#   $Revision: 1.7 $
#   $Name:  $
#   $Author: gauges $
#   $Date: 2010/03/10 12:26:12 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

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

contains(DEFINES,USE_CRENDER_EXTENSION) {           
HEADER += CLColorDefinition.h \
           CLDefaultStyles.h \
           CLEllipse.h \
           CLFontRendererBase.h \
           CLGlobalRenderInformation.h \
           CLGlobalStyle.h \
           CLGradientBase.h \
           CLGradientStop.h \
           CLGradientStops.h \
           CLGraphicalPrimitive1D.h \
           CLGraphicalPrimitive2D.h \
           CLGroup.h \
           CLImage.h \
           CLImageTexturizer.h \
           CLLayoutRenderer.h \
           CLLineEnding.h \
           CLLinearGradient.h \
           CLLocalRenderInformation.h \
           CLLocalStyle.h \
           CLPolygon.h \
           CLRadialGradient.h \
           CLRectangle.h \
           CLRelAbsVector.h \
           CLRenderCubicBezier.h \
           CLRenderCurve.h \
           CLRenderFlattener.h \
           CLRenderInformationBase.h \
           CLRenderPoint.h \
           CLRenderResolver.h \
           CLRGBAColor.h \
#           CLSimpleImageTexturizer.h \
           CLStyle.h \
           CLText.h \
           CLTransformation.h \
           CLTransformation2D.h \
           CLUnresolvedReferenceException.h \
	   tga_image.h \
           utility_classes.h
}

SOURCES += CLayout.cpp \
           CLayoutInitializer.cpp \
           CLBase.cpp \
           CLCurve.cpp \
           CLGraphicalObject.cpp \
           CLGlyphs.cpp \
           CListOfLayouts.cpp \
           CLReactionGlyph.cpp \
           SBMLDocumentLoader.cpp

contains(DEFINES,USE_CRENDER_EXTENSION) {
SOURCES += CLColorDefinition.cpp \
           CLDefaultStyles.cpp \
           CLEllipse.cpp \
           CLGlobalRenderInformation.cpp \
           CLGlobalStyle.cpp \
           CLGradientBase.cpp \
           CLGradientStop.cpp \
           CLGradientStops.cpp \
           CLGraphicalPrimitive1D.cpp \
           CLGraphicalPrimitive2D.cpp \
           CLGroup.cpp \
           CLImage.cpp \
           CLImageTexturizer.cpp \
           CLLayoutRenderer.cpp \
           CLLineEnding.cpp \
           CLLinearGradient.cpp \
           CLLocalRenderInformation.cpp \
           CLLocalStyle.cpp \
           CLPolygon.cpp \
           CLRadialGradient.cpp \
           CLRectangle.cpp \
           CLRelAbsVector.cpp \
           CLRenderCubicBezier.cpp \
           CLRenderCurve.cpp \
           CLRenderFlattener.cpp \
           CLRenderInformationBase.cpp \
           CLRenderPoint.cpp \
           CLRenderResolver.cpp \
# this class is only needed if we want to create 
# bitmaps from layouts in the backend
#           CLSimpleImageTexturizer.cpp \
           CLStyle.cpp \
           CLText.cpp \
           CLTransformation.cpp \
           CLTransformation2D.cpp \
           CLUnresolvedReferenceException.cpp \
	   tga_image.cpp \
           utility_classes.cpp
}

DISTFILES += layout.vcproj
