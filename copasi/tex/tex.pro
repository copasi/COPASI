# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/tex.pro,v $ 
#   $Revision: 1.4.2.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/11/13 14:53:15 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

LIB = tex

# Input
HEADERS += CMathMLToTeX.h \
	   CStructureParser.h
SOURCES += CMathMLToTeX.cpp \
	   CStructureParser.cpp

include(../lib.pri)

CONFIG += qt 

include(../common.pri)
include(../srcDistribution.pri)

#The following line was inserted by qt3to4
QT += xml
