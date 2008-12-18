# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CopasiDataModel.pro,v $ 
#   $Revision: 1.6 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/12/18 17:28:01 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2008/12/18 17:28:01 $
######################################################################

LIB = copasiDM
SRC_TARGET = CopasiDataModel

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CCopasiDataModel.h

SOURCES += CCopasiDataModel.cpp


DISTFILES += CopasiDataModel.vcproj
#The following line was inserted by qt3to4
QT +=  qt3support 
