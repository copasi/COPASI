######################################################################
# $Revision: 1.1.1.1 $ $Author: anuragr $ $Date: 2004/10/26 15:17:43 $  
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
