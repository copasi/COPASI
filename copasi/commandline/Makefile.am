####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libcommandline.a

libcommandline_a_SOURCES = \
	CopasiSE.cpp

EXTRA_DIST = \
	CopasiSE.h	CopasiSE.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

.cpp.xml:
	-clo++ -o c++ -D cxx_namespace=$* $< && \
	cat clo.cxx | \
	sed -e 's/clo.h/'$*'.h/g' \
	    -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' \
	    > $@ && \
	cat clo.h | sed -e 's/__clo_h__/COPASI_$*/g' > $*.h
	-@rm clo.*

%.cpp: %.xml
	-clo++ -o c++ -D cxx_namespace=$* $< && \
	cat clo.cxx | \
	sed -e 's/clo.h/'$*'.h/g' \
	    -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' \
	    > $@ && \
	cat clo.h | sed -e 's/__clo_h__/COPASI_$*/g' > $*.h
	@rm -f clo.*

