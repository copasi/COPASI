#TEMPLATE	= app
LANGUAGE	= C++

include(../lib.pri)

LIB= wizard
CONFIG	+= qt 

#SOURCES	+= main.cpp

FORMS	= wizard.ui

unix {
  UI_DIR = .
  MOC_DIR = .
  OBJECTS_DIR = .
}



