# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/stochastic-testsuite/stochastic-testsuite.pro,v $ 
#   $Revision: 1.13 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/05/25 15:12:17 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
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
# $Revision: 1.13 $ $Author: shoops $ $Date: 2011/05/25 15:12:17 $  
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
  LIBS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/", ../copasi/lib/, .lib)

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/", ../copasi/lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  LIBS = $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a) \
         $${LIBS}
  
  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}


# Input
HEADERS += 

SOURCES += copasi_wrapper.cpp
