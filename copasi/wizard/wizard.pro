# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.pro,v $
#   $Revision: 1.16 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/07/16 19:06:34 $
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

HEADERS = wizard.h

SOURCES = wizard.cpp

FORMS = wizard.ui

DISTFILES += help_html/figures/*.png \
             help_html/*.html
             
include(../lib.pri)

CONFIG += qt 

include(../common.pri)

QT += qt3support
