// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.cpp,v $
//   $Revision: 1.30 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/09/02 14:30:56 $
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

#include <QCloseEvent>
#include <QMutex>
#include <QMutexLocker>

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

  if (pCopasiGuiMutex == NULL)
    pCopasiGuiMutex = new QMutex();

  // Whenever a progress bar is active we do not want any user
  // intervention.
  if ((mpMainWidget = qApp->mainWidget()) != NULL)
    {
      mpMainWidget->setEnabled(false);
      qApp->processEvents();
    }

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
  QMutexLocker Locker(pCopasiGuiMutex);

  unsigned C_INT32 hItem = CProcessReport::addItem(name, type, pValue, pEndValue);

  mSlotFinished = false;

  emit addProgressItem(hItem);

  if (!mSlotFinished)
    {
      mWaitSlot.wait(pCopasiGuiMutex);
    }

  return hItem;
}


void CProgressBar::slotAddItem(const unsigned int handle)
{
  if (handle == C_INVALID_INDEX) return;

  QMutexLocker Locker(pCopasiGuiMutex);

  if (handle >= mProgressItemList.size()) // we need to resize
    {
      unsigned C_INT32 i, imax = mProgressItemList.size();

      mProgressItemList.resize(2 * imax, true); // Note, imax is never zero

      i = imax;
      imax *= 2;

      while (i < imax) mProgressItemList[i++] = NULL;
    }

  if (mProcessReportItemList[handle]->hasEndValue())
    mProgressItemList[handle] = new CQProgressItemBar(static_cast<CQProgressDialog *>(this));
  else
    mProgressItemList[handle] = new CQProgressItemText(static_cast<CQProgressDialog *>(this));

  mProgressItemList[handle]->initFromProcessReportItem(mProcessReportItemList[handle]);
  insertProgressItem(mProgressItemList[handle]);

  mSlotFinished = true;
  mWaitSlot.wakeAll();
}

bool CProgressBar::resetItem(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  return (mProgressItemList[handle]->reset() && mProceed);
}

bool CProgressBar::progressItem(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  QDateTime currDateTime = QDateTime::currentDateTime();

  if (mNextEventProcessing >= currDateTime)
    return mProceed;

  mNextEventProcessing = currDateTime.addSecs(1);

  QMutexLocker Locker(pCopasiGuiMutex);

  if (mPause)
    {
      mWaitPause.wait(pCopasiGuiMutex);
    }

  mSlotFinished = false;
  emit progressProgressBar(handle);

  if (!mSlotFinished)
    {
      mWaitSlot.wait(pCopasiGuiMutex);
    }

  return mProceed;
}

void CProgressBar::slotProgress(const unsigned int C_UNUSED(handle))
{
  unsigned C_INT32 hItem, hmax = mProgressItemList.size();

  QMutexLocker Locker(pCopasiGuiMutex);

  for (hItem = 0; hItem < hmax; hItem++)
    {
      if (mProgressItemList[hItem])
        mProceed &= mProgressItemList[hItem]->process();
    }

  mSlotFinished = true;
  mWaitSlot.wakeAll();
}

bool CProgressBar::finish()
{
  // The method must only be called from the main thread!
  CQProgressItem ** ppIt = mProgressItemList.array();
  CQProgressItem ** ppEnd = ppIt + mProgressItemList.size();

  for (; ppIt != ppEnd; ++ppIt)
    {
      if (*ppIt != NULL)
        {
          removeProgressItem(*ppIt);
          (*ppIt)->deleteLater();
          (*ppIt) = NULL;
        }
    }

  CProcessReport::finish();
  done(1);

  return mProceed;
}

bool CProgressBar::finishItem(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  QMutexLocker Locker(pCopasiGuiMutex);

  mSlotFinished = false;

  emit finishProgressBar(handle);

  if (!mSlotFinished)
    {
      mWaitSlot.wait(pCopasiGuiMutex);
    }

  return (CProcessReport::finishItem(handle) && mProceed);
}

void CProgressBar::slotFinish(const unsigned int handle)
{
  if (isValidHandle(handle) &&
      mProgressItemList[handle] != NULL)
    {
      QMutexLocker Locker(pCopasiGuiMutex);

      removeProgressItem(mProgressItemList[handle]);
      mProgressItemList[handle]->deleteLater();
      mProgressItemList[handle] = NULL;
    }

  mSlotFinished = true;
  mWaitSlot.wakeAll();
}

bool CProgressBar::proceed()
{
  return mProceed;
}

bool CProgressBar::setName(const std::string & name)
{
  QMutexLocker Locker(pCopasiGuiMutex);

  mSlotFinished = false;

  emit setProgressBarName(FROM_UTF8(name));

  if (!mSlotFinished)
    {
      mWaitSlot.wait(pCopasiGuiMutex);
    }

  return true;
}
void CProgressBar::slotSetName(QString name)
{
  QMutexLocker Locker(pCopasiGuiMutex);

  setCaption(name);
  CProcessReport::setName(TO_UTF8(name));

  mSlotFinished = true;
  mWaitSlot.wakeAll();
}

void CProgressBar::closeEvent(QCloseEvent *e)
{
  CQMessageBox::information(this, "COPASI", "COPASI is currently executing tasks.\n"
                            "Please stop them first before closing COPASI.");

  e->ignore();
}

// virtual
void CProgressBar::btnStopPressed()
{
  CQProgressDialog::btnStopPressed();
  mWaitPause.wakeAll();
}

// virtual
void CProgressBar::btnContinuePressed()
{
  CQProgressDialog::btnContinuePressed();
  mWaitPause.wakeAll();
}
