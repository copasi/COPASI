######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2004/11/04 01:01:43 $  
######################################################################

LIB = optimization

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += COptMethod.h \
           COptProblem.h \
           CRandomSearch.h \
           CRandomSearchMaster.h \
	   COptMethodSA.h \
           CRealProblem.h \
	   COptFunction.h
           
SOURCES += COptMethod.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           CRandomSearchMaster.cpp \
	   COptMethodSA.cpp \
           CRealProblem.cpp \
	   COptFunction.cpp
