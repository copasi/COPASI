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
        -lfunction \
        -lmodel \
        -loutput \
        -lsteadystate \
        -ltrajectory \
        -lutilities \
	-llapack \
	-lblas \
	-lF77

# the library search path.
LDFLAGS = -all-static \
        -L../function \
        -L../model \
        -L../output \
        -L../steadystate \
        -L../trajectory \
        -L../utilities \
	$(USER_LDFLAGS)

LDADD = \
        ../function/libfunction.a \
        ../output/liboutput.a \
        ../model/libmodel.a \
	../steadystate/libsteadystate.a \
        ../trajectory/libtrajectory.a \
        ../utilities/libutilities.a

SUBDIRS = \
        function \
        output \
        model \
        steadystate \
        trajectory \
        utilities

all-recursive install-data-recursive install-exec-recursive \
installdirs-recursive install-recursive uninstall-recursive  \
check-recursive installcheck-recursive info-recursive dvi-recursive: $(SUBDIRS)

$(SUBDIRS): ../
	@test -d $@ || ln -s ../$@ $@
