######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:17:59 $  
######################################################################

LIB = optimization
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
