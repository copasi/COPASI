// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CUpDownSubwidget.cpp,v $
//   $Revision: 1.9.2.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/13 21:46:50 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CUpDownSubwidget.h"
#include "CQIcons.h"

/*
 *  Constructs a CUpDownSubwidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CUpDownSubwidget::CUpDownSubwidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
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

  toolButtonDel->setIcon(CQIcons::getIcon(CQIcons::Delete));
  toolButtonUp->setIcon(CQIcons::getIcon(CQIcons::Up));
  toolButtonCopy->setIcon(CQIcons::getIcon(CQIcons::Copy));
  toolButtonDown->setIcon(CQIcons::getIcon(CQIcons::Down));

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
