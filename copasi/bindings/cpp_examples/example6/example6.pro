# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/cpp_examples/example6/example6.pro,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2009/10/13 17:19:37 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

TEMPLATE = app

CONFIG -= qt

include(../../../common.pri)

DEPENDPATH += ../../.. 
INCLUDEPATH += ../../../..
INCLUDEPATH += ../../..

COPASI_LIBS += COPASISE

contains(BUILD_OS, WIN32) {
  CONFIG += console

  debug {
    LIBS += $$join(COPASI_LIBS, ".lib  ../../../lib/debug/", ../../../lib/debug/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../../../lib/debug/", ../../../lib/debug/, .lib)
  }

  release {
    LIBS += $$join(COPASI_LIBS, ".lib  ../../../lib/release/", ../../../lib/release/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../../../lib/release/", ../../../lib/release/, .lib)
  }
  
  LIBS += delayimp.lib
}

contains(BUILD_OS, Linux) {
  LIBS = -L../../../../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../../../lib/lib", ../../../lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../../../lib/lib", ../../../lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  LIBS = $$join(COPASI_LIBS, ".a  ../../../lib/lib", ../../../lib/lib, .a) \
         $${LIBS}
  
  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../../../lib/lib, .a)
}


# Input
HEADERS += 

SOURCES += example6.cpp
