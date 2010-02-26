# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/semantic-test-suite/semantic-test-suite.pro,v $ 
#   $Revision: 1.16.2.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/02/26 16:50:25 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.16.2.1 $ $Author: shoops $ $Date: 2010/02/26 16:50:25 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

include(../copasi/common.pri)

DEPENDPATH += ../copasi/ 
INCLUDEPATH += ..
INCLUDEPATH += ../copasi

include(../copasi/app.pri)

COPASI_LIBS += $${COPASI_LIBS_SE}

contains(BUILD_OS, WIN32) {
  CONFIG += console

  debug {
    LIBS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/debug/", ../copasi/lib/debug/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/debug/", ../copasi/lib/debug/, .lib)
  }

  release {
    LIBS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/release/", ../copasi/lib/release/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/release/", ../copasi/lib/release/, .lib)
  }

  
  LIBS += delayimp.lib
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
