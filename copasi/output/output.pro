######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2003/05/19 00:39:47 $  
######################################################################

LIB = output
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
