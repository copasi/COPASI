####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libtrajectory.a

libtrajectory_a_SOURCES = \
	CTrajectory.cpp \
	CStochSolver.cpp \
	CTrajectoryTask.cpp \
	CTrajectoryProblem.cpp \
	CTrajectoryMethod.cpp \
	CLsodaMethod.cpp 

EXTRA_DIST = \
	trajectory.h \
	CTrajectory.h	CTrajectory.cpp \
	CStochSolver.h	CStochSolver.cpp \
	CTrajectoryTask.h	CTrajectoryTask.cpp \
	CTrajectoryProblem.h	CTrajectoryProblem.cpp \
	CTrajectoryMethod.h	CTrajectoryMethod.cpp \
	CLsodaMethod.h	CLsodaMethod.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)
