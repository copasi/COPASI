# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/optimization.pro,v $ 
#   $Revision: 1.31 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/12/11 21:46:07 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.31 $ $Author: shoops $ $Date: 2007/12/11 21:46:07 $  
######################################################################

LIB = optimization

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += COptItem.h \
           COptMethod.h \
           COptMethodEP.h \
           COptMethodGA.h \
           COptMethodGASR.h \
           COptMethodHookeJeeves.h \
           COptMethodLevenbergMarquardt.h \
           COptMethodNelderMead.h \
           COptMethodPraxis.h \
           COptMethodPS.h \
           COptMethodSA.h \
           COptMethodSRES.h \
           COptMethodSteepestDescent.h \
           COptMethodStatistics.h \
           COptMethodTruncatedNewton.h \
           COptProblem.h \
           COptTask.h \
           CPraxis.h \
           CRandomSearch.h \
           CTruncatedNewton.h \
           FminBrent.h
           
SOURCES += COptItem.cpp \
           COptMethod.cpp \
           COptMethodEP.cpp \
           COptMethodGA.cpp \
           COptMethodGASR.cpp \
           COptMethodHookeJeeves.cpp \
           COptMethodLevenbergMarquardt.cpp \
           COptMethodNelderMead.cpp \
           COptMethodPraxis.cpp \
           COptMethodPS.cpp \
           COptMethodSA.cpp \
           COptMethodSRES.cpp \
           COptMethodSteepestDescent.cpp \
           COptMethodStatistics.cpp \
           COptMethodTruncatedNewton.cpp \
           COptProblem.cpp \
           COptTask.cpp \
           CPraxis.cpp \
           CRandomSearch.cpp \
           CTruncatedNewton.cpp \
           FminBrent.cpp

DISTFILES += optimization.dsp
