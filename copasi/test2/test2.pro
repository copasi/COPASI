# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test2/test2.pro,v $ 
#   $Revision: 1.4.30.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/03/03 18:10:02 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.4.30.1 $ $Author: shoops $ $Date: 2010/03/03 18:10:02 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

# Input
HEADERS += CNormalItem.h \
           CNormalItemPower.h\
           CNormalProduct.h \
	       CNormalSum.h \
           CNormalLcm.h \
           CNormalFraction.h \
           CNormalTranslation.h\

	    
SOURCES += CNormalItem.cpp \
           CNormalItemPower.cpp\
           CNormalProduct.cpp \
           CNormalSum.cpp \
           CNormalLcm.cpp \
           CNormalFraction.cpp \
           CNormalTranslation.cpp\
           test.cpp

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

COPASI_LIBS = COPASISE

contains(BUILD_OS, WIN32) {
  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  LIBS = $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a) \
         $${LIBS}
  
  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}
