######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2003/06/05 18:49:12 $  
######################################################################

include(../common.pri)

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH += .. 
INCLUDEPATH += ..
OBJECTS_DIR = .
DESTDIR = ../lib
TARGET = $$LIB
