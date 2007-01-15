# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/trajectory.pro,v $ 
#   $Revision: 1.11 $ 
#   $Name:  $ 
#   $Author: nsimus $ 
#   $Date: 2007/01/15 12:05:12 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.11 $ $Author: nsimus $ $Date: 2007/01/15 12:05:12 $  
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
	   CTimeScaleSeparationMethod.h \
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
	   CTimeScaleSeparationMethod.cpp \
           CTimeSeries.cpp \
           CTrajectoryMethod.cpp \
           CTrajectoryProblem.cpp \
           CTrajectoryTask.cpp


DISTFILES += trajectory.dsp
