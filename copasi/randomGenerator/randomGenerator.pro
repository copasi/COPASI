######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2003/05/19 00:39:56 $  
######################################################################

LIB = randomGenerator
include(../lib.pri)

# Input
HEADERS += Cmt19937.h \
           Cr250.h \
           CRandom.h
           
SOURCES += Cmt19937.cpp \
           Cr250.cpp \
           CRandom.cpp
