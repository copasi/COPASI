######################################################################
# $Revision: 1.9 $ $Author: shoops $ $Date: 2005/02/08 16:33:04 $  
######################################################################

LIB = report

include(../lib.pri)
include(../common.pri)

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
