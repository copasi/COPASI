// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.cpp,v $
//   $Revision: 1.33.2.10 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/04/08 12:07:09 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
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
#include <QThread>

#include "copasi.h"
#include "qtUtilities.h"
#include "utilities/CVector.h"
#include "CProgressBar.h"
#include "DataModelGUI.h"
#include "CQProgressItemText.h"
#include "CQProgressItemBar.h"
#include "CQMessageBox.h"
#include "copasiui3window.h"

extern QApplication *pApp;

// static
CProgressBar * CProgressBar::create(QWidget* parent, const char* name,
                                    bool modal, Qt::WFlags fl)
{
  QWidget * pMainWidget = qApp->mainWidget();

  if (pMainWidget != NULL &&
      static_cast< CopasiUI3Window * >(pMainWidget)->getMainThread() != QThread::currentThread())
    {
      return NULL;
    }
  else
    {
      return new CProgressBar(parent, name, modal, fl);
    }
}

CProgressBar::CProgressBar(QWidget* parent, const char* name,
                           bool modal, Qt::WFlags fl):
    CQProgressDialog(parent, name, modal, fl | Qt::WStyle_Minimize),
    CProcessReport(),
    mProgressItemList(1),
    mNextEventProcessing(QDateTime::currentDateTime()),
    mpMainWidget(NULL),
    mpMainThread(NULL)
{
  mProgressItemList[0] = NULL;

  // Whenever a progress bar is active we do not want any user
  // intervention.
  if ((mpMainWidget = qApp->mainWidget()) != NULL)
    {
      mpMainThread = static_cast< CopasiUI3Window * >(mpMainWidget)->getMainThread();
      mpMainWidget->setEnabled(false);
      qApp->processEvents();
    }

  connect(this, SIGNAL(signalAddItem(const int)),
          this, SLOT(slotAddItem(const int)));

  connect(this, SIGNAL(signalSetName(QString)),
          this, SLOT(slotSetName(QString)));

  connect(this, SIGNAL(signalProgressAll()),
          this, SLOT(slotProgressAll()));

  connect(this, SIGNAL(signalFinishItem(const int)),
          this, SLOT(slotFinishItem(const int)));
}

CProgressBar::~CProgressBar()
{
  finish();

  size_t i, imax = mProgressItemList.size();

  for (i = 0; i < imax; i++)
    pdelete(mProgressItemList[i]);
}


size_t CProgressBar::addItem(const std::string & name,
                             const CCopasiParameter::Type & type,
                             const void * pValue,
                             const void * pEndValue)

{
  size_t hItem = CProcessReport::addItem(name, type, pValue, pEndValue);

  if (mpMainThread != NULL &&
      QThread::currentThread() != mpMainThread)
    {
      QMutexLocker Locker(&mMutex);
      mSlotFinished = false;

      emit signalAddItem((int) hItem);

      if (!mSlotFinished)
        {
          mWaitSlot.wait(&mMutex);
        }
    }
  else
    {
      slotAddItem((int) hItem);
      qApp->processEvents();
    }

  return hItem;
}


void CProgressBar::slotAddItem(const int handle)
{
  size_t Handle = (size_t) handle;

  if (Handle == C_INVALID_INDEX) return;

  QMutexLocker Locker(&mMutex);

  if (Handle >= mProgressItemList.size()) // we need to resize
    {
      size_t i, imax = mProgressItemList.size();

      mProgressItemList.resize(2 * imax, true); // Note, imax is never zero

      i = imax;
      imax *= 2;

      while (i < imax) mProgressItemList[i++] = NULL;
    }

  if (mProcessReportItemList[Handle]->hasEndValue())
    mProgressItemList[Handle] = new CQProgressItemBar(static_cast<CQProgressDialog *>(this));
  else
    mProgressItemList[Handle] = new CQProgressItemText(static_cast<CQProgressDialog *>(this));

  mProgressItemList[Handle]->initFromProcessReportItem(mProcessReportItemList[Handle]);
  insertProgressItem(mProgressItemList[Handle]);

  mSlotFinished = true;
  mWaitSlot.wakeAll();
}

bool CProgressBar::resetItem(const size_t & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  return (mProgressItemList[handle]->reset() && mProceed);
}

bool CProgressBar::progressItem(const size_t & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  QDateTime currDateTime = QDateTime::currentDateTime();

  if (mNextEventProcessing >= currDateTime)
    return mProceed;

  mNextEventProcessing = currDateTime.addSecs(1);

  if (mPause)
    {
      mWaitPause.wait(&mMutex);
    }

  if (mpMainThread != NULL &&
      QThread::currentThread() != mpMainThread)
    {
      if (mSlotFinished)
        {
          mSlotFinished = false;
          emit signalProgressAll();
        }
    }
  else
    {
      slotProgressAll();
      qApp->processEvents();
    }

  return mProceed;
}

void CProgressBar::slotProgressAll()
{
  size_t hItem, hmax = mProgressItemList.size();

  QMutexLocker Locker(&mMutex);

  for (hItem = 0; hItem < hmax; hItem++)
    {
      if (mProgressItemList[hItem])
        mProceed &= mProgressItemList[hItem]->process();
    }

  mSlotFinished = true;
}

bool CProgressBar::finish()
{
  // Assure that all signals have been properly handled before we delete
  // the progress items
  if (mpMainThread == NULL ||
      QThread::currentThread() == mpMainThread)
    QCoreApplication::processEvents();

  // The method must only be called from the main thread!
  CQProgressItem ** ppIt = mProgressItemList.array();
  CQProgressItem ** ppEnd = ppIt + mProgressItemList.size();
  CProcessReportItem **ppItem = mProcessReportItemList.array();

  for (; ppIt != ppEnd; ++ppIt, ++ppItem)
    {
      if (*ppIt != NULL)
        {
          removeProgressItem(*ppIt);

          // We must make sure the CProcessReportItem is not deleted prior to the actual delete.
          // The destructor of CQProgressItem will take care of the deletion.
          *ppItem = NULL;

          (*ppIt)->deleteLater();
          (*ppIt) = NULL;
        }
    }

  // We need to activate the user interface again.
  if (mpMainWidget != NULL)
    {
      mpMainWidget->setEnabled(true);

      if (mpMainThread == NULL ||
          QThread::currentThread() == mpMainThread)
        qApp->processEvents();
    }

  CProcessReport::finish();
  done(1);

  return mProceed;
}

bool CProgressBar::finishItem(const size_t & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  if (mpMainThread != NULL &&
      QThread::currentThread() != mpMainThread)
    {
      QMutexLocker Locker(&mMutex);
      mSlotFinished = false;

      emit signalFinishItem((int) handle);

      if (!mSlotFinished)
        {
          mWaitSlot.wait(&mMutex);
        }
    }
  else
    {
      slotFinishItem((int) handle);
      qApp->processEvents();
    }

  return mProceed;
}

void CProgressBar::slotFinishItem(const int handle)
{
  size_t Handle = (size_t) handle;

  if (isValidHandle(Handle) &&
      mProgressItemList[Handle] != NULL)
    {
      QMutexLocker Locker(&mMutex);

      removeProgressItem(mProgressItemList[Handle]);

      // We must make sure the CProcessReportItem is not deleted prior to the actual delete.
      // The destructor of CQProgressItem will take care of the deletion.
      mProcessReportItemList[Handle] = NULL;

      mProgressItemList[Handle]->deleteLater();
      mProgressItemList[Handle] = NULL;
    }

  mSlotFinished = true;
  mWaitSlot.wakeAll();
}

bool CProgressBar::proceed()
{
  return mProceed;
}

// virtual
bool CProgressBar::setName(const std::string & name)
{
  if (mpMainThread != NULL &&
      QThread::currentThread() != mpMainThread)
    {
      QMutexLocker Locker(&mMutex);
      mSlotFinished = false;

      emit signalSetName(FROM_UTF8(name));

      if (!mSlotFinished)
        {
          mWaitSlot.wait(&mMutex);
        }
    }
  else
    {
      slotSetName(FROM_UTF8(name));
      qApp->processEvents();
    }

  return true;
}
void CProgressBar::slotSetName(QString name)
{
  QMutexLocker Locker(&mMutex);

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
