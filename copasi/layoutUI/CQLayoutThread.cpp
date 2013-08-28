// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <qdockwidget.h>
#include <qdatetime.h>
#include <QSharedPointer>

#include <layoutUI/CQLayoutThread.h>
#include <layoutUI/CQSpringLayoutParameterWindow.h>

#include <layout/CCopasiSpringLayout.h>
#include <layout/CLayoutEngine.h>
#include <layout/CLayout.h>
#include <layout/CLayoutState.h>

#include <UI/copasiui3window.h>

CQLayoutThread::CQLayoutThread(QWidget* parent)
  : mpParameterWindow(NULL)
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
  terminate();
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

  // we didn't get a lock in time, skip but notify to render later
  emit layoutUpdated();
  return false;
}

QDockWidget* CQLayoutThread::getParameterWindow()
{
  return mpParameterWindow;
}

CQLayoutThread::~CQLayoutThread()
{
}

void CQLayoutThread::randomizeLayout(CLayout* layout)
{
  if (layout == NULL || mpParameterWindow == NULL)
    return;

  CCopasiSpringLayout l(layout, &mpParameterWindow->getLayoutParameters());
  l.randomize();
  emit layoutCreated(QSharedPointer<CLayoutState>(new CLayoutState(layout)));

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

  bool doUpdate = true;
  mStopLayout = false;

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
          // redraw
          finalize();
          CLayoutState *state = new CLayoutState(mpCurrentLayout);
          emit layoutCreated(QSharedPointer<CLayoutState>(state));
          emit layoutUpdated();
        }
    }

  finalize();
  emit layoutCreated(QSharedPointer<CLayoutState>(new CLayoutState(mpCurrentLayout)));
  // redraw the layout
  emit layoutUpdated();
  emit layoutFinished();
}

CLayout* CQLayoutThread::getFinalLayout()
{
  return mpCurrentLayout;
}
