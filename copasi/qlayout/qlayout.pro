# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = qlayout
DISTFILES = qlayout.pro

include(../lib.pri)
include(../common.pri)

QT +=  opengl 
CONFIG += qt

HEADERS += \
           qanimationcontrols.h       \
           qanimationsettingseditor.h \
           qanimationwindow.h         \
           qconnectiongraphicsitem.h  \
           qcopasianimation.h         \
           qcopasieffect.h            \
           qcopasigraphicsitem.h      \
           qeffectdescription.h       \
           qeffectdescriptionedit.h   \
           qlabelgraphicsitem.h       \
           qlayoutscene.h             \
           qlayoutview.h              \
           qrenderconverter.h         \
           qroundedrect.h             \
           qstyledgraphicsitem.h

SOURCES += \
           qanimationcontrols.cpp       \
           qanimationsettingseditor.cpp \
           qanimationwindow.cpp         \
           qconnectiongraphicsitem.cpp  \
           qcopasianimation.cpp         \
           qcopasieffect.cpp            \
           qcopasigraphicsitem.cpp      \
           qeffectdescription.cpp       \
           qeffectdescriptionedit.cpp   \
           qlabelgraphicsitem.cpp       \
           qlayoutscene.cpp             \
           qlayoutview.cpp              \
           qrenderconverter.cpp         \
           qroundedrect.cpp             \
           qstyledgraphicsitem.cpp

FORMS += \
           qanimationcontrols.ui       \
           qanimationsettingseditor.ui \
           qanimationwindow.ui         \
           qeffectdescriptionedit.ui


DISTFILES += CMakeLists.txt

include(../srcDistribution.pri)
