######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2006/06/20 13:19:50 $  
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
