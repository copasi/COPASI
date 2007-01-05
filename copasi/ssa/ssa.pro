######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2006/10/30 21:12:12 $  
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
