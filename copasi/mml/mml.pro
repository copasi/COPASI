# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/mml/Attic/mml.pro,v $ 
#   $Revision: 1.6 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/07/08 16:06:28 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.6 $ $Author: shoops $ $Date: 2008/07/08 16:06:28 $
######################################################################

LIB = mml

include(../lib.pri)
include(../common.pri)

CONFIG += qt

# Input
HEADERS += qtmmlwidget.h
SOURCES += qtmmlwidget.cpp


DISTFILES += MathML.vcproj
