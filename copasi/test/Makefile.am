####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = test

test_SOURCES = test.cpp

# matrix_SOURCES = matrix.cpp

EXTRA_DIST = test.cpp matrix.cpp

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = test

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

# the library search path.
LIBS = \
	-lelementaryFluxModes \
	-lmodel \
        -lfunction \
        -loutput \
        -lsteadystate \
        -ltrajectory \
        -lutilities \
        -loutput \
        -lfunction \
        -lmodel \
	-llapack \
	-lblas \
	-lF77 \
	-lfl

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
        -L../steadystate \
        -L../trajectory \
        -L../utilities

SUBDIRS = \
	elementaryFluxModes \
	function \
	model \
	optimization \
	output \
	steadystate \
	trajectory \
	utilities

all-recursive install-data-recursive install-exec-recursive \
installdirs-recursive install-recursive uninstall-recursive  \
check-recursive installcheck-recursive info-recursive dvi-recursive: $(SUBDIRS)

$(SUBDIRS): ../
	@test -d $@ || ln -s ../$@ $@
