######################################################################
# Created by Stefan Hoops <shoops@vt.edu> Sat May 17 20:42:30 2003
######################################################################

LIB = elementaryFluxModes
include(../lib.pri)

# Input
HEADERS += CEFMAlgorithm.h \
           CElementaryFluxModes.h \
           CFluxMode.h \
           CFluxScore.h \
           CTableauLine.h \
           CTableauMatrix.h
           
SOURCES += CEFMAlgorithm.cpp \
           CElementaryFluxModes.cpp \
           CFluxMode.cpp \
           CFluxScore.cpp \
           CTableauLine.cpp \
           CTableauMatrix.cpp
