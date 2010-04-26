# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/lyap.pro,v $ 
#   $Revision: 1.6.2.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/04/26 17:40:52 $ 
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
# $Revision: 1.6.2.3 $ $Author: shoops $ $Date: 2010/04/26 17:40:52 $
######################################################################

LIB = lyap

# Input
HEADERS += CLyapWolfMethod.h \
           #CTimeSeries.h \
           CLyapMethod.h \
           CLyapProblem.h \
           CLyapTask.h

SOURCES += CLyapWolfMethod.cpp \
           #CTimeSeries.cpp \
           CLyapMethod.cpp \
           CLyapProblem.cpp \
           CLyapTask.cpp

include(../lib.pri)
include(../common.pri)
