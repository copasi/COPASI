TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH += .. $${LIB}
OBJECTS_DIR = $${LIB}
DESTDIR = lib

macx{
  INCLUDEPATH += /System/Library/Frameworks/vecLib.framework/Headers
  DEFINES += __MacOsX__
}
