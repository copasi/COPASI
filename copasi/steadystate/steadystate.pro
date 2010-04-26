# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/steadystate.pro,v $ 
#   $Revision: 1.11.2.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/04/26 17:40:54 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.11.2.3 $ $Author: shoops $ $Date: 2010/04/26 17:40:54 $
######################################################################

LIB = steadystate

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

include(../lib.pri)
include(../common.pri)
