######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sun May 18 11:05:59 2003
######################################################################

LIB = optimization
include(../lib.pri)

# Input
HEADERS += COptMethod.h \
           COptProblem.h \
           CRandomSearch.h \
           CRandomSearchMaster.h \
           CRealProblem.h
           
SOURCES += COptMethod.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           CRandomSearchMaster.cpp \
           CRealProblem.cpp
