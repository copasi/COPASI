######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2006/10/30 21:12:11 $  
######################################################################

include(../common.pri)

TEMPLATE = app

DEPENDPATH += .. 
INCLUDEPATH += ..

contains(BUILD_OS, WIN32) {
  COPASI_LIBS += ../lib/COPASISE.lib

  LIBS += $$COPASI_LIBS
  TARGETDEPS += $$COPASI_LIBS
} else {
  # The order of objects is important 
  LIBS += -L ../lib -lCAPASISE
  
  TARGETDEPS += $$COPASI_LIBS
}

# Input
HEADERS += 

SOURCES += test.cpp \

