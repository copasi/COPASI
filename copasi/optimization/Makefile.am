####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = liboptimization.a

liboptimization_a_SOURCES = \
	COptMethod.cpp \
	CRandomSearch.cpp \
	CRandomSearchMaster.cpp \
	COptProblem.cpp \
	CRealProblem.cpp

EXTRA_DIST = \
	COptMethod.h	COptMethod.cpp \
	CRandomSearch.h	CRandomSearch.cpp \
	CRandomSearchMaster.h	CRandomSearchMaster.cpp \
	COptProblem.h	COptProblem.cpp \
	CRealProblem.h	CRealProblem.cpp \
	optimization.h

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

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

