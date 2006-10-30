######################################################################
# $Revision: 1.22 $ $Author: shoops $ $Date: 2006/10/30 21:12:15 $  
######################################################################

LIB = plot

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS += CPlotItem.h \
           CPlotSpecification.h \
           COutputDefinitionVector.h

SOURCES += CPlotItem.cpp \
           CPlotSpecification.cpp \
           COutputDefinitionVector.cpp \

DISTFILES += plot.dsp
