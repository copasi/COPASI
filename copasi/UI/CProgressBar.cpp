// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QApplication>
#include <QLayout>
#include <QtCore/QWaitCondition>

#include <QCloseEvent>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "copasi/copasi.h"
#include "qtUtilities.h"
#include "CProgressBar.h"

#include "copasi/core/CVector.h"
#include "DataModelGUI.h"
#include "CQProgressItemText.h"
#include "CQProgressItemBar.h"
#include "CQMessageBox.h"
#include "copasiui3window.h"

#undef min
#undef max

// static
CProgressBar * CProgressBar::create(QWidget* parent, const char* name, Qt::WindowModality windowModality)
{
  QWidget * pParent = parent;

  if (pParent == NULL)
    {
      pParent = CopasiUI3Window::getMainWindow();
    }

  if (CopasiUI3Window::isMainThread())
    {
      return new CProgressBar(pParent, name, windowModality);
    }
  else
    {
      return NULL;
    }
}

CProgressBar::CProgressBar(QWidget* parent, const char* name, Qt::WindowModality windowModality):
  CQProgressDialog(parent, name, windowModality, Qt::WindowMinimizeButtonHint),
  CProcessReport(),
  mSlotFinished(true),
  mMutex(),
  mWaitSlot(),
  mWaitPause(),
  mLastHItem(C_INVALID_INDEX),
  mProgressItemList(1),
  mNextEventProcessing(QDateTime::currentDateTime()),
  mpMainWidget(NULL)
{
  CopasiUI3Window::getMainWindow()->disableSliders(true);

  mProgressItemList[0] = NULL;

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

  if (!CopasiUI3Window::isMainThread())
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
      QCoreApplication::processEvents();
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

  return (mProgressItemList[handle]->reset() && proceed());
}

bool CProgressBar::progressItem(const size_t & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL)
    return false;

  return proceed();
}

void CProgressBar::slotProgressAll()
{
  size_t hItem, hmax = mProgressItemList.size();

  QMutexLocker Locker(&mMutex);

  for (hItem = 0; hItem < hmax; hItem++)
    {
      if (mProgressItemList[hItem])
        mProgressItemList[hItem]->process();
    }

  mSlotFinished = true;
}

// virtual
bool CProgressBar::finish()
{
  // Assure that all signals have been properly handled before we delete
  // the progress items
  if (CopasiUI3Window::isMainThread())
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

  CopasiUI3Window::getMainWindow()->disableSliders(false);
  done(1);

  return CProcessReport::finish();
}

bool CProgressBar::finishItem(const size_t & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  if (!CopasiUI3Window::isMainThread())
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
      QCoreApplication::processEvents();
    }

  return proceed();
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

// virtual
bool CProgressBar::proceed()
{
  if (mProccessingInstruction == ProccessingInstruction::Pause)
    {
      QMutexLocker Locker(&mMutex);
      mWaitPause.wait(&mMutex);
    }

  QDateTime currDateTime = QDateTime::currentDateTime();

  if (mNextEventProcessing < currDateTime)
    {
      mNextEventProcessing = currDateTime.addSecs(1);

      if (!CopasiUI3Window::isMainThread())
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
          QCoreApplication::processEvents();
        }
    }

  return CProcessReport::proceed();
}

// virtual
bool CProgressBar::setName(const std::string & name)
{
  if (!CopasiUI3Window::isMainThread())
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
      QCoreApplication::processEvents();
    }

  return true;
}
void CProgressBar::slotSetName(QString name)
{
  QMutexLocker Locker(&mMutex);

  setWindowTitle(name);
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
  mProccessingInstruction = ProccessingInstruction::Stop;
  CQProgressDialog::btnStopPressed();
  mWaitPause.wakeAll();
}

// virtual
void CProgressBar::btnKillPressed()
{
  mProccessingInstruction = ProccessingInstruction::Kill;
  CQProgressDialog::btnKillPressed();
  mWaitPause.wakeAll();
}

// virtual
void CProgressBar::btnPausePressed()
{
  mProccessingInstruction = ProccessingInstruction::Pause;
  CQProgressDialog::btnPausePressed();
}

// virtual
void CProgressBar::btnContinuePressed()
{
  mProccessingInstruction = ProccessingInstruction::Continue;
  CQProgressDialog::btnContinuePressed();
  mWaitPause.wakeAll();
}
