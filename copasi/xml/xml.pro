######################################################################
# $Revision: 1.9 $ $Author: shoops $ $Date: 2006/10/30 21:12:09 $  
######################################################################

LIB = xml

include(../lib.pri)
include(../common.pri)

TARGET = copasiXML

# Input
HEADERS += CCopasiXML.h \
           CCopasiXMLInterface.h \
           CCopasiXMLVersion.h \
           CExpat.h \
           CXMLHandler.h  \
           CCopasiXMLParser.h

SOURCES += CCopasiXML.cpp \
           CCopasiXMLInterface.cpp \
           CExpat.cpp \
           CCopasiXMLParser.cpp


DISTFILES += copasi.xsd \
             copasiXML.dsp
