// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QDockWidget>
#include <QtCore/QDateTime>
#include <QtCore/QSharedPointer>

#include <copasi/layoutUI/CQLayoutThread.h>
#include <copasi/layoutUI/CQSpringLayoutParameterWindow.h>

#include <copasi/layout/CCopasiSpringLayout.h>
#include <copasi/layout/CLayoutEngine.h>
#include <copasi/layout/CLayout.h>
#include <copasi/layout/CLayoutState.h>

#include <copasi/UI/copasiui3window.h>

CQLayoutThread::CQLayoutThread(QWidget* parent)
  : QThread(parent)
  , mpParameterWindow(NULL)
  , mpCurrentLayout(NULL)
  , mNumIterations(1000)
  , mUpdateWait(100)
  , mStopLayout(false)
  , mPause(false)
  , mpCurrent(NULL)
  , mpCurrentEngine(NULL)
{
  qRegisterMetaType<QSharedPointer<CLayoutState> >();
  mpParameterWindow = new CQSpringLayoutParameterWindow("Layout Parameters", parent);
  connect(CopasiUI3Window::getMainWindow(), SIGNAL(signalQuit()), this, SLOT(terminateLayout()), Qt::DirectConnection);
}

void CQLayoutThread::terminateLayout()
{
  mSync.lock();
  mStopLayout = true;

  if (mpCurrentEngine != NULL)
    mpCurrentEngine->requestStop();

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

  if (mpCurrentEngine != NULL)
    mpCurrentEngine->requestStop();

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
  mpCurrentEngine = &le;
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

  mpCurrentEngine = NULL;

  // calculate new curves and emit state
  finalize();

  emit layoutStateChanged(QSharedPointer<CLayoutState>(new CLayoutState(mpCurrentLayout)));
  emit layoutUpdated();

  emit layoutFinished();
}
