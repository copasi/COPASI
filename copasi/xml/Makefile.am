####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libcopasiXML.a

libcopasiXML_a_SOURCES = \
	CExpat.cpp \
	CCopasiXMLInterface.cpp \
	CCopasiXML.cpp

EXTRA_DIST = \
	CExpat.h CExpat.cpp \
	CCopasiXMLInterface.h CCopasiXMLInterface.cpp \
	CCopasiXML.h CCopasiXML.cpp

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

