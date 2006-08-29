######################################################################
# $Revision: 1.23 $ $Author: shoops $ $Date: 2006/08/29 13:38:55 $  
######################################################################

LIB = optimization

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += COptMethod.h \
           COptMethodGA.h \
           COptMethodHookeJeeves.h \
           COptProblem.h \
           CRandomSearch.h \
           COptMethodGASR.h \
           COptMethodLevenbergMarquardt.h \
           COptMethodNelderMead.h \
           COptMethodSRES.h \
           COptMethodSteepestDescent.h \
           COptMethodStatistics.h \
           COptMethodEP.h \
           CRealProblem.h \
           COptFunction.h \
           COptTask.h \ 
           COptItem.h \
           FminBrent.h
           
SOURCES += COptMethod.cpp \
           COptMethodGA.cpp \
           COptMethodHookeJeeves.cpp \
           COptProblem.cpp \
           CRandomSearch.cpp \
           COptMethodGASR.cpp \
           COptMethodLevenbergMarquardt.cpp \
           COptMethodNelderMead.cpp \
           COptMethodSRES.cpp \
           COptMethodSteepestDescent.cpp \
           COptMethodStatistics.cpp \
           COptMethodEP.cpp \
           CRealProblem.cpp \
           COptFunction.cpp \
           COptTask.cpp \
           COptItem.cpp \
           FminBrent.cpp

DISTFILES += optimization.dsp
