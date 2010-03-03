# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mml/Attic/mml.pro,v $ 
#   $Revision: 1.7.2.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/03/03 18:09:56 $ 
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
# $Revision: 1.7.2.2 $ $Author: shoops $ $Date: 2010/03/03 18:09:56 $
######################################################################

LIB = mml

CONFIG += qt

# Input
HEADERS += qtmmlwidget.h
SOURCES += qtmmlwidget.cpp

include(../lib.pri)
include(../common.pri)

#The following line was inserted by qt3to4
QT += xml  opengl qt3support 
