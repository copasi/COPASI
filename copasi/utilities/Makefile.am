####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libutilities.a

libutilities_a_SOURCES = \
	CCopasiException.cpp \
	CCopasiMessage.cpp \
	CGlobals.cpp \
	CRandom.cpp \
	CReadConfig.cpp \
	CVersion.cpp \
	CWriteConfig.cpp \
	utility.cpp

EXTRA_DIST = \
	utilities.h \
	CCopasiException.h	CCopasiException.cpp \
	CCopasiMessage.h	CCopasiMessage.cpp \
	CCopasiVector.h \
	CGlobals.h		CGlobals.cpp \
	CRandom.h		CRandom.cpp \
	CReadConfig.h		CReadConfig.cpp \
	CVersion.h		CVersion.cpp \
	CWriteConfig.h		CWriteConfig.cpp \
	messages.h \
	utility.h		utility.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)
