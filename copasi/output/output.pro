######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2004/11/04 01:01:43 $  
######################################################################

LIB = output

include(../common.pri)
include(../lib.pri)

# Input
HEADERS += CDatum.h \
           CNodeO.h \
           COutput.h \
           COutputEvent.h \
           COutputLine.h \
           COutputList.h \
           CUDFunction.h \
           CUDFunctionDB.h \
           output.h

SOURCES += CDatum.cpp \
           CNodeO.cpp \
           COutput.cpp \
           COutputEvent.cpp \
           COutputLine.cpp \
           COutputList.cpp \
           CUDFunction.cpp \
           CUDFunctionDB.cpp
