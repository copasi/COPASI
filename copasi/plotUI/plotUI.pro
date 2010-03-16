# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotUI.pro,v $
#   $Revision: 1.8 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/03/16 18:56:25 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2010/03/16 18:56:25 $
######################################################################

LIB = plotUI

HEADERS += CHistogram.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           HistoWidget.h \
           PlotSubwidget.h \
           plotwindow.h \
           scrollbar.h \
           scrollzoomer.h

SOURCES += CHistogram.cpp \
           CopasiPlot.cpp \
           COutputHandlerPlot.cpp \
           HistoWidget.cpp \
           PlotSubwidget.cpp \
           plotwindow.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp

FORMS += PlotSubwidget.ui
FORMS +=  HistoWidget.ui

FORMS3 +=  curve2dwidget.ui

HEADERS += curve2dwidget.ui.h

DISTFILES += QwtLicense

include(../lib.pri)

CONFIG += qt

include(../common.pri)


#The following line was inserted by qt3to4
QT +=  opengl qt3support 

 #The following line was inserted by qt3to4
CONFIG += uic3

#The following line is for implementing QtSvg module
QT += svg
