######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2004/11/04 01:01:42 $  
######################################################################

LIB = randomGenerator

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += Cmt19937.h \
           Cr250.h \
           CRandom.h
           
SOURCES += Cmt19937.cpp \
           Cr250.cpp \
           CRandom.cpp
