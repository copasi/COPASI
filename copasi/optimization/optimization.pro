######################################################################
# $Revision: 1.24 $ $Author: shoops $ $Date: 2006/08/31 16:50:34 $  
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
           COptMethodSA.h \
           COptMethodSRES.h \
           COptMethodSteepestDescent.h \
           COptMethodStatistics.h \
           COptMethodEP.h \
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
           COptMethodSA.cpp \
           COptMethodSRES.cpp \
           COptMethodSteepestDescent.cpp \
           COptMethodStatistics.cpp \
           COptMethodEP.cpp \
           COptTask.cpp \
           COptItem.cpp \
           FminBrent.cpp

DISTFILES += optimization.dsp
