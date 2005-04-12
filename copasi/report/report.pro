######################################################################
# $Revision: 1.10 $ $Author: ssahle $ $Date: 2005/04/12 15:06:34 $  
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
           CRenameHandler.h \
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
