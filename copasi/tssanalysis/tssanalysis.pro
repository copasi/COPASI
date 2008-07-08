# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/tssanalysis.pro,v $
#   $Revision: 1.7 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/07/08 16:06:30 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2008/07/08 16:06:30 $
######################################################################

LIB = tssanalysis

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CILDMMethod.h \
           CILDMModifiedMethod.h \
           CCSPMethod.h \
	       CTSSAMethod.h \
           CTSSAProblem.h \
           CTSSATask.h

SOURCES += CILDMMethod.cpp \
           CILDMModifiedMethod.cpp \
           CCSPMethod.cpp \
	       CTSSAMethod.cpp \
           CTSSAProblem.cpp \
           CTSSATask.cpp


DISTFILES += tssanalysis.vcproj
