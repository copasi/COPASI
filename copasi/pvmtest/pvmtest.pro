# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/pvmtest/pvmtest.pro,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/05/25 15:12:20 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2011/05/25 15:12:20 $  
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

  POST_TARGETDEPS += ../lib/libCOPASISE.a
}
