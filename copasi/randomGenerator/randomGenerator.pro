######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2005/02/08 16:33:04 $  
######################################################################

LIB = randomGenerator

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += Cmt19937.h \
           Cr250.h \
           CRandom.h
           
SOURCES += Cmt19937.cpp \
           Cr250.cpp \
           CRandom.cpp
