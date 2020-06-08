// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CUpDownSubwidget.h"
#include "copasi/resourcesUI/CQIconResource.h"

/*
 *  Constructs a CUpDownSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CUpDownSubwidget::CUpDownSubwidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
  : QWidget(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CUpDownSubwidget::~CUpDownSubwidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CUpDownSubwidget::init()
{
  setIndex(0, true, true);
  enableCopy(false);

  toolButtonDel->setIcon(CQIconResource::icon(CQIconResource::editDelete));
  toolButtonUp->setIcon(CQIconResource::icon(CQIconResource::moveUp));
  toolButtonCopy->setIcon(CQIconResource::icon(CQIconResource::editCopy));
  toolButtonDown->setIcon(CQIconResource::icon(CQIconResource::moveDown));
}

void CUpDownSubwidget::slotCopy()
{
  emit copy(mIndex);
}

void CUpDownSubwidget::slotUp()
{
  emit up(mIndex);
}

void CUpDownSubwidget::slotDown()
{
  emit down(mIndex);
}

void CUpDownSubwidget::slotDel()
{
  emit del(mIndex);
}

void CUpDownSubwidget::enableCopy(const bool & enable)
{
  if (enable) toolButtonCopy->show();
  else toolButtonCopy->hide();
}

void CUpDownSubwidget::setIndex(int index, bool isFirst, bool isLast)
{
  mIndex = index;

  if ((mIndex == 0) || (isFirst))
    toolButtonUp->setEnabled(false);
  else
    toolButtonUp->setEnabled(true);

  if (isLast)
    toolButtonDown->setEnabled(false);
  else
    toolButtonDown->setEnabled(true);
}

int CUpDownSubwidget::getIndex() const
{
  return mIndex;
}
