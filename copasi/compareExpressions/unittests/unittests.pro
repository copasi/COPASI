# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/unittests.pro,v $ 
#   $Revision: 1.9 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/03/06 11:28:49 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

TEMPLATE = app

CONFIG -= qt

include(../../common.pri)

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
HEADERS +=  test_expression_comparison.hpp \
            test_node_conversion.hpp \
            test_cnormallogical.hpp \
            test_normalform.hpp 

SOURCES += test.cpp \
           test_expression_comparison.cpp \
           test_node_conversion.cpp \
           test_cnormallogical.cpp \
           test_normalform.cpp 


