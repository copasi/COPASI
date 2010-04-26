# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/commercial.pro,v $ 
#   $Revision: 1.2.2.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/04/26 17:40:54 $ 
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
# $Revision: 1.2.2.2 $ $Author: shoops $ $Date: 2010/04/26 17:40:54 $  
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
