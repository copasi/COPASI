####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libtrajectory.a

libtrajectory_a_SOURCES = \
	Clsoda.cpp \
	CODESolver.cpp \
	CTrajectory.cpp \
	CStochSolver.cpp

EXTRA_DIST = \
	trajectory.h \
	Clsoda.h	Clsoda.cpp \
	CODESolver.h	CODESolver.cpp \
	CTrajectory.h	CTrajectory.cpp \
	CStochSolver.h	CStochSolver.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)
