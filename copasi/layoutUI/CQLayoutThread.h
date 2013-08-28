// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQ_LAYOUT_THREAD_H
#define CQ_LAYOUT_THREAD_H

#include <qthread.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <qsharedpointer.h>
#include <qmetatype.h>

#include <layout/CCopasiSpringLayout.h>

class CQSpringLayoutParameterWindow;
class CLayout;
class QWidget;
class QDockWidget;
class CCopasiSpringLayout;

class CQLayoutThread : public QThread
{
  Q_OBJECT;
public:
  CQLayoutThread(QWidget* parent);
  virtual ~CQLayoutThread();

  QDockWidget* getParameterWindow();

  void randomizeLayout(CLayout* layout);

  /**
   * Run the layout algorithm on the given layout
   */
  void createSpringLayout(CLayout* layout, int numIntervals = 1000, int updateWait = 100);

  void stopLayout();

  CLayout* getFinalLayout();

  void resume();

  void finalize();

  bool pause();

signals:
  void layoutUpdated();
  void layoutFinished();
  void layoutCreated(QSharedPointer<CLayout> newLayout);

public slots:
  void terminateLayout();

protected:
  virtual void run();

  /**
   * The parameter window
   */
  CQSpringLayoutParameterWindow* mpParameterWindow;

  /**
   * The current layout
   */
  CLayout* mpCurrentLayout;

  /**
   * Number of Iterations the layout algorithm will run
   */
  int mNumIterations;

  /**
   * Number of msecs to wait between updates, use 0 to disable updates
   */
  int mUpdateWait;

  /**
   * boolean indicating whether the layout algorithm should stop
   */
  bool mStopLayout;

  // synchronization
  QMutex mSync;
  QWaitCondition mPauseCond;
  bool mPause;
  CCopasiSpringLayout *mpCurrent;
};

Q_DECLARE_METATYPE(QSharedPointer<CLayout>)

#endif //CQ_LAYOUT_THREAD_H
