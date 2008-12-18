# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/barChart.pro,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/12/18 17:20:46 $ 
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
  
#The following line was inserted by qt3to4
QT += xml  opengl qt3support 
