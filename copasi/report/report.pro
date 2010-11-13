# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/report.pro,v $ 
#   $Revision: 1.23.2.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/11/13 16:55:59 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.23.2.2 $ $Author: shoops $ $Date: 2010/11/13 16:55:59 $
######################################################################

LIB = report
DISTFILES = report.pro

# Input
HEADERS += ArtisticLicense.h \
           CArrayElementReference.h \
           CCopasiArray.h \
           CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiObjectReference.h \
           CCopasiRootContainer.h \
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
           CCopasiRootContainer.cpp \
           CCopasiStaticString.cpp \
           CCopasiTimer.cpp \
           CKeyFactory.cpp \
           COutputAssistant.cpp \
           CReportDefinition.cpp \
           CReportDefinitionVector.cpp \
           CReport.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
