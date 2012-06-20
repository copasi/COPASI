# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/optimization.pro,v $
#   $Revision: 1.38 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2012/06/20 21:17:11 $
# End CVS Header

# Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.38 $ $Author: shoops $ $Date: 2012/06/20 21:17:11 $
######################################################################

LIB = optimization
DISTFILES = optimization.pro

# Input
HEADERS += COptItem.h \
           COptMethod.h \
           COptMethodEP.h \
           COptMethodDE.h \
           COptMethodGA.h \
           COptMethodGASR.h \
           COptMethodHookeJeeves.h \
           COptMethodLevenbergMarquardt.h \
           COptMethodNelderMead.h \
           COptMethodPraxis.h \
           COptMethodPS.h \
           COptMethodSA.h \
           COptMethodCoranaWalk.h \
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
           COptMethodDE.cpp \
           COptMethodEP.cpp \
           COptMethodGA.cpp \
           COptMethodGASR.cpp \
           COptMethodHookeJeeves.cpp \
           COptMethodLevenbergMarquardt.cpp \
           COptMethodNelderMead.cpp \
           COptMethodPraxis.cpp \
           COptMethodPS.cpp \
           COptMethodSA.cpp \
           COptMethodCoranaWalk.cpp \
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

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
