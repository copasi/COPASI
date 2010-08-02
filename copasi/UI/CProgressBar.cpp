// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.cpp,v $
//   $Revision: 1.29 $
//   $Name:  $
//   $Author: heilmand $
//   $Date: 2010/08/02 15:10:15 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <q3progressdialog.h>
#include <qapplication.h>
#include <qlayout.h>
#include <qwaitcondition.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QMutex>

#include "copasi.h"
#include "qtUtilities.h"
#include "utilities/CVector.h"
#include "CProgressBar.h"
#include "DataModelGUI.h"
#include "CQProgressItemText.h"
#include "CQProgressItemBar.h"
#include "CQMessageBox.h"

extern QApplication *pApp;

CProgressBar::CProgressBar(QWidget* parent, const char* name,
                           bool modal, Qt::WFlags fl):
    CQProgressDialog(parent, name, modal, fl | Qt::WStyle_Minimize),
    CProcessReport(),
    mProgressItemList(1),
    mNextEventProcessing(QDateTime::currentDateTime()),
    mpMainWidget(NULL)
{
  mProgressItemList[0] = NULL;

  // Whenever a progress bar is active we do not want any user
  // intervention.
  if ((mpMainWidget = qApp->mainWidget()) != NULL)
    {
      mpMainWidget->setEnabled(false);
      qApp->processEvents();
    }

  connect(this, SIGNAL(processEvents()), this, SLOT(slotProcessEvents()));


  connect(this, SIGNAL(addProgressItem(const unsigned int)),
          this, SLOT(slotAddItem(const unsigned int)));

  connect(this, SIGNAL(setProgressBarName(QString)),
          this, SLOT(slotSetName(QString)));

  connect(this, SIGNAL(progressProgressBar(const unsigned int)),
          this, SLOT(slotProgress(const unsigned int)));

  connect(this, SIGNAL(finishProgressBar(const unsigned int)),
          this, SLOT(slotFinish(const unsigned int)));
}

CProgressBar::~CProgressBar()
{
  finish();

  // We need to activate the user interface again.
  if (mpMainWidget != NULL)
    {
      mpMainWidget->setEnabled(true);
      qApp->processEvents();
    }

  unsigned C_INT32 i, imax = mProgressItemList.size();

  for (i = 0; i < imax; i++)
    pdelete(mProgressItemList[i]);
}


unsigned C_INT32 CProgressBar::addItem(const std::string & name,
                                       const CCopasiParameter::Type & type,
                                       const void * pValue,
                                       const void * pEndValue)

{
  unsigned C_INT32 hItem = CProcessReport::addItem(name, type, pValue, pEndValue);

  mMutex.lock();
  mSlotFinished = false;
  mMutex.unlock();

  emit addProgressItem(hItem);

  mMutex.lock();

  if (!mSlotFinished)
    mWaitSlot.wait(&mMutex);

  mMutex.unlock();

  return hItem;
}


void CProgressBar::slotAddItem(const unsigned int handle)
{
  if (handle == C_INVALID_INDEX) return;

  if (handle >= mProgressItemList.size()) // we need to resize
    {
      unsigned C_INT32 i, imax = mProgressItemList.size();

      CVector< CQProgressItem * > tmp = mProgressItemList;
      mProgressItemList.resize(2 * imax); // Note, imax is never zero

      for (i = 0; i < imax; i++)  // Copy existing items
        mProgressItemList[i] = tmp[i];

      imax *= 2;

      while (i < imax) mProgressItemList[i++] = NULL;
    }

  if (mProcessReportItemList[handle]->hasEndValue())
    mProgressItemList[handle] = new CQProgressItemBar(static_cast<CQProgressDialog *>(this));
  else
    mProgressItemList[handle] = new CQProgressItemText(static_cast<CQProgressDialog *>(this));

  mProgressItemList[handle]->initFromProcessReportItem(mProcessReportItemList[handle]);
  insertProgressItem(mProgressItemList[handle]);

  mMutex.lock();
  mSlotFinished = true;
  mWaitSlot.wakeAll();
  mMutex.unlock();
}

bool CProgressBar::reset(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  return (mProgressItemList[handle]->reset() && mProceed);
}

bool CProgressBar::progress(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  QDateTime currDateTime = QDateTime::currentDateTime();

  if (mNextEventProcessing >= currDateTime && currDateTime.addSecs(1) > mNextEventProcessing)
    return mProceed;

  mNextEventProcessing = QDateTime::currentDateTime().addSecs(1);

  mMutex.lock();
  mSlotFinished = false;

  if (mPause)
    mWaitPause.wait(&mMutex);

  mMutex.unlock();

  emit progressProgressBar(handle);

  mMutex.lock();

  if (!mSlotFinished)
    mWaitSlot.wait(&mMutex);

  bool ret = mProceedReturn;
  mMutex.unlock();

  return ret;
}

void CProgressBar::slotProgress(const unsigned int C_UNUSED(handle))
{
  bool Proceed = mProceed;

  unsigned C_INT32 hItem, hmax = mProgressItemList.size();

  for (hItem = 0; hItem < hmax; hItem++)
    {
      if (mProgressItemList[hItem])
        Proceed = mProgressItemList[hItem]->process() && mProceed;
    }

  emit processEvents();

  mMutex.lock();
  mSlotFinished = true;
  mProceedReturn = Proceed;
  mWaitSlot.wakeAll();
  mMutex.unlock();
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

  mMutex.lock();
  mSlotFinished = false;
  mMutex.unlock();

  emit finishProgressBar(handle);

  mMutex.lock();

  if (!mSlotFinished)
    mWaitSlot.wait(&mMutex);

  bool ret = mFinishReturn;
  mMutex.unlock();

  return ret;
}

void CProgressBar::slotFinish(const unsigned int handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return;

  removeProgressItem(mProgressItemList[handle]);
  pdelete(mProgressItemList[handle]);

  mMutex.lock();
  mSlotFinished = true;
  mFinishReturn = (CProcessReport::finish(handle) && mProceed);
  mWaitSlot.wakeAll();
  mMutex.unlock();

}

bool CProgressBar::proceed()
{
  emit processEvents();
  return mProceed;
}

bool CProgressBar::setName(const std::string & name)
{
  emit setProgressBarName(FROM_UTF8(name));
  return true;
}
void CProgressBar::slotSetName(QString name)
{
  setCaption(name);
  CProcessReport::setName(TO_UTF8(name));
}

void CProgressBar::closeEvent(QCloseEvent *e)
{
  CQMessageBox::information(this, "COPASI", "COPASI is currently executing tasks.\n"
                            "Please stop them first before closing COPASI.");

  e->ignore();
}

void CProgressBar::slotProcessEvents()
{
  static bool ProcessEvents = true;

  if (ProcessEvents)
    {
      ProcessEvents = false;
      qApp->processEvents();
      ProcessEvents = true;
    }
}

void CProgressBar::btnContinuePressed()
{
  CQProgressDialog::btnContinuePressed();
  mWaitPause.wakeAll();
}
