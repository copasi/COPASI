######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2006/10/30 21:12:14 $  
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
