####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = test
test_SOURCES = test.cpp
test_LDADD   = \
	../utilities/libutilities.a \
	../function/libfunction.a \
	../output/liboutput.a \
	../model/libmodel.a \
	../trajectory/libtrajectory.a

EXTRA_DIST = test.cpp 

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = test

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

# the library search path.
test_LDFLAGS = $(all_libraries)
