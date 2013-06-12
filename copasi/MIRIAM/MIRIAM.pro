# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = MIRIAM

DISTFILES = MIRIAM.pro
DISTFILES += MIRIAMResources.xml

CONFIG -= qt

DEPENDPATH += ..
INCLUDEPATH += ..

!win32:{
  QMAKE_CFLAGS_WARN_ON += -Wno-unused-parameter 
  QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter 
}

# Input
HEADERS += CBiologicalDescription.h
HEADERS += CCreator.h
HEADERS += CConstants.h
HEADERS += CMIRIAMResource.h
HEADERS += CModelMIRIAMInfo.h
HEADERS += CModified.h
HEADERS += CReference.h
HEADERS += CRaptorInit.h
HEADERS += CRDFGraph.h
HEADERS += CRDFGraphConverter.h
HEADERS += CRDFLiteral.h
HEADERS += CRDFNode.h
HEADERS += CRDFObject.h
HEADERS += CRDFParser.h
HEADERS += CRDFPredicate.h
HEADERS += CRDFSubject.h
HEADERS += CRDFTriplet.h
HEADERS += CRDFUtilities.h
HEADERS += CRDFWriter.h
HEADERS += WebServicesIssues/stdsoap2.h
HEADERS += WebServicesIssues/soapStub.h
HEADERS += WebServicesIssues/soapH.h
HEADERS += WebServicesIssues/soapMiriamWebServicesSoapBindingProxy.h
HEADERS += WebServicesIssues/MiriamWebServicesSoapBinding.nsmap

SOURCES += CBiologicalDescription.cpp
SOURCES += CCreator.cpp
SOURCES += CConstants.cpp
SOURCES += CMIRIAMResource.cpp
SOURCES += CModelMIRIAMInfo.cpp
SOURCES += CModified.cpp
SOURCES += CReference.cpp
SOURCES += CRaptorInit.cpp
SOURCES += CRDFGraph.cpp
SOURCES += CRDFGraphConverter.cpp
SOURCES += CRDFLiteral.cpp
SOURCES += CRDFNode.cpp
SOURCES += CRDFObject.cpp
SOURCES += CRDFParser.cpp
SOURCES += CRDFPredicate.cpp
SOURCES += CRDFSubject.cpp
SOURCES += CRDFTriplet.cpp
SOURCES += CRDFUtilities.cpp
SOURCES += CRDFWriter.cpp
SOURCES += WebServicesIssues/soapC.cpp
SOURCES += WebServicesIssues/soapMiriamWebServicesSoapBindingProxy.cpp
SOURCES += WebServicesIssues/stdsoap2.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
