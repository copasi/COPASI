// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "CQProgressDialog.h"

#include <QtCore/QVariant>
#include <QApplication>
#include <QtCore/QTimer>

#include "copasiui3window.h"

#include "copasi/resourcesUI/CQIconResource.h"

/*
 *  Constructs a CQProgressDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be Qt::WindowModal.
 */
CQProgressDialog::CQProgressDialog(QWidget* parent, const char* name, Qt::WindowModality windowModality, Qt::WindowFlags fl)
  : QDialog(parent, fl)
{
  setObjectName(QString::fromUtf8(name));

  setupUi(this);

  setWindowModality(windowModality);

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

  verticalLayout->removeItem(mpSpacer);
  verticalLayout->addWidget(pItem);
  verticalLayout->addItem(mpSpacer);

  pItem->show();

  mItemCount++;
  return true;
}

bool CQProgressDialog::removeProgressItem(CQProgressItem * pItem)
{
  verticalLayout->removeWidget(pItem);

  mItemCount--;

  if (mItemCount == 0) mpLine->hide();

  return true;
}

void CQProgressDialog::init()
{
  mpBtnPause->setIcon(CQIconResource::icon(CQIconResource::playerPause));
  mpBtnContinue->setIcon(CQIconResource::icon(CQIconResource::playerStart));
  mpBtnStop->setIcon(CQIconResource::icon(CQIconResource::playerStop));
  mpBtnKill->setIcon(CQIconResource::icon(CQIconResource::playerKill));

  mpLine->hide();

  mpBtnContinue->setEnabled(false);
  mpBtnKill->setEnabled(false);

  mItemCount = 0;

  QTimer::singleShot(1500, this, SLOT(timerShow()));

  return;
}

void CQProgressDialog::done(int)
{
  // ignore
}
void CQProgressDialog::accept()
{
  // ignore
}
void CQProgressDialog::reject()
{
  // ignore
}

void CQProgressDialog::btnContinuePressed()
{
  mpBtnPause->setEnabled(true);
  mpBtnContinue->setEnabled(false);
}

void CQProgressDialog::btnPausePressed()
{
  mpBtnPause->setEnabled(false);
  mpBtnContinue->setEnabled(true);
}

void CQProgressDialog::btnStopPressed()
{
  mpBtnPause->setEnabled(false);
  mpBtnContinue->setEnabled(false);
  mpBtnStop->setEnabled(false);
  mpBtnKill->setEnabled(true);
}

void CQProgressDialog::btnKillPressed()
{
  mpBtnPause->setEnabled(false);
  mpBtnContinue->setEnabled(false);
  mpBtnStop->setEnabled(false);
  mpBtnKill->setEnabled(false);
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
