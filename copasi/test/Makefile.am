####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = test matrix

test_SOURCES = test.cpp

matrix_SOURCES = matrix.cpp

EXTRA_DIST = test.cpp matrix.cpp

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
	test -d $@ || ln -s ../$@ $@
