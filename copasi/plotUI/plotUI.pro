# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotUI.pro,v $ 
#   $Revision: 1.14 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2012/05/02 23:40:07 $ 
# End CVS Header 

# Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

LIB = plotUI


DISTFILES = plotUI.pro

HEADERS += BandedGraphWidget.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           CQPlotColors.h \
           curve2dwidget.h \
           HistoWidget.h \
           PlotSubwidget.h \
           plotwindow.h \
           scrollbar.h \
           scrollzoomer.h

SOURCES += BandedGraphWidget.cpp \
           CopasiPlot.cpp \
           COutputHandlerPlot.cpp \
           CQPlotColors.cpp \
           curve2dwidget.cpp \
           HistoWidget.cpp \
           PlotSubwidget.cpp \
           plotwindow.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp

FORMS += BandedGraphWidget.ui
FORMS +=  PlotSubwidget.ui
FORMS +=  HistoWidget.ui
FORMS +=  curve2dwidget.ui

DISTFILES += QwtLicense

include(../lib.pri)

CONFIG += qt

include(../common.pri)
include(../srcDistribution.pri)

