

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
           plotwindow.h

SOURCES += CopasiPlot.cpp \
           doublerect.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           CPlotSpec.cpp \
           CPlotSpecVector.cpp \
           zoomplot.cpp 

FORMS +=  curve2dwidget.ui
