# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mml/Attic/mml.pro,v $ 
#   $Revision: 1.8.2.3 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/11/13 16:55:57 $ 
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
# $Revision: 1.8.2.3 $ $Author: shoops $ $Date: 2010/11/13 16:55:57 $
######################################################################

LIB = mml
DISTFILES = mml.pro

# Input
HEADERS += qtmmlwidget.h
SOURCES += qtmmlwidget.cpp

include(../lib.pri)

CONFIG += qt

include(../common.pri)
include(../srcDistribution.pri)

#The following line was inserted by qt3to4
QT += xml  opengl 
