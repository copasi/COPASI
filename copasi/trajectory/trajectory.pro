######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2003/05/19 00:39:50 $  
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
           CTrajectoryMethod.h \
           CTrajectoryProblem.h \
           CTrajectoryTask.h

SOURCES += CHybridMethod.cpp \
           CHybridNextReactionRKMethod.cpp \
           CLsodaMethod.cpp \
           CStochDirectMethod.cpp \
           CStochMethod.cpp \
           CStochNextReactionMethod.cpp \
           CTrajectoryMethod.cpp \
           CTrajectoryProblem.cpp \
           CTrajectoryTask.cpp
