######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2003/05/19 12:45:54 $  
######################################################################

LIB = xml
include(../lib.pri)

TARGET = copasiXML

# Input
HEADERS += CCopasiXML.h \
           CCopasiXMLInterface.h \
           CExpat.h

SOURCES += CCopasiXML.cpp \
           CCopasiXMLInterface.cpp \
           CExpat.cpp
