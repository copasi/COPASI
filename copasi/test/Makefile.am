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
        -lfunction \
        -lmodel \
        -loutput \
        -lsteadystate \
        -ltrajectory \
        -lutilities \
	-llapack \
	-lblas \
	-lF77 \
	-lfl

# the library search path.
LDFLAGS = -all-static \
	-L../elementaryFluxModes \
        -L../function \
        -L../model \
        -L../output \
        -L../steadystate \
        -L../trajectory \
        -L../utilities \
	$(USER_LDFLAGS)

LDADD = \
	../elementaryFluxModes/libelementaryFluxModes.a \
        ../function/libfunction.a \
        ../model/libmodel.a \
        ../output/liboutput.a \
	../steadystate/libsteadystate.a \
        ../trajectory/libtrajectory.a \
        ../utilities/libutilities.a

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
