# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/resourcesUI/resourcesUI.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2012/03/15 19:55:24 $ 
# End CVS Header 

# Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

LIB = resourcesUI

DISTFILES = resourcesUI.pro
DISTFILES += images/*.*

RESOURCES += copasi.qrc

HEADERS   += CQIconResource.h

SOURCES   += CQIconResource.cpp

include(../lib.pri)

CONFIG += qt

include(../common.pri)
include(../srcDistribution.pri)

