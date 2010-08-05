# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/test/test.pro,v $ 
#   $Revision: 1.10 $ 
#   $Name:  $ 
#   $Author: jpahle $ 
#   $Date: 2010/08/05 16:17:18 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.10 $ $Author: jpahle $ $Date: 2010/08/05 16:17:18 $  
######################################################################

TEMPLATE = app
# Input
HEADERS += 

SOURCES += test.cpp 

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

contains(BUILD_OS, WIN32) {
  COPASI_LIBS += ../lib/COPASISE.lib

  LIBS += $$COPASI_LIBS
  TARGETDEPS += $$COPASI_LIBS
} else {
  # The order of objects is important 
  LIBS += -L ../lib -lCOPASISE
  
  TARGETDEPS += $$COPASI_LIBS
}


