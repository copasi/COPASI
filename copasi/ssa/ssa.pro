######################################################################
# $Revision: 1.1 $ $Author: tjohann $ $Date: 2006/09/12 15:16:20 $  
######################################################################

LIB = ssa

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CSSATask.h \
	   CSSAProblem.h \
	   CSSAMethod.h

SOURCES += CSSATask.cpp \
	   CSSAProblem.cpp \
	   CSSAMethod.cpp

DISTFILES += ssa.dsp
