/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/28 19:50:14 $
   End CVS Header */

#include <qprogressdialog.h>
#include <qapplication.h>
#include <qlayout.h>
#include <qapplication.h>

#include "copasi.h"
#include "qtUtilities.h"
#include "utilities/CVector.h"
#include "CProgressBar.h"
#include "DataModelGUI.h"
#include "CQProgressItemText.h"
#include "CQProgressItemBar.h"

extern QApplication *pApp;

CProgressBar::CProgressBar(QWidget* parent, const char* name,
                           bool modal, WFlags fl):
    CProcessReport(),
    CQProgressDialog(parent, name, modal, fl),
    mProgressItemList(1),
    mNextEventProcessing(QTime::currentTime())
{mProgressItemList[0] = NULL;}

CProgressBar::~CProgressBar()
{
  unsigned C_INT32 i, imax = mProgressItemList.size();

  for (i = 0; i < imax; i++)
    pdelete(mProgressItemList[i]);
}

unsigned C_INT32 CProgressBar::addItem(const std::string & name,
                                       const CCopasiParameter::Type & type,
                                       const void * pValue,
                                       const void * pEndValue)
{
  unsigned C_INT32 hItem = CProcessReport::addItem(name,
                           type,
                           pValue,
                           pEndValue);
  if (hItem == C_INVALID_INDEX) return hItem;

  if (hItem >= mProgressItemList.size()) // we need to resize
    {
      unsigned C_INT32 i, imax = mProgressItemList.size();

      CVector< CQProgressItem * > tmp = mProgressItemList;
      mProgressItemList.resize(2 * imax); // Note, imax is never zero

      for (i = 0; i < imax; i++)  // Copy existing items
        mProgressItemList[i] = tmp[i];

      imax *= 2;
      while (i < imax) mProgressItemList[i++] = NULL;
    }

  if (mProcessReportItemList[hItem]->hasEndValue())
    mProgressItemList[hItem] = new CQProgressItemBar(static_cast<CQProgressDialog *>(this));
  else
    mProgressItemList[hItem] = new CQProgressItemText(static_cast<CQProgressDialog *>(this));

  mProgressItemList[hItem]->initFromProcessReportItem(mProcessReportItemList[hItem]);
  insertProgressItem(mProgressItemList[hItem]);

  return hItem;
}

bool CProgressBar::reset(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  return (mProgressItemList[handle]->reset() && mProceed);
}

bool CProgressBar::progress(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  if (mNextEventProcessing < QTime::currentTime())
    {
      mNextEventProcessing = QTime::currentTime().addMSecs(1000);
      pApp->processEvents();
    }

  return (mProgressItemList[handle]->process() && mProceed);
}

bool CProgressBar::finish()
{
  unsigned C_INT32 i, imax = mProgressItemList.size();

  for (i = 0; i < imax; i++)
    if (mProgressItemList[i]) finish(i);

  CProcessReport::finish();
  done(1);

  return mProceed;
}

bool CProgressBar::finish(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  removeProgressItem(mProgressItemList[handle]);
  pdelete(mProgressItemList[handle]);

  return (CProcessReport::finish(handle) && mProceed);
}

bool CProgressBar::proceed()
{return mProceed;}

bool CProgressBar::setName(const std::string & name)
{
  setCaption(FROM_UTF8(name));
  return (CProcessReport::setName(name) && mProceed);
}
