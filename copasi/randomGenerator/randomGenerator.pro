# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/randomGenerator/randomGenerator.pro,v $ 
#   $Revision: 1.9 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/12/18 19:04:51 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.9 $ $Author: shoops $ $Date: 2008/12/18 19:04:51 $
######################################################################

LIB = randomGenerator

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += Cmt19937.h \
           Cr250.h \
           CRandom.h

SOURCES += Cmt19937.cpp \
           Cr250.cpp \
           CRandom.cpp


DISTFILES += randomGenerator.vcproj
#The following line was inserted by qt3to4
QT +=  qt3support 
