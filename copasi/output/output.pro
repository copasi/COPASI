######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sun May 18 08:55:32 2003
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
