####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = test

test_SOURCES = \
	test.cpp

test_DEPENDENCIES = $(test_LIBS) check_LIBS

test_LIBS = \
	../elementaryFluxModes \
	../model \
	../function \
	../output \
	../optimization \
	../randomGenerator \
	../steadystate \
	../trajectory \
	../utilities

# matrix_SOURCES = matrix.cpp

EXTRA_DIST = test.cpp matrix.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

# the library search path.
LIBS = \
	-Wl,-lelementaryFluxModes \
	-Wl,-lmodel \
	-Wl,-lfunction \
	-Wl,-loutput \
	-Wl,-loptimization \
	-Wl,-lsteadystate \
	-Wl,-ltrajectory \
	-Wl,-lrandomGenerator \
	-Wl,-lutilities \
	-Wl,-loutput \
	-Wl,-lfunction \
	-Wl,-lmodel \
	-lmkl_lapack \
	-lmkl_p3 \
	-lg2c \
	-lpthread

#  Use this for standard clapack
#	-llapack \
#	-lblas \
#	-lF77 \
#	-lfl

#  Use this for the intel performance library under linux
#	-lmkl_lapack \
#	-lmkl_p3 \
#	-lg2c \
#	-lpthread \

# the library search path.
LDFLAGS = -all-static $(all_libraries) $(USER_LDFLAGS)\
	-L../elementaryFluxModes \
        -L../function \
        -L../model \
        -L../output \
	-L../optimization \
	-L../randomGenerator \
        -L../steadystate \
        -L../trajectory \
        -L../utilities

check_LIBS:
	@for d in $(test_LIBS); do (cd $$d && make); done
