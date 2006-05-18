######################################################################
# $Revision: 1.4.12.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:56 $  
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

DISTFILES += randomGenerator.dsp
