# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.pro,v $ 
#   $Revision: 1.11.14.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/03/03 11:04:01 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

LANGUAGE	= C++

LIB= wizard

include(../lib.pri)
include(../common.pri)

CONFIG	+= qt 

unix {
  UI_DIR = .
  MOC_DIR = .
  OBJECTS_DIR = .
}

# FORMS	= wizard.ui

HEADERS += \
           wizard.h \
           wizard.ui.h
           
SOURCES += \
           wizard.cpp

                   
DISTFILES += wizard.dsp \
             help_html/figures/*.png \
             help_html/*.html
