# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/unittests.pro,v $ 
#   $Revision: 1.1.2.2 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/02/15 13:11:24 $ 
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
           test000001.hpp \
           test000002.hpp \
           test000003.hpp \
           test000004.hpp \
           test000005.hpp \
           test000006.hpp \
           test000007.hpp \
           test000008.hpp \
           test000009.hpp \
           test000010.hpp \
           test000011.hpp \
           test000012.hpp \
           test000013.hpp \
           test000014.hpp \
           test000015.hpp \
           test000016.hpp \
           test000017.hpp \
           test000018.hpp \
           test000019.hpp \
           test000020.hpp 


SOURCES += utilities.cpp \
           test000001.cpp \ 
           test000002.cpp \ 
           test000003.cpp \ 
           test000004.cpp \ 
           test000005.cpp \ 
           test000006.cpp \ 
           test000007.cpp \ 
           test000008.cpp \ 
           test000009.cpp \ 
           test000010.cpp \ 
           test000011.cpp \ 
           test000012.cpp \ 
           test000013.cpp \ 
           test000014.cpp \ 
           test000015.cpp \ 
           test000016.cpp \ 
           test000017.cpp \ 
           test000018.cpp \ 
           test000019.cpp \ 
           test000020.cpp \ 
           test.cpp


