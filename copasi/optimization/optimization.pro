######################################################################
# $Revision: 1.3 $ $Author: lixu1 $ $Date: 2003/09/23 04:07:43 $  
######################################################################

LIB = optimization
include(../lib.pri)

# Input
HEADERS += COptMethod.h \
           COptProblem.h \
           CRandomSearch.h \
           CRandomSearchMaster.h \
           CRealProblem.h \
		   CExpression.h
           
SOURCES += COptMethod.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           CRandomSearchMaster.cpp \
           CRealProblem.cpp \
		   CExpression.cpp
