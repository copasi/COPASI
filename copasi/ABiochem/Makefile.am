####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = ABiochem

ABiochem_SOURCES = \
	1d.cpp \
	ab.cpp \
	abiochem.cpp \
	CGene.cpp \
	Erdos.cpp \
	r250.c \
	random.c

ABiochem_DEPENDENCIES = $(ABiochem_LIBS) check_LIBS

ABiochem_LIBS = \
	../elementaryFluxModes \
	../model \
	../function \
	../output \
	../randomGenerator \
	../report \
	../steadystate \
	../trajectory \
	../utilities

EXTRA_DIST =  \
	clo.cpp \
	abiochem.cpp \
	CGene.h CGene.cpp \
	Erdos.cpp \
	r250.h r250.c \
	random.c

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

# the library search path.
LIBS = \
	-Wl,-lelementaryFluxModes \
	-Wl,-lmodel \
        -Wl,-lfunction \
        -Wl,-loutput \
        -Wl,-lsteadystate \
        -Wl,-ltrajectory \
        -Wl,-lutilities \
        -Wl,-loutput \
        -Wl,-lfunction \
        -Wl,-lmodel \
	-Wl,-lreport \
	-Wl,-lrandomGenerator \
        -llapack -lblas -lf2c -lfl

#  Use this for standard clapack
#	-llapack \
#	-lblas \
#	-lF77 \
#	-lfl

#  Use this for gcc 3.2 with clapack
#	-llapack -lblas -lf2c -lfl

#  Use this for the intel performance library under linux
#	-lmkl_lapack \
#	-lmkl_p3 \
#	-lg2c \
#	-lpthread \

# the library search path.
LDFLAGS = -static $(all_libraries) $(USER_LDFLAGS)\
	-L../elementaryFluxModes \
        -L../function \
        -L../model \
        -L../output \
	-L../randomGenerator \
	-L../report \
        -L../steadystate \
        -L../trajectory \
        -L../utilities

check_LIBS:
	@for d in $(ABiochem_LIBS); do (cd $$d && make); done
