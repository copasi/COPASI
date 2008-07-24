# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/tex.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: pwilly $ 
#   $Date: 2008/07/24 10:58:00 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

LIB = tex

include(../lib.pri)
include(../common.pri)

CONFIG += qt 

# Input
HEADERS += CMathMLToTeX.h \
	   CStructureParser.h
SOURCES += CMathMLToTeX.cpp \
	   CStructureParser.cpp

DISTFILES += TeX.dsp
