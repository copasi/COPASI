######################################################################
# $Revision: 1.5 $ $Author: djchen $ $Date: 2003/10/10 13:34:31 $  
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
