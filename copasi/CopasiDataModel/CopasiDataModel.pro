######################################################################
# $Revision: 1.1.12.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:51 $  
######################################################################

LIB = copasiDM
SRC_TARGET = CopasiDataModel

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCopasiDataModel.h

SOURCES += CCopasiDataModel.cpp

DISTFILES += CopasiDataModel.dsp
