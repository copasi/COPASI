######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2004/01/15 16:28:40 $  
######################################################################

LIB = plot
include(../lib.pri)
CONFIG += qt

HEADERS += plotwidget1.h \
           doublerect.h \
           zoomplot.h \
           CopasiPlot.h \
           plotspec.h \
           CPlotSpec.h \
           CPlotSpecVector.h \
           plotwindow.h  \
           curve2dwidget.h

SOURCES += CopasiPlot.cpp \
           doublerect.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           CPlotSpec.cpp \
           CPlotSpecVector.cpp \
           zoomplot.cpp \
           curve2dwidget.cpp

# FORMS +=  curve2dwidget.ui
