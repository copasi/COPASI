######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2004/11/18 20:29:28 $  
######################################################################

LIB = optimization

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += COptMethod.h \
           COptMethodEP2.h \
           COptMethodGA.h \
           COptMethodHGASA.h \
           COptMethodSA.h \
           COptProblem.h \
           CRandomSearch.h \
           CRandomSearchMaster.h \
           CRealProblem.h \
           COptFunction.h
           
SOURCES += COptMethod.cpp \
           COptMethodEP2.cpp \
           COptMethodGA.cpp \
           COptMethodHGASA.cpp \
           COptMethodSA.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           CRandomSearchMaster.cpp \
           CRealProblem.cpp \
           COptFunction.cpp
