######################################################################
# $Revision: 1.11 $ $Author: shoops $ $Date: 2005/06/29 20:24:22 $  
######################################################################

LIB = report

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiObjectReference.h \
           CCopasiStaticString.h \
           CCopasiTimer.h \
		       CKeyFactory.h \
           CRenameHandler.h \
		       CReportDefinition.h \
		       CReportDefinitionVector.h \
		       CReport.h 
		#   CReportBody.h

SOURCES += CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
           CCopasiStaticString.cpp \
           CCopasiTimer.cpp \
		       CKeyFactory.cpp \
		       CReportDefinition.cpp \
		       CReportDefinitionVector.cpp \
		       CReport.cpp 
		#   CReportBody.cpp 
