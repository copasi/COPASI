####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = test matrix

test_SOURCES = test.cpp

matrix_SOURCES = matrix.cpp

EXTRA_DIST = test.cpp 

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = test matrix

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

# the library search path.
LIBS = \
	-lutilities \
	-lfunction \
	-lmodel \
	-loutput \
	-lsteadystate \
	-ltrajectory

# the library search path.
LDFLAGS = -all-static\
	-L../utilities \
	-L../function \
	-L../model \
	-L../output \
	-L../steadystate \
	-L../trajectory

LDADD = \
	../utilities/libutilities.a \
	../function/libfunction.a \
	../output/liboutput.a \
	../model/libmodel.a \
	../trajectory/libtrajectory.a
