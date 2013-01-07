# Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

LIB = resourcesUI

DISTFILES += resourcesUI.pro
DISTFILES += copasi.qrc
DISTFILES += images/*.*

RESOURCES += copasi.qrc

HEADERS   += CQIconResource.h

SOURCES   += CQIconResource.cpp

include(../lib.pri)

CONFIG += qt

include(../common.pri)
include(../srcDistribution.pri)

