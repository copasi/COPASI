####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libsteadystate.a

libsteadystate_a_SOURCES = \
	CSteadyStateMethod.cpp \
	CNewtonMethod.cpp \
	CSteadyStateProblem.cpp \
	CSteadyStateTask.cpp \
	CMca.cpp \
	CEigen.cpp

EXTRA_DIST = \
	steadystate.h \
	CSteadyStateMethod.h CSteadyStateMethod.cpp \
	CNewtonMethod.h	CNewtonMethod.cpp \
	CSteadyStateProblem.h CSteadyStateProblem.cpp \
	CSteadyStateTask.h CSteadyStateTask.cpp \
	CMca.h CMca.cpp \
	CEigen.h CEigen.cpp 

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)
