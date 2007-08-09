# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/unittests/unittests.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2007/08/09 05:24:58 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

TEMPLATE = app

CONFIG -= qt

include(../../common.pri)

contains(BUILD_OS, WIN32) {
#  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

#  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
}

contains(BUILD_OS, Linux) {
#  LIBS = -L../lib \
#         $$join(COPASI_LIBS, " -l", -l) \
#         $${LIBS}

!isEmpty(CPPUNIT_PATH)
{
  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
  
  INCLUDEPATH += $${CPPUNIT_PATH}/include
}

#  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
#  QMAKE_LFLAGS += -z rescan

#  LIBS = -L../lib \
#         $$join(COPASI_LIBS, " -l", -l) \
#         $${LIBS}

#  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
#  QMAKE_LFLAGS += -Wl,-search_paths_first
#  
#
#  LIBS = $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a) \
#         $${LIBS}

!isEmpty(CPPUNIT_PATH)
{
  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
  
  INCLUDEPATH += $${CPPUNIT_PATH}/include
}

#  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}


# Input
HEADERS +=  test_expression_comparison.hpp \
            test_node_conversion.hpp \
            test_normalform.hpp 

SOURCES += test.cpp \
           test_expression_comparison.cpp \
           test_node_conversion.cpp \
           test_normalform.cpp 


