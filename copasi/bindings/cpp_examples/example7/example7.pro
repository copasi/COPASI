# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/cpp_examples/example7/example7.pro,v $ 
#   $Revision: 1.4 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/05/25 15:12:19 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

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

include(../../../app.pri)

COPASI_LIBS += $${COPASI_LIBS_SE}

contains(BUILD_OS, WIN32) {
  CONFIG += console

  debug {
    LIBS += $$join(COPASI_LIBS, ".lib  ../../../lib/debug/", ../../../lib/debug/, .lib)
    POST_TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../../../lib/debug/", ../../../lib/debug/, .lib)
  }

  release {
    LIBS += $$join(COPASI_LIBS, ".lib  ../../../lib/release/", ../../../lib/release/, .lib)
    POST_TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../../../lib/release/", ../../../lib/release/, .lib)
  }
  
  LIBS += delayimp.lib
}

contains(BUILD_OS, Linux) {
  LIBS = -L../../../../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../../../lib/lib", ../../../lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../../../lib/lib", ../../../lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  LIBS = $$join(COPASI_LIBS, ".a  ../../../lib/lib", ../../../lib/lib, .a) \
         $${LIBS}
  
  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../../../lib/lib", ../../../lib/lib, .a)
}


# Input
HEADERS += 

SOURCES += example7.cpp
