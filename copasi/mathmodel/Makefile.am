####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libmathmodel.a

libmathmodel_a_SOURCES = \
	CMathSymbol.cpp \
	CMathConstant.cpp \
	CMathVariable.cpp \
	CMathModel.cpp \
	CMathNode.cpp \
	CMathEq.cpp

EXTRA_DIST = \
	CMathSymbol.h CMathSymbol.cpp \
	CMathConstant.h CMathConstant.cpp \
	CMathVariable.h CMathVariable.cpp \
	CMathModel.h CMathModel.cpp \
	CMathNode.h CMathNode.cpp \
	CMathEq.h CMathEq.cpp


####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

.lpp.cpp:
	$(LEX) -t $< | \
	sed -e 's/class istream;/#include "copasi.h"/' \
	    -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
	    -e 's/#include <unistd.h>/using namespace std;/' > $@

%.cpp: %.lpp
	$(LEX) -t $< | \
	sed -e 's/class istream;/#include "copasi.h"/' \
	    -e 's/<FlexLexer.h>/"FlexLexer.h"/' \
	    -e 's/#include <unistd.h>/using namespace std;/' > $@

