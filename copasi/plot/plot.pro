######################################################################
# $Revision: 1.16 $ $Author: shoops $ $Date: 2006/04/16 21:04:15 $  
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

INCLUDEPATH += $${QWT_PATH}/include
