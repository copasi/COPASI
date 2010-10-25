# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/crosssection/crosssection.pro,v $ 
#   $Revision: 1.1.2.1 $ 
#   $Name:  $ 
#   $Author: aekamal $ 
#   $Date: 2010/10/25 16:12:47 $ 
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

