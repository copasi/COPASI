######################################################################
# $Revision: 1.4 $ $Author: lixu1 $ $Date: 2003/09/30 01:15:26 $  
######################################################################

LIB = optimization
include(../lib.pri)

# Input
HEADERS += COptMethod.h \
           COptProblem.h \
           CRandomSearch.h \
           CRandomSearchMaster.h \
           CRealProblem.h \
		   COptFunction.h
           
SOURCES += COptMethod.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           CRandomSearchMaster.cpp \
           CRealProblem.cpp \
		   COptFunction.cpp
