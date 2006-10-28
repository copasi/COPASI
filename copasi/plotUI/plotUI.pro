######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2006/10/28 00:31:05 $  
######################################################################

LIB = plotUI

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS += CHistogram.h \
           plotwidget1.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           plotwindow.h \
           scrollbar.h \
           scrollzoomer.h

SOURCES += CHistogram.cpp \
           CopasiPlot.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           COutputHandlerPlot.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp

FORMS +=  curve2dwidget.ui
FORMS +=  HistoWidget.ui

HEADERS += curve2dwidget.ui.h
HEADERS +=  HistoWidget.ui.h

INCLUDEPATH += $${QWT_PATH}/include

DISTFILES += plotUI.dsp
DISTFILES += QwtLicense
