######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2006/06/20 13:17:02 $  
######################################################################

LIB = copasiDM
SRC_TARGET = CopasiDataModel

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCopasiDataModel.h

SOURCES += CCopasiDataModel.cpp

DISTFILES += CopasiDataModel.dsp
