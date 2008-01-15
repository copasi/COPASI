# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/MIRIAM.pro,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/01/15 17:45:38 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
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
HEADERS += CRaptorInit.h
HEADERS += CRDFEdge.h
HEADERS += CRDFGraph.h
HEADERS += CRDFLiteral.h
HEADERS += CRDFNode.h
HEADERS += CRDFObject.h
HEADERS += CRDFParser.h
HEADERS += CRDFSubject.h
HEADERS += CRDFWriter.h

SOURCES += CAuthor.cpp 
SOURCES += CModelMIRIAMInfo.cpp
SOURCES += CRaptorInit.cpp
SOURCES += CRDFEdge.cpp
SOURCES += CRDFGraph.cpp
SOURCES += CRDFLiteral.cpp
SOURCES += CRDFNode.cpp
SOURCES += CRDFObject.cpp
SOURCES += CRDFParser.cpp
SOURCES += CRDFSubject.cpp
SOURCES += CRDFWriter.cpp
