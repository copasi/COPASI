####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libelementaryFluxModes.a

libelementaryFluxModes_a_SOURCES = \
	CElementaryFluxModes.cpp \
	CEFMAlgorithm.cpp \
	CTableauMatrix.cpp \
	CTableauLine.cpp \
	CFluxMode.cpp \
	CFluxScore.cpp

EXTRA_DIST = \
	CElementaryFluxModes.h	CElementaryFluxModes.cpp \
	CEFMAlgorithm.h		CEFMAlgorithm.cpp \
	CTableauMatrix.h	CTableauMatrix.cpp \
	CTableauLine.h		CTableauLine.cpp \
	CFluxMode.h		CFluxMode.cpp \
	CFluxScore.h		CFluxScore.cpp

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

