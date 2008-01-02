# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/semantic-test-suite/semantic-test-suite.pro,v $ 
#   $Revision: 1.13 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/01/02 10:15:53 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.13 $ $Author: gauges $ $Date: 2008/01/02 10:15:53 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

include(../copasi/common.pri)

DEPENDPATH += ../copasi/ 
INCLUDEPATH += ..
INCLUDEPATH += ../copasi

COPASI_LIBS += COPASISE

contains(BUILD_OS, WIN32) {
  LIBS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/", ../copasi/lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/", ../copasi/lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  LIBS = $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a) \
         $${LIBS}
  
  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}


# Input
HEADERS += 

SOURCES += copasi_wrapper.cpp
