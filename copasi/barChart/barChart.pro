# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/barChart.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/09/18 07:22:27 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = barChart


include(../lib.pri)
CONFIG += qt 
include(../common.pri)

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
  
