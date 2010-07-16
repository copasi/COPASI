# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/trajectory.pro,v $
#   $Revision: 1.18 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/07/16 19:03:27 $
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
# $Revision: 1.18 $ $Author: shoops $ $Date: 2010/07/16 19:03:27 $
######################################################################

LIB = trajectory

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
           CTrajectoryMethod.h \
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
           CTrajectoryMethod.cpp \
           CTrajectoryProblem.cpp \
           CTrajectoryTask.cpp

include(../lib.pri)
include(../common.pri)
