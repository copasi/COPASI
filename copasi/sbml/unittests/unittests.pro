# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/unittests.pro,v $ 
#   $Revision: 1.1.2.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/02/14 10:52:44 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

TEMPLATE = app

CONFIG -= qt

LIBS += -lCOPASISE -L../../lib/ 

include(../../common.pri)

INCLUDEPATH += ../../..

contains(BUILD_OS, WIN32) {
#  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

#  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
}

contains(BUILD_OS, Linux) {
!isEmpty(CPPUNIT_PATH) {
  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
  INCLUDEPATH += $${CPPUNIT_PATH}/include

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

   PRE_TARGETDEPS += ../../lib/libCOPASISE.a
}

}

contains(BUILD_OS, SunOS) {
#  QMAKE_LFLAGS += -z rescan

#  LIBS = -L../lib \
#         $$join(COPASI_LIBS, " -l", -l) \
#         $${LIBS}

#  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
!isEmpty(CPPUNIT_PATH) {
  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
  INCLUDEPATH += $${CPPUNIT_PATH}/include

  LIBS = $$join(COPASI_LIBS, ".a  ../../lib/lib", ../../lib/lib, .a) \
         $${LIBS}
   
   PRE_TARGETDEPS += ../../lib/libCOPASISE.a

}

}


# Input
HEADERS += utilities.hpp \
           test000001.hpp 


SOURCES += utilities.cpp \
           test000001.cpp \ 
           test.cpp


