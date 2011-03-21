# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/unittests.pro,v $ 
#   $Revision: 1.32.2.4 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2011/03/21 11:32:55 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

TEMPLATE = app

CONFIG -= qt

include(../../common.pri)
include(../../app.pri)

COPASI_LIBS += $${COPASI_LIBS_SE}

INCLUDEPATH += ../../..

contains(BUILD_OS, WIN32) {
#  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

#  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = $$join(COPASI_LIBS, ".a  ../../lib/lib", ../../lib/lib, .a) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../../lib/lib", ../../lib/lib, .a)

!isEmpty(CPPUNIT_PATH) {
  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
  INCLUDEPATH += $${CPPUNIT_PATH}/include
}

}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan
  LIBS += -lsocket
  LIBS += -lnsl

!isEmpty(CPPUNIT_PATH) {
  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
  INCLUDEPATH += $${CPPUNIT_PATH}/include

  LIBS = $$join(COPASI_LIBS, ".a  ../../lib/lib", ../../lib/lib, .a) \
         $${LIBS}
}

}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first

  LIBS = $$join(COPASI_LIBS, ".a  ../../lib/lib", ../../lib/lib, .a) \
         $${LIBS}
   
  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../../lib/lib", ../../lib/lib, .a)
  
!isEmpty(CPPUNIT_PATH) {
  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
  INCLUDEPATH += $${CPPUNIT_PATH}/include

}

}


# Input
HEADERS += utilities.hpp
HEADERS += test000001.hpp
HEADERS += test000002.hpp
HEADERS += test000003.hpp
HEADERS += test000004.hpp
HEADERS += test000005.hpp
HEADERS += test000006.hpp
HEADERS += test000007.hpp
HEADERS += test000008.hpp
HEADERS += test000009.hpp
HEADERS += test000010.hpp
HEADERS += test000011.hpp
HEADERS += test000012.hpp
HEADERS += test000013.hpp
HEADERS += test000014.hpp
HEADERS += test000015.hpp
HEADERS += test000016.hpp
HEADERS += test000017.hpp
HEADERS += test000018.hpp
HEADERS += test000019.hpp
HEADERS += test000020.hpp
HEADERS += test000021.h
HEADERS += test000022.h
HEADERS += test000023.h
HEADERS += test000024.h
HEADERS += test000025.h
HEADERS += test000026.h
HEADERS += test000027.h
HEADERS += test000028.h
HEADERS += test000029.h
HEADERS += test000030.h
HEADERS += test000031.h
HEADERS += test000032.h
HEADERS += test000033.h
HEADERS += test000034.h
HEADERS += test000035.h
HEADERS += test000036.h
HEADERS += test000037.h
HEADERS += test000038.h
HEADERS += test000039.h
HEADERS += test000040.h
HEADERS += test000041.h
HEADERS += test000042.h
HEADERS += test000043.h
HEADERS += test000044.h
HEADERS += test000045.h
HEADERS += test000046.h
HEADERS += test000047.h
HEADERS += test000048.h
HEADERS += test000049.h
HEADERS += test000050.h
HEADERS += test000051.h
HEADERS += test000052.h
HEADERS += test000053.h
HEADERS += test000054.h
HEADERS += test000055.h
HEADERS += test000056.h
HEADERS += test000057.h
HEADERS += test000058.h
HEADERS += test000059.h
HEADERS += test000060.h
HEADERS += test000061.h
HEADERS += test000062.h
HEADERS += test000063.h
HEADERS += test000064.h
HEADERS += test000065.h
HEADERS += test000066.h
HEADERS += test000067.h
HEADERS += test000068.h
HEADERS += test000069.h
HEADERS += test000070.h
HEADERS += test000071.h
HEADERS += test000072.h
HEADERS += test000073.h
HEADERS += test000074.h
HEADERS += test000075.h
HEADERS += test000076.h
HEADERS += test000077.h
HEADERS += test000078.h
HEADERS += test000079.h
HEADERS += test000080.h
HEADERS += test000081.h
HEADERS += test000082.h
HEADERS += test000083.h
HEADERS += test000084.h
HEADERS += test000085.h
HEADERS += test000086.h
HEADERS += test000087.h
HEADERS += test000088.h
HEADERS += test000089.h
HEADERS += test000090.h
HEADERS += test000091.h
HEADERS += test000092.h
HEADERS += test000093.h
HEADERS += test000094.h
HEADERS += test000095.h
HEADERS += test000096.h 


SOURCES += utilities.cpp
SOURCES += test000001.cpp
SOURCES += test000002.cpp
SOURCES += test000003.cpp
SOURCES += test000004.cpp
SOURCES += test000005.cpp
SOURCES += test000006.cpp
SOURCES += test000007.cpp
SOURCES += test000008.cpp
SOURCES += test000009.cpp
SOURCES += test000010.cpp
SOURCES += test000011.cpp
SOURCES += test000012.cpp
SOURCES += test000013.cpp
SOURCES += test000014.cpp
SOURCES += test000015.cpp
SOURCES += test000016.cpp
SOURCES += test000017.cpp
SOURCES += test000018.cpp
SOURCES += test000019.cpp
SOURCES += test000020.cpp
SOURCES += test000021.cpp
SOURCES += test000022.cpp
SOURCES += test000023.cpp
SOURCES += test000024.cpp
SOURCES += test000025.cpp
SOURCES += test000026.cpp
SOURCES += test000027.cpp
SOURCES += test000028.cpp
SOURCES += test000029.cpp
SOURCES += test000030.cpp
SOURCES += test000031.cpp
SOURCES += test000032.cpp
SOURCES += test000033.cpp
SOURCES += test000034.cpp
SOURCES += test000035.cpp
SOURCES += test000036.cpp
SOURCES += test000037.cpp
SOURCES += test000038.cpp
SOURCES += test000039.cpp
SOURCES += test000040.cpp
SOURCES += test000041.cpp
SOURCES += test000042.cpp
SOURCES += test000043.cpp
SOURCES += test000044.cpp
SOURCES += test000045.cpp
SOURCES += test000046.cpp
SOURCES += test000047.cpp
SOURCES += test000048.cpp
SOURCES += test000049.cpp
SOURCES += test000050.cpp
SOURCES += test000051.cpp
SOURCES += test000052.cpp
SOURCES += test000053.cpp
SOURCES += test000054.cpp
SOURCES += test000055.cpp
SOURCES += test000056.cpp
SOURCES += test000057.cpp
SOURCES += test000058.cpp
SOURCES += test000059.cpp
SOURCES += test000060.cpp
SOURCES += test000061.cpp
SOURCES += test000062.cpp
SOURCES += test000063.cpp
SOURCES += test000064.cpp
SOURCES += test000065.cpp
SOURCES += test000066.cpp
SOURCES += test000067.cpp
SOURCES += test000068.cpp
SOURCES += test000069.cpp
SOURCES += test000070.cpp
SOURCES += test000071.cpp
SOURCES += test000072.cpp
SOURCES += test000073.cpp
SOURCES += test000074.cpp
SOURCES += test000075.cpp
SOURCES += test000076.cpp
SOURCES += test000077.cpp
SOURCES += test000078.cpp
SOURCES += test000079.cpp
SOURCES += test000080.cpp
SOURCES += test000081.cpp
SOURCES += test000082.cpp
SOURCES += test000083.cpp
SOURCES += test000084.cpp
SOURCES += test000085.cpp
SOURCES += test000086.cpp
SOURCES += test000087.cpp
SOURCES += test000088.cpp
SOURCES += test000089.cpp
SOURCES += test000090.cpp
SOURCES += test000091.cpp
SOURCES += test000092.cpp
SOURCES += test000093.cpp
SOURCES += test000094.cpp
SOURCES += test000095.cpp
SOURCES += test000096.cpp
SOURCES += test.cpp
