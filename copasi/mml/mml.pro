# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mml/Attic/mml.pro,v $ 
#   $Revision: 1.7 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/12/18 18:57:58 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2008/12/18 18:57:58 $
######################################################################

LIB = mml

include(../lib.pri)
include(../common.pri)

CONFIG += qt

# Input
HEADERS += qtmmlwidget.h
SOURCES += qtmmlwidget.cpp


DISTFILES += MathML.vcproj
#The following line was inserted by qt3to4
QT += xml  opengl qt3support 
