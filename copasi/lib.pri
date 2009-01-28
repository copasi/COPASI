# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lib.pri,v $ 
#   $Revision: 1.9 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2009/01/28 03:56:28 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.9 $ $Author: shoops $ $Date: 2009/01/28 03:56:28 $  
######################################################################

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH  += .. 
INCLUDEPATH += ..
OBJECTS_DIR  = .

win32 {
  debug:   DESTDIR = ../tmp/debug
  release: DESTDIR = ../tmp/release
} else {
  DESTDIR = ../tmp
}
   
TARGET       = $$LIB

isEmpty(SRC_TARGET) {
  SRC_TARGET = $$LIB
}

!contains(BUILD_OS, WIN32) {
  QMAKE_AR     = tar -czf
  QMAKE_RANLIB = 
}

