######################################################################
# $Revision: 1.10 $ $Author: shoops $ $Date: 2004/11/04 01:01:43 $  
######################################################################

LIB = plot

include(../common.pri)
include(../lib.pri)

CONFIG += qt

HEADERS += plotwidget1.h \
           doublerect.h \
           zoomplot.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           CPlotItem.h \
           CPlotSpecification.h \
           CPlotSpec2Vector.h \
           plotwindow.h  
#           curve2dwidget.h

SOURCES += CopasiPlot.cpp \
           doublerect.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           COutputHandlerPlot.cpp \
           CPlotItem.cpp \
           CPlotSpecification.cpp \
           CPlotSpec2Vector.cpp \
           zoomplot.cpp 
#           curve2dwidget.cpp

FORMS +=  curve2dwidget.ui
