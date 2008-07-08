# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/steadystate.pro,v $ 
#   $Revision: 1.10 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/07/08 16:06:29 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.10 $ $Author: shoops $ $Date: 2008/07/08 16:06:29 $
######################################################################

LIB = steadystate

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CEigen.h \
           CMCAMethod.h \
           CMCAProblem.h \
	   CMCATask.h \
       	   CNewtonMethod.h \
           CSteadyStateMethod.h \
           CSteadyStateProblem.h \
           CSteadyStateTask.h

SOURCES += CEigen.cpp \
           CMCAMethod.cpp \
           CMCAProblem.cpp \
	   CMCATask.cpp \
           CNewtonMethod.cpp \
           CSteadyStateMethod.cpp \
           CSteadyStateProblem.cpp \
           CSteadyStateTask.cpp


DISTFILES +=steadystate.vcproj
