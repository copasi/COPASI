######################################################################
# $Revision: 1.16.2.2 $ $Author: shoops $ $Date: 2006/06/07 14:59:53 $  
######################################################################

LIB = plot

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS += CHistogram.h \
           plotwidget1.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           CPlotItem.h \
           CPlotSpecification.h \
           COutputDefinitionVector.h \
           plotwindow.h \
           scrollbar.h \
           scrollzoomer.h

SOURCES += CHistogram.cpp \
           CopasiPlot.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           COutputHandlerPlot.cpp \
           CPlotItem.cpp \
           CPlotSpecification.cpp \
           COutputDefinitionVector.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp

FORMS +=  curve2dwidget.ui
FORMS +=  HistoWidget.ui

HEADERS += curve2dwidget.ui.h
HEADERS +=  HistoWidget.ui.h

INCLUDEPATH += $${QWT_PATH}/include

DISTFILES += plot.dsp
DISTFILES += QwtLicense
