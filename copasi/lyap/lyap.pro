# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/lyap.pro,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/07/08 16:06:34 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2008/07/08 16:06:34 $
######################################################################

LIB = lyap

include(../lib.pri)
include(../common.pri)

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


DISTFILES += lyaponov.vcproj
