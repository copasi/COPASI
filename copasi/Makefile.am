####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = copasi
copasi_SOURCES = main.cpp 

copasi_LDADD = \
	./function/libfunction.a \
	./output/liboutput.a \
	./model/libmodel.a \
	./steadystate/libsteadystate.a \
	./trajectory/libtrajectory.a \
	./utilities/libutilities.a 

SUBDIRS = \
	ABiochem \
	commandline\
	elementaryFluxModes \
	function \
	output \
	model \
	optimization \
	steadystate \
	trajectory \
	utilities \
	CopasiUI \
	test 

EXTRA_DIST = \
	main.cpp \
	copasi.h \
	FlexLexer.h

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

# the library search path.
copasi_LDFLAGS = $(all_libraries)
