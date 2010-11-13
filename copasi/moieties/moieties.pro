# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/moieties.pro,v $
#   $Revision: 1.6.2.1 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/11/13 14:53:12 $
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
# $Revision: 1.6.2.1 $ $Author: shoops $ $Date: 2010/11/13 14:53:12 $
######################################################################

LIB = moieties

# Input
HEADERS += CMoietiesMethod.h
HEADERS += CMoietiesProblem.h
HEADERS += CMoietiesTask.h

SOURCES += CMoietiesMethod.cpp
SOURCES += CMoietiesProblem.cpp
SOURCES += CMoietiesTask.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
