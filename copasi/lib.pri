# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.10 $ $Author: shoops $ $Date: 2010/03/16 18:54:41 $  
######################################################################

TEMPLATE = lib

DISTFILES += CMakeLists.txt

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
  macx:debug {
  } else {
    QMAKE_AR     = tar -czf
    QMAKE_RANLIB = 
  }
}

