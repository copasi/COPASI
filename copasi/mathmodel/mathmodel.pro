######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sat May 17 20:51:56 2003
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
