######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2006/10/30 21:12:17 $  
######################################################################

LIB = mathmodel

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CMathConstant.h \
           CMathEq.h \
           CMathModel.h \
           CMathNode.h \
           CMathSymbol.h \
           CMathVariable.h
           
SOURCES += CMathConstant.cpp \
           CMathEq.cpp \
           CMathModel.cpp \
           CMathNode.cpp \
           CMathSymbol.cpp \
           CMathVariable.cpp
  
DISTFILES += mathmodel.dsp
