######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2004/11/04 01:01:43 $  
######################################################################

LIB = mathmodel

include(../common.pri)
include(../lib.pri)

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
