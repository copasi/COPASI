# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiDataModel/CopasiDataModel.pro,v $ 
#   $Revision: 1.9 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/03/07 19:27:11 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.9 $ $Author: shoops $ $Date: 2011/03/07 19:27:11 $
######################################################################

LIB = copasiDM
SRC_TARGET = CopasiDataModel
DISTFILES = CopasiDataModel.pro

# Input
HEADERS += CCopasiDataModel.h

SOURCES += CCopasiDataModel.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
