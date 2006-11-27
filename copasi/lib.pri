######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2006/11/27 17:30:29 $  
######################################################################

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH  += .. 
INCLUDEPATH += ..
OBJECTS_DIR  = .
DESTDIR      = ../lib
TARGET       = $$LIB

isEmpty(SRC_TARGET) {
  SRC_TARGET = $$LIB
}

!contains(BUILD_OS, WIN32) {
  QMAKE_AR     = tar -czf
  QMAKE_RANLIB = 
}

