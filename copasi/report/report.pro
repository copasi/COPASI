######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:18:01 $  
######################################################################

LIB = report
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
