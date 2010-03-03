# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.pro,v $
#   $Revision: 1.14.2.2 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/03/03 18:10:00 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

LANGUAGE	= C++

LIB= wizard

FORMS3	= wizard.ui

DISTFILES += help_html/figures/*.png \
             help_html/*.html
             
include(../lib.pri)

CONFIG += qt 

include(../common.pri)

#The following line was inserted by qt3to4
QT += xml  opengl qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3
