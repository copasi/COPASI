# Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
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
           CQPlotSubwidget.h \
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
           CQPlotSubwidget.cpp \
           plotwindow.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp

FORMS += BandedGraphWidget.ui
FORMS +=  PlotSubwidget.ui
FORMS +=  CQPlotSubwidget.ui
FORMS +=  HistoWidget.ui
FORMS +=  curve2dwidget.ui

DISTFILES += QwtLicense

include(../lib.pri)

CONFIG += qt

include(../common.pri)
include(../srcDistribution.pri)

