######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2005/02/08 16:33:05 $  
######################################################################

LIB = trajectory

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CHybridMethod.h \
           CHybridNextReactionRKMethod.h \
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
           CHybridNextReactionRKMethod.cpp \
           CLsodaMethod.cpp \
           CStochDirectMethod.cpp \
           CStochMethod.cpp \
           CStochNextReactionMethod.cpp \
           CTauLeapMethod.cpp \
           CTimeSeries.cpp \
           CTrajectoryMethod.cpp \
           CTrajectoryProblem.cpp \
           CTrajectoryTask.cpp
