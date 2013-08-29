# Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 




LIB = qlayout
DISTFILES = qlayout.pro

include(../lib.pri)
include(../common.pri)

QT +=  opengl 
CONFIG += qt

HEADERS += \
           CQAnimationControls.h       \
           CQAnimationSettingsEditor.h \
           CQAnimationWindow.h         \
           CQConnectionGraphicsItem.h  \
           CQCopasiAnimation.h         \
           CQCopasiEffect.h            \
           CQCopasiGraphicsItem.h      \
           CQEffectDescription.h       \
           CQEffectDescriptionEdit.h   \
           CQLabelGraphicsItem.h       \
           CQLayoutScene.h             \
           CQLayoutView.h              \
           CQRenderConverter.h         \
           CQRoundedRect.h             \
           CQStyledGraphicsItem.h

SOURCES += \
           CQAnimationControls.cpp       \
           CQAnimationSettingsEditor.cpp \
           CQAnimationWindow.cpp         \
           CQConnectionGraphicsItem.cpp  \
           CQCopasiAnimation.cpp         \
           CQCopasiEffect.cpp            \
           CQCopasiGraphicsItem.cpp      \
           CQEffectDescription.cpp       \
           CQEffectDescriptionEdit.cpp   \
           CQLabelGraphicsItem.cpp       \
           CQLayoutScene.cpp             \
           CQLayoutView.cpp              \
           CQRenderConverter.cpp         \
           CQRoundedRect.cpp             \
           CQStyledGraphicsItem.cpp

FORMS += \
           CQAnimationControls.ui       \
           CQAnimationSettingsEditor.ui \
           CQAnimationWindow.ui         \
           CQEffectDescriptionEdit.ui


DISTFILES += CMakeLists.txt

include(../srcDistribution.pri)
