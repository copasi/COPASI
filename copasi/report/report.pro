# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/report.pro,v $ 
#   $Revision: 1.18 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2008/09/22 22:15:32 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.18 $ $Author: ssahle $ $Date: 2008/09/22 22:15:32 $
######################################################################

LIB = report

include(../lib.pri)
include(../common.pri)

# Input
HEADERS +=  CArrayElementReference.h \
           CCopasiArray.h \
           CCopasiContainer.h \
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

SOURCES += CArrayElementReference.cpp \
           CCopasiArray.cpp \
           CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
           CCopasiStaticString.cpp \
           CCopasiTimer.cpp \
           CKeyFactory.cpp \
           COutputAssistant.cpp \
           CReportDefinition.cpp \
           CReportDefinitionVector.cpp \
           CReport.cpp


DISTFILES += report.vcproj
