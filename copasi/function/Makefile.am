####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libfunction.a

libfunction_a_SOURCES = \
	CRange.cpp \
	CUsageRange.cpp \
	CFunction.cpp \
	CFunctionParameter.cpp \
	CFunctionParameters.cpp \
	CKinFunction.cpp \
	CMassAction.cpp \
	CFunctionDB.cpp \
	CNodeK.cpp \
	lexkk.cpp

EXTRA_DIST = \
	CRange.h		CRange.cpp \
	CUsageRange.h		CUsageRange.cpp \
	CFunction.h		CFunction.cpp \
	CFunctionParameter.h	CFunctionParameter.cpp \
	CFunctionParameters.h	CFunctionParameters.cpp \
	CMassAction.h 		CMassAction.cpp \
	CKinFunction.h		CKinFunction.cpp \
	CFunctionDB.h		CFunctionDB.cpp \
	CNodeK.h		CNodeK.cpp \
	lexkk.h 		lexkk.cpp\
	CCallParameter.h \
	CCallParameters.h

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

.lpp.cpp:
	$(LEX) $<

%.cpp: %.lpp
	$(LEX) $<
