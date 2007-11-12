# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/barChart.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: akoenig $ 
#   $Date: 2007/11/12 17:01:06 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = barChart

include(../lib.pri)
include(../common.pri)

CONFIG += qt 
DEPENDPATH += .. 
INCLUDEPATH += ..
INCLUDEPATH += $${QWT3D_PATH}/include


# Input

HEADERS +=  qwt3dBars.h \
  qwt3dScale.h \
  qwt3dPlot.h \
  qwt3dColor.h \
  qwt3dBaseWidget.h 
  

SOURCES += qwt3dBars.cpp \
  qwt3dScale.cpp \
  qwt3dPlot.cpp \
  qwt3dColor.cpp\
  qwt3dBaseWidget.cpp 
  
