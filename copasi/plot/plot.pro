######################################################################
# $Revision: 1.11 $ $Author: shoops $ $Date: 2005/02/08 16:33:04 $  
######################################################################

LIB = plot

include(../lib.pri)
include(../common.pri)

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
