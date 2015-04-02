// Copyright (C) 2013 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtGui/QDockWidget>
#include <QtCore/QDateTime>
#include <QtCore/QSharedPointer>

#include <layoutUI/CQLayoutThread.h>
#include <layoutUI/CQSpringLayoutParameterWindow.h>

#include <layout/CCopasiSpringLayout.h>
#include <layout/CLayoutEngine.h>
#include <layout/CLayout.h>
#include <layout/CLayoutState.h>

#include <UI/copasiui3window.h>

CQLayoutThread::CQLayoutThread(QWidget* parent)
  : QThread(parent)
  , mpParameterWindow(NULL)
  , mpCurrentLayout(NULL)
  , mNumIterations(1000)
  , mUpdateWait(100)
  , mStopLayout(false)
  , mPause(false)
  , mpCurrent(NULL)
{
  qRegisterMetaType<QSharedPointer<CLayoutState> >();
  mpParameterWindow = new CQSpringLayoutParameterWindow("Layout Parameters", parent);
  connect(CopasiUI3Window::getMainWindow(), SIGNAL(signalQuit()), this, SLOT(terminateLayout()), Qt::DirectConnection);
}

void CQLayoutThread::terminateLayout()
{
  mSync.lock();
  mStopLayout = true;
  mPauseCond.wakeAll();
  mSync.unlock();

  wait();
}

void CQLayoutThread::resume()
{
  mSync.lock();
  mPause = false;
  mSync.unlock();
  mPauseCond.wakeAll();
}

bool CQLayoutThread::pause()
{
  if (mSync.tryLock(30))
    {
      mPause = true;
      mSync.unlock();
      return true;
    }

  return false;
}

QDockWidget* CQLayoutThread::getParameterWindow()
{
  return mpParameterWindow;
}

CQLayoutThread::~CQLayoutThread()
{
  pdelete(mpCurrent);
  pdelete(mpParameterWindow);
}

void CQLayoutThread::randomizeLayout(CLayout* layout)
{
  if (layout == NULL || mpParameterWindow == NULL)
    return;

  CCopasiSpringLayout l(layout, &mpParameterWindow->getLayoutParameters());
  l.randomize();

  emit layoutStateChanged(QSharedPointer<CLayoutState>(new CLayoutState(layout)));
  emit layoutUpdated();
}

void CQLayoutThread::createSpringLayout(CLayout* layout, int numIntervals, int updateWait)
{
  mpCurrentLayout = layout;
  mNumIterations = numIntervals;
  mUpdateWait = updateWait;
  start();
}

void CQLayoutThread::finalize()
{
  if (mpCurrent == NULL) return;

  mpCurrent->finalizeState();
}

void CQLayoutThread::stopLayout()
{
  mStopLayout = true;
  mPauseCond.wakeAll();
}

void CQLayoutThread::run()
{
  if (mpCurrentLayout == NULL)
    return;

  mStopLayout = false;

  if (mpCurrent != NULL)
    {
      delete mpCurrent;
      mpCurrent = NULL;
    }

  // create the spring layout
  mpCurrent = new CCopasiSpringLayout(mpCurrentLayout, &mpParameterWindow->getLayoutParameters());
  mpCurrent ->createVariables();

  CLayoutEngine le(mpCurrent, false);
  int i = 0;
  qint64 tick, last = 0;
  double pot, oldPot = -1.0;

  for (; (i < mNumIterations) && (mStopLayout) == false; ++i)
    {
      mSync.lock();

      if (mPause)
        mPauseCond.wait(&mSync);

      //test again, in case we should stop after the pause
      if (mStopLayout)
        {
          mSync.unlock();
          break;
        }

      pot = le.step();

      // no more working on the layout, release lock
      mSync.unlock();

      if (pot == 0.0 || fabs((pot - oldPot) / pot) < 1e-9)
        {
          break;
        }
      else
        {
          oldPot = pot;
        }

      tick = QDateTime::currentMSecsSinceEpoch();

      if (mUpdateWait != 0 && (tick - last > mUpdateWait))
        {
          last = tick;

          // calculate new curves and emit state
          finalize();

          emit layoutStateChanged(QSharedPointer<CLayoutState>(new CLayoutState(mpCurrentLayout)));
          emit layoutUpdated();
        }
    }

  // calculate new curves and emit state
  finalize();

  emit layoutStateChanged(QSharedPointer<CLayoutState>(new CLayoutState(mpCurrentLayout)));
  emit layoutUpdated();

  emit layoutFinished();
}
