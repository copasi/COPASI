# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/report.pro,v $ 
#   $Revision: 1.17 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/07/08 16:06:31 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.17 $ $Author: shoops $ $Date: 2008/07/08 16:06:31 $
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


DISTFILES += report.vcproj
