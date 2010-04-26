# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotUI.pro,v $
#   $Revision: 1.7.2.4 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/04/26 18:25:05 $
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
# $Revision: 1.7.2.4 $ $Author: shoops $ $Date: 2010/04/26 18:25:05 $
######################################################################

LIB = plotUI

HEADERS += CHistogram.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           curve2dwidget.h \
           HistoWidget.h \
           PlotSubwidget.h \
           plotwindow.h \
           scrollbar.h \
           scrollzoomer.h

SOURCES += CHistogram.cpp \
           CopasiPlot.cpp \
           COutputHandlerPlot.cpp \
           curve2dwidget.cpp \
           HistoWidget.cpp \
           PlotSubwidget.cpp \
           plotwindow.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp

FORMS += PlotSubwidget.ui
FORMS +=  HistoWidget.ui
FORMS +=  curve2dwidget.ui

HEADERS += curve2dwidget.ui.h

DISTFILES += QwtLicense

include(../lib.pri)

CONFIG += qt

include(../common.pri)


#The following line was inserted by qt3to4
QT +=  opengl 

#The following line is for implementing QtSvg module
QT += svg qt3support
