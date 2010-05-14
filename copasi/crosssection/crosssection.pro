# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/crosssection.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2010/05/14 22:20:55 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

LIB = crosssection

# Input
HEADERS += CCrossSectionMethod.h \
           CCrossSectionProblem.h \
           CCrossSectionTask.h

SOURCES += CCrossSectionMethod.cpp \
           CCrossSectionProblem.cpp \
           CCrossSectionTask.cpp

include(../lib.pri)
include(../common.pri)

#The following line was inserted by qt3to4
#QT +=  qt3support
