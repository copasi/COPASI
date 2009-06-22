# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/plotUI.pro,v $
#   $Revision: 1.6 $
#   $Name:  $
#   $Author: pwilly $
#   $Date: 2009/06/22 20:47:04 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

######################################################################
# $Revision: 1.6 $ $Author: pwilly $ $Date: 2009/06/22 20:47:04 $
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

#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3 +=  curve2dwidget.ui
#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3 +=  HistoWidget.ui

HEADERS += curve2dwidget.ui.h
HEADERS +=  HistoWidget.ui.h

INCLUDEPATH += $${QWT_PATH}/include
#INCLUDEPATH += $${QWT_PATH}/include/qwt-qt3

DISTFILES += plotUI.vcproj
DISTFILES += QwtLicense
#The following line was inserted by qt3to4
QT +=  opengl qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3

#The following line was inserted by qt3to4
QT +=  

#The following line is for implementing QtSvg module
QT += svg
