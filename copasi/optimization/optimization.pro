######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2005/01/06 17:10:20 $  
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
           COptFunction.h \
           COptItem.h
           
SOURCES += COptMethod.cpp \
           COptMethodEP2.cpp \
           COptMethodGA.cpp \
           COptMethodHGASA.cpp \
           COptMethodSA.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           CRandomSearchMaster.cpp \
           CRealProblem.cpp \
           COptFunction.cpp \
           COptItem.cpp
