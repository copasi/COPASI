######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2005/09/19 21:12:54 $  
######################################################################

LIB = fitting

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CExperiment.h \
           CExperimentSet.h \
           CExperimentObjectMap.h \
           CFitItem.h \
           CFitMethod.h \
           CFitProblem.h \
           CFitTask.h
           
SOURCES += CExperiment.cpp \
           CExperimentSet.cpp  \
           CExperimentObjectMap.cpp \
           CFitItem.cpp \
           CFitMethod.cpp \
           CFitProblem.cpp \
           CFitTask.cpp
