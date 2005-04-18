######################################################################
# $Revision: 1.14 $ $Author: ssahle $ $Date: 2005/04/18 09:23:41 $  
######################################################################

LIB = plot

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS += CHistogram.h \
           plotwidget1.h \
           doublerect.h \
           zoomplot.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           CPlotItem.h \
           CPlotSpecification.h \
           CPlotSpec2Vector.h \
           COutputDefinitionVector.h \
           plotwindow.h  
#           curve2dwidget.h

SOURCES += CHistogram.cpp \
           CopasiPlot.cpp \
           doublerect.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           COutputHandlerPlot.cpp \
           CPlotItem.cpp \
           CPlotSpecification.cpp \
           CPlotSpec2Vector.cpp \
           COutputDefinitionVector.cpp \
           zoomplot.cpp 
#           curve2dwidget.cpp

FORMS +=  curve2dwidget.ui
FORMS +=  HistoWidget.ui

INCLUDEPATH += $${QWT_PATH}/include
