# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/barChart.pro,v $ 
#   $Revision: 1.7 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/08/22 21:39:53 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = barChart
DISTFILES = barChart.pro

FORMS += \
  CQBaseWidget.ui

# Input
HEADERS += \
  CQBaseWidget.h \
  qwt3dBars.h \
  qwt3dScale.h \
  qwt3dPlot.h \
  qwt3dColor.h 
  

SOURCES += \
  CQBaseWidget.cpp \
  qwt3dBars.cpp \
  qwt3dScale.cpp \
  qwt3dPlot.cpp \
  qwt3dColor.cpp 

  
include(../lib.pri)

CONFIG += qt 

include(../common.pri)
include(../srcDistribution.pri)

#The following line was inserted by qt3to4
QT += xml opengl 
