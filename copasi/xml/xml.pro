######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2006/06/20 13:20:40 $  
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
