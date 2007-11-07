# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/optimization.pro,v $ 
#   $Revision: 1.30 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/11/07 14:10:47 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.30 $ $Author: shoops $ $Date: 2007/11/07 14:10:47 $  
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
           COptMethodPS.h \
           COptMethodSA.h \
           COptMethodSRES.h \
           COptMethodSteepestDescent.h \
           COptMethodStatistics.h \
           COptProblem.h \
           COptTask.h \
           CRandomSearch.h \
           FminBrent.h
           
SOURCES += COptItem.cpp \
           COptMethod.cpp \
           COptMethodEP.cpp \
           COptMethodGA.cpp \
           COptMethodGASR.cpp \
           COptMethodHookeJeeves.cpp \
           COptMethodLevenbergMarquardt.cpp \
           COptMethodNelderMead.cpp \
           COptMethodPS.cpp \
           COptMethodSA.cpp \
           COptMethodSRES.cpp \
           COptMethodSteepestDescent.cpp \
           COptMethodStatistics.cpp \
           COptProblem.cpp \
           COptTask.cpp \
           CRandomSearch.cpp \
           FminBrent.cpp

contains(DEFINES, COPASI_PRAXIS) {
  HEADERS += COptMethodPraxis.h \
             CPraxis.h
           
  SOURCES += COptMethodPraxis.cpp \
             CPraxis.cpp
}

contains(DEFINES, COPASI_TRUNCATED_NEWTON) {
  HEADERS += COptMethodTruncatedNewton.h \
             CTruncatedNewton.h
           
  SOURCES += COptMethodTruncatedNewton.cpp \
             CTruncatedNewton.cpp
}

DISTFILES += optimization.dsp
