# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CopasiDataModel.pro,v $ 
#   $Revision: 1.8.2.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/11/13 14:53:09 $ 
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
# $Revision: 1.8.2.1 $ $Author: shoops $ $Date: 2010/11/13 14:53:09 $
######################################################################

LIB = copasiDM
SRC_TARGET = CopasiDataModel

# Input
HEADERS += CCopasiDataModel.h

SOURCES += CCopasiDataModel.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
