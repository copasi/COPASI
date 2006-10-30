######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2006/10/30 21:12:15 $  
######################################################################

include(../common.pri)

TEMPLATE = app

DEPENDPATH += .. 
INCLUDEPATH += ..

contains(BUILD_OS, WIN32) {
  LIBS += ../lib/COPASISE.lib
} else {
  # The order of libs is important 
  LIBS = -L../lib \
         -lCOPASISE \
         $${LIBS}

  TARGETDEPS += ../lib/libCOPASISE.a
}

# Input
HEADERS += 

SOURCES += pvmtest.cpp

