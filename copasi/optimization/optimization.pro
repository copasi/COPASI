######################################################################
# $Revision: 1.18 $ $Author: shoops $ $Date: 2005/12/06 20:03:11 $  
######################################################################

LIB = optimization

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += COptMethod.h \
#           COptMethodEP2.h \
           COptMethodGA.h \
           COptMethodHookeJeeves.h \
#           COptMethodHGASA.h \
#           COptMethodSA.h \
           COptProblem.h \
           CRandomSearch.h \
           COptMethodGASR.h \
           COptMethodSteepestDescent.h \
		       COptMethodEP.h \
#           CRandomSearchMaster.h \
           CRealProblem.h \
           COptFunction.h \
           COptTask.h \ 
           COptItem.h \
           FminBrent.h
           
SOURCES += COptMethod.cpp \
#           COptMethodEP2.cpp \
           COptMethodGA.cpp \
           COptMethodHookeJeeves.cpp \
#           COptMethodHGASA.cpp \
#           COptMethodSA.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           COptMethodGASR.cpp \
           COptMethodSteepestDescent.cpp \
		       COptMethodEP.cpp \
#           CRandomSearchMaster.cpp \
           CRealProblem.cpp \
           COptFunction.cpp \
           COptTask.cpp \
           COptItem.cpp \
           FminBrent.cpp
