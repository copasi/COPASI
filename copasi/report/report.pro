######################################################################
# $RCSfile: report.pro,v $ $Revision: 1.1 $ 
# Commited by: $Author: shoops $ ($Date: 2003/05/18 20:09:38 $) 
######################################################################

LIB = report

include(../lib.pri)

# Input
HEADERS += CCopasiContainer.h \
           CCopasiObject.h \
           CCopasiObjectName.h \
           CCopasiObjectReference.h \
           CKeyFactory.h

SOURCES += CCopasiContainer.cpp \
           CCopasiObject.cpp \
           CCopasiObjectName.cpp \
           CKeyFactory.cpp
