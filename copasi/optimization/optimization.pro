######################################################################
# $Revision: 1.9 $ $Author: chlee $ $Date: 2005/01/24 16:10:26 $  
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
		   COptTask.h \ 
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
		   COptTask.cpp \
           COptItem.cpp
