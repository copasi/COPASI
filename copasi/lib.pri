######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2006/11/28 14:49:41 $  
######################################################################

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH  += .. 
INCLUDEPATH += ..
OBJECTS_DIR  = .
DESTDIR      = ../tmp
TARGET       = $$LIB

isEmpty(SRC_TARGET) {
  SRC_TARGET = $$LIB
}

!contains(BUILD_OS, WIN32) {
  QMAKE_AR     = tar -czf
  QMAKE_RANLIB = 
}

