# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/MIRIAM.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/11/21 16:15:07 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = MIRIAM

include(../lib.pri)
include(../common.pri)

CONFIG -= qt

DEPENDPATH += .. 
INCLUDEPATH += ..

# Input
HEADERS += CAuthor.h
HEADERS += CModelMIRIAMInfo.h
HEADERS += CRDFEdge.h
HEADERS += CRDFGraph.h
HEADERS += CRDFLiteral.h
HEADERS += CRDFNode.h
HEADERS += CRDFObject.h
HEADERS += CRDFParser.h
HEADERS += CRDFSubject.h

SOURCES += CAuthor.cpp 
SOURCES += CModelMIRIAMInfo.cpp
SOURCES += CRDFEdge.cpp
SOURCES += CRDFGraph.cpp
SOURCES += CRDFLiteral.cpp
SOURCES += CRDFNode.cpp
SOURCES += CRDFObject.cpp
SOURCES += CRDFParser.cpp
SOURCES += CRDFSubject.cpp
