######################################################################
# $Revision: 1.5 $ $Author: lixu1 $ $Date: 2003/08/13 16:06:45 $  
######################################################################

LIB = report
include(../lib.pri)

# Input
HEADERS += CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiObjectReference.h \
		   CReportDefinition.h \
		   CReportDefinitionVector.h \
		   CKeyFactory.h \
		   CReport.h \
		   CReportBody.h

SOURCES += CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
		   CReportDefinition.cpp \
		   CReportDefinitionVector.cpp \
	       CKeyFactory.cpp \
		   CReport.cpp \
		   CReportBody.cpp 
