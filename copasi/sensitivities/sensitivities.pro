# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/sensitivities.pro,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/07/08 16:06:33 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2008/07/08 16:06:33 $
######################################################################

LIB = sensitivities

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CSensMethod.h \
           CSensProblem.h \
           CSensTask.h

SOURCES += CSensMethod.cpp \
           CSensProblem.cpp \
           CSensTask.cpp


DISTFILES += sensitivities.vcproj
