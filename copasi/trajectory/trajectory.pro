######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:18:03 $  
######################################################################

LIB = trajectory
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
