######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2005/02/08 16:33:05 $  
######################################################################

LIB = xml

include(../lib.pri)
include(../common.pri)

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
