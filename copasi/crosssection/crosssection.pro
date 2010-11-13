# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/crosssection.pro,v $ 
#   $Revision: 1.1.2.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/11/13 16:55:55 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

LIB = crosssection
DISTFILES = crosssection.pro

# Input
HEADERS += CCrossSectionMethod.h \
           CCrossSectionProblem.h \
           CCrossSectionTask.h

SOURCES += CCrossSectionMethod.cpp \
           CCrossSectionProblem.cpp \
           CCrossSectionTask.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
