# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/sensitivities.pro,v $ 
#   $Revision: 1.8 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/07/16 19:02:49 $ 
# End CVS Header 

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.8 $ $Author: shoops $ $Date: 2010/07/16 19:02:49 $
######################################################################

LIB = sensitivities

# Input
HEADERS += CSensMethod.h \
           CSensProblem.h \
           CSensTask.h

SOURCES += CSensMethod.cpp \
           CSensProblem.cpp \
           CSensTask.cpp

include(../lib.pri)
include(../common.pri)
