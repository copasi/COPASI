######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sun May 18 11:13:31 2003
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
