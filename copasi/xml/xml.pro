######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:18:06 $  
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
