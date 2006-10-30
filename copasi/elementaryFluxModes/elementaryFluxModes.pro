######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sat May 17 20:42:30 2003
######################################################################

LIB = elementaryFluxModes

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CEFMAlgorithm.h \
           CEFMMethod.h \
           CEFMProblem.h \
           CEFMTask.h \
           CFluxMode.h \
           CFluxScore.h \
           CTableauLine.h \
           CTableauMatrix.h

contains(DEFINES, COPASI_EXTREMECURRENTS) {
   HEADERS += CExtremeCurrentCalculator.h
}
           
SOURCES += CEFMAlgorithm.cpp \
           CEFMMethod.cpp \
           CEFMProblem.cpp \
           CEFMTask.cpp \
           CFluxMode.cpp \
           CFluxScore.cpp \
           CTableauLine.cpp \
           CTableauMatrix.cpp 

contains(DEFINES, COPASI_EXTREMECURRENTS) {
   SOURCES += CExtremeCurrentCalculator.cpp
}


DISTFILES += elementaryFluxModes.dsp
