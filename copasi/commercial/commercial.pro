# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/commercial.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/12/18 17:25:59 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2008/12/18 17:25:59 $  
######################################################################

include(../lib.pri)
include(../common.pri)

#Input
HEADERS += Cmd5.h \
           CRegistration.h \
           BigInt.h \
           GenericDecode.h 

SOURCES += Cmd5.cpp \
           CRegistration.cpp \
           BigInt.c \
           GenericDecode.c

#The following line was inserted by qt3to4
QT +=  qt3support 
