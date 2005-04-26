/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQProgressDialog.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/26 14:29:21 $
   End CVS Header */

#include "qapplication.h"

extern QApplication *pApp;
bool CQProgressDialog::insertProgressItem(CQProgressItem * pItem)
{
  if (mItemCount == 0) mpLine->show();

  CQProgressDialogLayout->removeItem(mpSpacer);
  CQProgressDialogLayout->addWidget(pItem);
  CQProgressDialogLayout->addItem(mpSpacer);

  pItem->show();
  pApp->processEvents();

  mItemCount++;
  return true;
}

bool CQProgressDialog::removeProgressItem(CQProgressItem * pItem)
{
  CQProgressDialogLayout->remove(pItem);

  mItemCount--;
  if (mItemCount == 0) mpLine->hide();

  pApp->processEvents();
  return true;
}

void CQProgressDialog::init()
{
  mpLine->hide();
  mpBtnPause->hide();
  mpBtnContinue->hide();

  mItemCount = 0;

  mPause = false;
  mProceed = true;

  return;
}

void CQProgressDialog::btnContinuePressed()
{mPause = false;}

void CQProgressDialog::btnPausePressed()
{mPause = true;}

void CQProgressDialog::btnStopPressed()
{mProceed = false;}
