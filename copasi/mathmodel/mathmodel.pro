######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2005/02/08 16:33:04 $  
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
