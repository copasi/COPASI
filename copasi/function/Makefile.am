####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libfunction.a

libfunction_a_SOURCES = \
	CBaseFunction.cpp \
	CBaseIdentifier.cpp \
	CFunctionDB.cpp \
	CKinFunction.cpp \
	CMassAction.cpp \
	CNodeK.cpp \
	lexkk.cpp

EXTRA_DIST = \
	CBaseFunction.h		CBaseFunction.cpp \
	CBaseIdentifier.h	CBaseIdentifier.cpp \
	CFunctionDB.h		CFunctionDB.cpp \
	CKinFunction.h		CKinFunction.cpp \
	CMassAction.h		CMassAction.cpp \
	CNodeK.h		CNodeK.cpp \
	lexkk.h 		lexkk.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi

.lpp.cpp:
	$(LEX) $<

%.cpp: %.lpp
	$(LEX) $<
