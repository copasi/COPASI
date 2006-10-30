######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2006/10/30 21:12:19 $  
######################################################################

LIB = copasiDM
SRC_TARGET = CopasiDataModel

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCopasiDataModel.h

SOURCES += CCopasiDataModel.cpp


DISTFILES += CopasiDataModel.dsp
