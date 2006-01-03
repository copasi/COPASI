/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQProgressDialog.ui.h,v $
   $Revision: 1.4.8.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/03 16:10:06 $
   End CVS Header */

#include <qapplication.h>
#include <qtimer.h>

bool CQProgressDialog::insertProgressItem(CQProgressItem * pItem)
{
  if (mItemCount == 0) mpLine->show();

  CQProgressDialogLayout->removeItem(mpSpacer);
  CQProgressDialogLayout->addWidget(pItem);
  CQProgressDialogLayout->addItem(mpSpacer);

  pItem->show();
  qApp->processEvents();

  mItemCount++;
  return true;
}

bool CQProgressDialog::removeProgressItem(CQProgressItem * pItem)
{
  CQProgressDialogLayout->remove(pItem);

  mItemCount--;
  if (mItemCount == 0) mpLine->hide();

  qApp->processEvents();
  return true;
}

void CQProgressDialog::init()
{
  mpLine->hide();
  //  mpBtnPause->hide();
  //  mpBtnContinue->hide();

  mpBtnContinue->setEnabled(false);

  mItemCount = 0;

  mPause = false;
  mProceed = true;

  mpTimer = new QTimer(this);
  mpTimer->start(1500, true);
  connect(mpTimer, SIGNAL(timeout()), this, SLOT(timerShow()));

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
{this->show();}
