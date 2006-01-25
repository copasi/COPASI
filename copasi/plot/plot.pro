######################################################################
# $Revision: 1.14.10.1 $ $Author: ssahle $ $Date: 2006/01/25 12:01:20 $  
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
           CPlotSpec2Vector.h \
           COutputDefinitionVector.h \
           plotwindow.h \
           scrollbar.h \
           scrollzoomer.h
#           curve2dwidget.h

SOURCES += CHistogram.cpp \
           CopasiPlot.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           COutputHandlerPlot.cpp \
           CPlotItem.cpp \
           CPlotSpecification.cpp \
           CPlotSpec2Vector.cpp \
           COutputDefinitionVector.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp
#           curve2dwidget.cpp

FORMS +=  curve2dwidget.ui
FORMS +=  HistoWidget.ui

INCLUDEPATH += $${QWT_PATH}/include
