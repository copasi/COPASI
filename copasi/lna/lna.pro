# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lna/lna.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: jpahle $ 
#   $Date: 2011/05/24 17:33:45 $ 
# End CVS Header 

# Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

LIB = lna
DISTFILES = lna.pro

# Input
HEADERS += CLNAMethod.h \
           CLNAProblem.h \
	   CLNATask.h

SOURCES += CLNAMethod.cpp \
           CLNAProblem.cpp \
	   CLNATask.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)

#The following line was inserted by qt3to4
QT +=  qt3support 
