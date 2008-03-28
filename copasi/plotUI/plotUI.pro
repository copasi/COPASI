# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotUI.pro,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: pwilly $ 
#   $Date: 2008/03/28 23:47:02 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.3 $ $Author: pwilly $ $Date: 2008/03/28 23:47:02 $  
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
#INCLUDEPATH += $${QWT_PATH}/include/qwt-qt3

DISTFILES += plotUI.dsp
DISTFILES += QwtLicense
