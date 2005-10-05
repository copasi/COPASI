######################################################################
# $Revision: 1.12 $ $Author: ssahle $ $Date: 2005/10/05 14:07:22 $  
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
           COutputAssistant.h \  
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
           COutputAssistant.cpp \  
		       CReportDefinition.cpp \
		       CReportDefinitionVector.cpp \
		       CReport.cpp 
		#   CReportBody.cpp 
