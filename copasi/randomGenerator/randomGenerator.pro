######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:18:00 $  
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
