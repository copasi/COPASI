######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2003/06/25 19:00:08 $  
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
           CXMLHandler.cpp \
           CCopasiXMLParser.cpp
