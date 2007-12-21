# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/tssanalysis.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: isurovts $ 
#   $Date: 2007/12/21 11:43:59 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.2 $ $Author: isurovts $ $Date: 2007/12/21 11:43:59 $  
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


DISTFILES += tssanalysis.dsp
