# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/trajectory.pro,v $ 
#   $Revision: 1.13 $ 
#   $Name:  $ 
#   $Author: nsimus $ 
#   $Date: 2007/04/05 09:55:07 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.13 $ $Author: nsimus $ $Date: 2007/04/05 09:55:07 $  
######################################################################

LIB = trajectory

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CHybridMethod.h \
           CHybridMethodLSODA.h \
           CHybridNextReactionRKMethod.h \
           CHybridNextReactionLSODAMethod.h \
           CLsodaMethod.h \
           CLsodarMethod.h \
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
           CLsodarMethod.cpp \
           CStochDirectMethod.cpp \
           CStochMethod.cpp \
           CStochNextReactionMethod.cpp \
           CTauLeapMethod.cpp \
           CTimeSeries.cpp \
           CTrajectoryMethod.cpp \
           CTrajectoryProblem.cpp \
           CTrajectoryTask.cpp


DISTFILES += trajectory.dsp
