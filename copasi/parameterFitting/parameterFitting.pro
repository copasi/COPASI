######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2005/09/16 19:20:33 $  
######################################################################

LIB = fitting

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CExperiment.h \
           CExperimentSet.h \
           CFitMethod.h \
           CFitProblem.h \
           CFitTask.h
           
SOURCES += CExperiment.cpp \
           CExperimentSet.cpp \
           CFitMethod.cpp \
           CFitProblem.cpp \
           CFitTask.cpp
