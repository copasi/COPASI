######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2004/11/04 01:01:42 $  
######################################################################

LIB = report

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiStaticString.h \
           CCopasiObjectReference.h \
		   CReportDefinition.h \
		   CReportDefinitionVector.h \
		   CKeyFactory.h \
		   CReport.h 
		#   CReportBody.h

SOURCES += CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
           CCopasiStaticString.cpp \
		   CReportDefinition.cpp \
		   CReportDefinitionVector.cpp \
	       CKeyFactory.cpp \
		   CReport.cpp 
		#   CReportBody.cpp 
