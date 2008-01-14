# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/stochastic-testsuite/stochastic-testsuite.pro,v $ 
#   $Revision: 1.8.12.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/01/14 09:52:30 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.8.12.1 $ $Author: gauges $ $Date: 2008/01/14 09:52:30 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

include(../copasi/common.pri)

DEPENDPATH += ../copasi/ 
INCLUDEPATH += ../copasi/
INCLUDEPATH += ..

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
