######################################################################
# $Revision: 1.13 $ $Author: shoops $ $Date: 2005/10/13 13:12:49 $  
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
