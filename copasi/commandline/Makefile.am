####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = copasi

copasi_SOURCES = \
	COptionParser.cpp \
	COptions.cpp \
	copasi.cpp

copasi_DEPENDENCIES = $(copasi_LIBS) check_LIBS

copasi_LIBS = \
	../elementaryFluxModes \
	../model \
	../function \
	../output \
	../optimization \
	../randomGenerator \
	../report \
	../steadystate \
	../trajectory \
	../utilities

EXTRA_DIST = \
	COptionParser.h	COptionParser.cpp	COptionParser.xml \
	COptions.h	COptions.cpp \
	copasi.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

# the library search path.
LIBS = \
	-Wl,-lrandomGenerator \
	-Wl,-lutilities \
	-Wl,-loutput \
	-Wl,-lreport \
	-Wl,-lfunction \
	-Wl,-lmodel \
	-Wl,-lutilities \
	-Wl,-lsteadystate \
	-Wl,-ltrajectory \
	-Wl,-lutilities \
	-Wl,-loutput \
	-lmkl_lapack -lmkl_p3 -lg2c -lpthread

#  Use this for standard clapack
#	-llapack -lblas -lF77 -lfl

#  Use this for the intel performance library under linux
#	-lmkl_lapack -lmkl_p3 -lg2c -lpthread

# the library search path.
LDFLAGS = -all-static $(all_libraries) $(USER_LDFLAGS)\
	-L../elementaryFluxModes \
        -L../function \
        -L../model \
        -L../output \
	-L../optimization \
	-L../randomGenerator \
        -L../report \
        -L../steadystate \
        -L../trajectory \
        -L../utilities

check_LIBS:
	@for d in $(copasi_LIBS); do (cd $$d && make || rm *.a); done

.xml.cpp:
	-@rm $@ $*.h
	-clo++ -o c++ $< && \
	cat $@ | \
	sed -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' \
	    > $@.tmp && \
	mv $@.tmp $@
	../../cvs_admin/c++style $@
	../../cvs_admin/c++style $*.h

%.cpp: %.xml
	-@rm $@ $*.h
	-clo++ -o c++ $< && \
	cat $@ | \
	sed -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' \
	    > $@.tmp && \
	mv $@.tmp $@
	../../cvs_admin/c++style $@
	../../cvs_admin/c++style $*.h
