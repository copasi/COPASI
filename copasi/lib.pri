######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2006/06/20 13:16:12 $  
######################################################################

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH += .. 
INCLUDEPATH += ..
OBJECTS_DIR = .
DESTDIR = ../lib
TARGET = $$LIB

isEmpty(SRC_TARGET) {
  SRC_TARGET = $$LIB
}

