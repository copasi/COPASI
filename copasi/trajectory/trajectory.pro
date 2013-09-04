# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.21 $ $Author: shoops $ $Date: 2011/03/07 19:34:14 $
######################################################################

LIB = trajectory
DISTFILES = trajectory.pro

# Input
HEADERS += CHybridMethod.h \
           CHybridMethodLSODA.h \
           CHybridMethodODE45.h \
           CHybridNextReactionRKMethod.h \
           CHybridNextReactionLSODAMethod.h \
           CInterpolation.h \
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
           CHybridMethodODE45.cpp \
           CHybridNextReactionRKMethod.cpp \
           CHybridNextReactionLSODAMethod.cpp \
           CInterpolation.cpp \
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
