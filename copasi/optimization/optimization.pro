######################################################################
# $Revision: 1.15 $ $Author: anuragr $ $Date: 2005/07/20 05:10:15 $  
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
		   FminBrent.h \
		   COptMethodGASR.h \
		   COptMethodSteepestDescent.h \
#           CRandomSearchMaster.h \
           CRealProblem.h \
           COptFunction.h \
           COptTask.h \ 
           COptItem.h \
           FminBrent.h
           
SOURCES += COptMethod.cpp \
#           COptMethodEP2.cpp \
           COptMethodGA.cpp \
#           COptMethodHGASA.cpp \
#           COptMethodSA.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
		   COptMethodGASR.cpp \
		   COptMethodSteepestDescent.cpp \
		   FminBrent.cpp \
#           CRandomSearchMaster.cpp \
           CRealProblem.cpp \
           COptFunction.cpp \
	   COptTask.cpp \
           COptItem.cpp \
           FminBrent.cpp
