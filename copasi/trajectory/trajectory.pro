# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/trajectory.pro,v $
#   $Revision: 1.20.2.2 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/11/13 16:56:01 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
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
# $Revision: 1.20.2.2 $ $Author: shoops $ $Date: 2010/11/13 16:56:01 $
######################################################################

LIB = trajectory
DISTFILES = trajectory.pro

# Input
HEADERS += CHybridMethod.h \
           CHybridMethodLSODA.h \
           CHybridNextReactionRKMethod.h \
           CHybridNextReactionLSODAMethod.h \
           CLsodaMethod.h \
           CStochDirectMethod.h \
           CStochMethod.h \
           CStochNextReactionMethod.h \
           CTauLeapMethod.h \
           CTimeSeries.h \
           CTrajAdaptiveSA.h \
           CTrajectoryMethod.h \
           CTrajectoryMethodDsaLsodar.h \
           CTrajectoryProblem.h \
           CTrajectoryTask.h

SOURCES += CHybridMethod.cpp \
           CHybridMethodLSODA.cpp \
           CHybridNextReactionRKMethod.cpp \
           CHybridNextReactionLSODAMethod.cpp \
           CLsodaMethod.cpp \
           CStochDirectMethod.cpp \
           CStochMethod.cpp \
           CStochNextReactionMethod.cpp \
           CTauLeapMethod.cpp \
           CTimeSeries.cpp \
           CTrajAdaptiveSA.cpp \
           CTrajectoryMethod.cpp \
           CTrajectoryMethodDsaLsodar.cpp \
           CTrajectoryProblem.cpp \
           CTrajectoryTask.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
