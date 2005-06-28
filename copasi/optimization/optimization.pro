######################################################################
# $Revision: 1.13 $ $Author: anuragr $ $Date: 2005/06/28 20:32:56 $  
######################################################################

LIB = optimization

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += COptMethod.h \
#           COptMethodEP2.h \
           COptMethodGA.h \
#           COptMethodHGASA.h \
#           COptMethodSA.h \
           COptProblem.h \
           CRandomSearch.h \
		   COptMethodGASR.h \
#           CRandomSearchMaster.h \
           CRealProblem.h \
           COptFunction.h \
		   COptTask.h \ 
           COptItem.h
           
SOURCES += COptMethod.cpp \
#           COptMethodEP2.cpp \
           COptMethodGA.cpp \
#           COptMethodHGASA.cpp \
#           COptMethodSA.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
		   COptMethodGASR.cpp \
#           CRandomSearchMaster.cpp \
           CRealProblem.cpp \
           COptFunction.cpp \
		   COptTask.cpp \
           COptItem.cpp
