######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2003/05/19 00:39:53 $  
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
