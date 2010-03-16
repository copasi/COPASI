# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/tssanalysis.pro,v $
#   $Revision: 1.11 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/03/16 18:57:44 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

LIB = tssanalysis

# Input
HEADERS += CILDMMethod.h \
           CILDMModifiedMethod.h \
	         CTSSAMethod.h \
           CTSSAProblem.h \
           CTSSATask.h \
           CCSPMethod.h

SOURCES += CILDMMethod.cpp \
           CILDMModifiedMethod.cpp \
	         CTSSAMethod.cpp \
           CTSSAProblem.cpp \
           CTSSATask.cpp \
           CCSPMethod.cpp

include(../lib.pri)
include(../common.pri)

           
