######################################################################
# $Revision: 1.9 $ $Author: ssahle $ $Date: 2004/08/09 13:14:22 $  
######################################################################

LIB = plot
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
