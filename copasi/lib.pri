# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lib.pri,v $ 
#   $Revision: 1.9.2.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/02/26 16:50:24 $ 
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
# $Revision: 1.9.2.1 $ $Author: shoops $ $Date: 2010/02/26 16:50:24 $  
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
  macx:debug {
    DESTDIR = ../lib
  } else {
    DESTDIR = ../tmp
  }
}
   
TARGET       = $$LIB

isEmpty(SRC_TARGET) {
  SRC_TARGET = $$LIB
}

!contains(BUILD_OS, WIN32) {
  !macx:debug {
    QMAKE_AR     = tar -czf
    QMAKE_RANLIB = 
  }
}

