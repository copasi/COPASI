######################################################################
# $Revision: 1.4 $ $Author: lixu1 $ $Date: 2003/08/12 18:33:09 $  
######################################################################

LIB = report
include(../lib.pri)

# Input
HEADERS += CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiObjectReference.h \
		   CReportDefinition.h \
		   CKeyFactory.h \
		   CReport.h \
		   CReportBody.h

SOURCES += CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
		   CReportDefinition.cpp \
	       CKeyFactory.cpp \
		   CReport.cpp \
		   CReportBody.cpp 
