####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libtrajectory.a

libtrajectory_a_SOURCES = \
	CTrajectoryTask.cpp \
	CTrajectoryProblem.cpp \
	CTrajectoryMethod.cpp \
	CLsodaMethod.cpp \
	CStochMethod.cpp \
  CStochDirectMethod.cpp \
  CStochNextReactionMethod.cpp

EXTRA_DIST = \
	trajectory.h \
	CTrajectory.h	CTrajectory.cpp \
	CStochSolver.h	CStochSolver.cpp \
	CTrajectoryTask.h	CTrajectoryTask.cpp \
	CTrajectoryProblem.h	CTrajectoryProblem.cpp \
	CTrajectoryMethod.h	CTrajectoryMethod.cpp \
	CLsodaMethod.h	CLsodaMethod.cpp \
	CStochMethod.h CStochMethod.cpp \
  CstochDirectMethod.h CStochDirectMethod.cpp \
  CstochNextReactionMethod.h CStochNextReactionMethod.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)
