######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2004/11/04 01:01:42 $  
######################################################################

LIB = trajectory

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += CHybridMethod.h \
           CHybridNextReactionRKMethod.h \
           CLsodaMethod.h \
           CStochDirectMethod.h \
           CStochMethod.h \
           CStochNextReactionMethod.h \
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
           CTimeSeries.cpp \
           CTrajectoryMethod.cpp \
           CTrajectoryProblem.cpp \
           CTrajectoryTask.cpp
