######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2004/11/04 01:01:42 $  
######################################################################

LIB = xml

include(../common.pri)
include(../lib.pri)

TARGET = copasiXML

# Input
HEADERS += CCopasiXML.h \
           CCopasiXMLInterface.h \
           CExpat.h \
           CXMLHandler.h  \
           CCopasiXMLParser.h

SOURCES += CCopasiXML.cpp \
           CCopasiXMLInterface.cpp \
           CExpat.cpp \
           CCopasiXMLParser.cpp
