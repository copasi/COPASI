######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2003/07/02 14:28:30 $  
######################################################################

LIB = xml
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
