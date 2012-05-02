// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQProgressDialog.cpp,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/02 20:34:51 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQProgressDialog.h"

#include <QtCore/QVariant>
#include <QtGui/QApplication>
#include <QtCore/QTimer>

#include "copasiui3window.h"

#include "resourcesUI/CQIconResource.h"

/*
 *  Constructs a CQProgressDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CQProgressDialog::CQProgressDialog(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setModal(modal);
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQProgressDialog::~CQProgressDialog()
{
  // no need to delete child widgets, Qt does it all for us
}

bool CQProgressDialog::insertProgressItem(CQProgressItem * pItem)
{
  if (mItemCount == 0) mpLine->show();

  vboxLayout->removeItem(mpSpacer);
  vboxLayout->addWidget(pItem);
  vboxLayout->addItem(mpSpacer);

  pItem->show();

  mItemCount++;
  return true;
}

bool CQProgressDialog::removeProgressItem(CQProgressItem * pItem)
{
  vboxLayout->removeWidget(pItem);

  mItemCount--;

  if (mItemCount == 0) mpLine->hide();

  return true;
}

void CQProgressDialog::init()
{
  mpBtnPause->setIcon(CQIconResource::icon(CQIconResource::playerPause));
  mpBtnContinue->setIcon(CQIconResource::icon(CQIconResource::playerStart));
  mpBtnStop->setIcon(CQIconResource::icon(CQIconResource::playerStop));

  mpLine->hide();
  //  mpBtnPause->hide();
  //  mpBtnContinue->hide();

  mpBtnContinue->setEnabled(false);

  mItemCount = 0;

  mPause = false;
  mProceed = true;

  QTimer::singleShot(1500, this, SLOT(timerShow()));

  return;
}

void CQProgressDialog::btnContinuePressed()
{
  mPause = false;

  mpBtnPause->setEnabled(true);
  mpBtnContinue->setEnabled(false);
}

void CQProgressDialog::btnPausePressed()
{
  mPause = true;

  mpBtnPause->setEnabled(false);
  mpBtnContinue->setEnabled(true);
}

void CQProgressDialog::btnStopPressed()
{
  mPause = false;
  mProceed = false;

  mpBtnPause->setEnabled(false);
  mpBtnContinue->setEnabled(false);
  mpBtnStop->setEnabled(false);
}

void CQProgressDialog::timerShow()
{
  if (CopasiUI3Window::getMainWindow() != NULL &&
      CopasiUI3Window::getMainWindow()->messageShown())
    {
      QTimer::singleShot(1500, this, SLOT(timerShow()));
    }
  else
    {
      show();
    }
}
