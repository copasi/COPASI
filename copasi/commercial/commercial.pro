# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/commercial.pro,v $ 
#   $Revision: 1.2.2.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/03/03 18:09:55 $ 
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
# $Revision: 1.2.2.1 $ $Author: shoops $ $Date: 2010/03/03 18:09:55 $  
######################################################################

#Input
HEADERS += Cmd5.h \
           CRegistration.h \
           BigInt.h \
           GenericDecode.h 

SOURCES += Cmd5.cpp \
           CRegistration.cpp \
           BigInt.c \
           GenericDecode.c

include(../lib.pri)
include(../common.pri)

#The following line was inserted by qt3to4
QT +=  qt3support 
