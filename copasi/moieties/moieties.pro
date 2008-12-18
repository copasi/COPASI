# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/moieties.pro,v $
#   $Revision: 1.4 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/12/18 18:59:02 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2008/12/18 18:59:02 $
######################################################################

LIB = moieties

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CMoietiesMethod.h
HEADERS += CMoietiesProblem.h
HEADERS += CMoietiesTask.h

SOURCES += CMoietiesMethod.cpp
SOURCES += CMoietiesProblem.cpp
SOURCES += CMoietiesTask.cpp

DISTFILES += moieties.vcproj
#The following line was inserted by qt3to4
QT +=  qt3support 
