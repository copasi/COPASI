######################################################################
# $Revision: 1.3.4.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:55 $  
######################################################################

LIB = fitting
SRC_TARGET = parameterFitting

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CExperiment.h \
           CExperimentSet.h \
           CExperimentObjectMap.h \
           CExperimentFileInfo.h \
           CFitItem.h \
           CFitMethod.h \
           CFitProblem.h \
           CFitTask.h
           
SOURCES += CExperiment.cpp \
           CExperimentSet.cpp  \
           CExperimentObjectMap.cpp \
           CExperimentFileInfo.cpp \
           CFitItem.cpp \
           CFitMethod.cpp \
           CFitProblem.cpp \
           CFitTask.cpp

DISTFILES += fitting.dsp
