######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:17:57 $  
######################################################################

LIB = mathmodel
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
