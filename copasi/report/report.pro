######################################################################
# $Revision: 1.3 $ $Author: msinghal $ $Date: 2003/06/06 19:06:53 $  
######################################################################

LIB = report
include(../lib.pri)

# Input
HEADERS += CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiObjectReference.h \
		   CReportDefinition.h \
		   CKeyFactory.h

SOURCES += CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
		   CReportDefinition.cpp \
	       CKeyFactory.cpp
