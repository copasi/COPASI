######################################################################
# $Revision: 1.6 $ $Author: ssahle $ $Date: 2004/04/06 14:56:09 $  
######################################################################

LIB = plot
include(../lib.pri)
CONFIG += qt

HEADERS += plotwidget1.h \
           doublerect.h \
           zoomplot.h \
           CopasiPlot.h \
           plotspec.h \
           COutputHandlerPlot.h \
           CPlotSpec.h \
           CPlotSpecVector.h \
           plotwindow.h  \
           curve2dwidget.h

SOURCES += CopasiPlot.cpp \
           doublerect.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           COutputHandlerPlot.cpp \
           CPlotSpec.cpp \
           CPlotSpecVector.cpp \
           zoomplot.cpp \
           curve2dwidget.cpp

# FORMS +=  curve2dwidget.ui
