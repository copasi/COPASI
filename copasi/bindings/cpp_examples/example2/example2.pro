# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/cpp_examples/example2/example2.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2009/03/04 08:16:15 $ 
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
  LIBS += $$join(COPASI_LIBS, ".lib  ../../../lib/", ../../../lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../../../lib/", ../../../lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../copasi/lib \
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

SOURCES += example2.cpp
