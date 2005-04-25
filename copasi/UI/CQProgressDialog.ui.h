/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQProgressDialog.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

#include "qapplication.h"

extern QApplication *pApp;
bool CQProgressDialog::insertProgressItem(CQProgressItem * pItem)
{
  if (mItemCount == 0) mpLine->show();

  CQProgressDialogLayout->removeItem(mpSpacer);

  CQProgressDialogLayout->addWidget(pItem);
  pItem->show();

  CQProgressDialogLayout->addItem(mpSpacer);

  CQProgressDialogLayout->activate();
  update();
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
  mItemCount = 0;

  return;
}
