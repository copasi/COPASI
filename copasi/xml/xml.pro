######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2003/05/19 00:39:55 $  
######################################################################

LIB = xml
include(../lib.pri)


# Input
HEADERS += CCopasiXML.h \
           CCopasiXMLInterface.h \
           CExpat.h

SOURCES += CCopasiXML.cpp \
           CCopasiXMLInterface.cpp \
           CExpat.cpp
