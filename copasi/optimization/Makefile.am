####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = liboptimization.a

liboptimization_a_SOURCES = \
	CGA.cpp \
	COptAlgorithm.cpp \
	COptAlgorithmParameter.cpp \
	COptProblem.cpp \
	CRealProblem.cpp

EXTRA_DIST = \
	CGA.h				CGA.cpp \
	COptAlgorithm.h			COptAlgorithm.cpp \
	COptAlgorithmParameter.h	COptAlgorithmParameter.cpp \
	COptProblem.h			COptProblem.cpp \
	CRealProblem.h			CRealProblem.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

.lpp.cpp:
	$(LEX) -t $< | \
	sed -e 's/class istream;/#include "copasi.h"/' \
	    -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
	    -e '/#include <unistd.h>/d' > $@

%.cpp: %.lpp
	$(LEX) -t $< | \
	sed -e 's/class istream;/#include "copasi.h"/' \
	    -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
	    -e '/#include <unistd.h>/d' > $@

