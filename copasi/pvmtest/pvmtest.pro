# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/pvmtest/pvmtest.pro,v $ 
#   $Revision: 1.3.30.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/03/03 18:10:00 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.3.30.1 $ $Author: shoops $ $Date: 2010/03/03 18:10:00 $  
######################################################################

TEMPLATE = app

DEPENDPATH += .. 
INCLUDEPATH += ..

# Input
HEADERS += 

SOURCES += pvmtest.cpp

include(../common.pri)

contains(BUILD_OS, WIN32) {
  LIBS += ../lib/COPASISE.lib
} else {
  # The order of libs is important 
  LIBS = -L../lib \
         -lCOPASISE \
         $${LIBS}

  TARGETDEPS += ../lib/libCOPASISE.a
}
