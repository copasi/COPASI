####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libfunction.a

libfunction_a_SOURCES = \
	CRange.cpp \
	CUsageRange.cpp \
	CFunction.cpp \
	CFunctionParameter.cpp \
	CFunctionParameters.cpp \
	CKinFunction.cpp \
	CKinFunctionFlexLexer.cpp \
	CMassAction.cpp \
	CFunctionDB.cpp \
	CNodeK.cpp

EXTRA_DIST = \
	CRange.h		CRange.cpp \
	CUsageRange.h		CUsageRange.cpp \
	CFunction.h		CFunction.cpp \
	CFunctionParameter.h	CFunctionParameter.cpp \
	CFunctionParameters.h	CFunctionParameters.cpp \
	CMassAction.h 		CMassAction.cpp \
	CKinFunction.h		CKinFunction.cpp \
	CKinFunctionFlexLexer.cpp \
	CKinFunctionFlexLexer.lpp \
	CFunctionDB.h		CFunctionDB.cpp \
	CNodeK.h		CNodeK.cpp \
	CCallParameter.h \
	CCallParameters.h \
	function.h

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

