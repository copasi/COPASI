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

#ifndef CQ_LAYOUT_THREAD_H
#define CQ_LAYOUT_THREAD_H

#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtCore/QSharedPointer>
#include <QtCore/QMetaType>

#include <copasi/copasi.h>
#include <copasi/layout/CLayoutState.h>
#include <copasi/layout/CCopasiSpringLayout.h>

class CQSpringLayoutParameterWindow;
class CLayout;
class QWidget;
class QDockWidget;
class CCopasiSpringLayout;
class CLayoutEngine;

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

  void resume();

  void finalize();

  bool pause();

signals:
  void layoutUpdated();
  void layoutFinished();
  void layoutStateChanged(QSharedPointer<CLayoutState> newState);

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
  CLayoutEngine* mpCurrentEngine;
};

Q_DECLARE_METATYPE(QSharedPointer<CLayoutState>)

#endif //CQ_LAYOUT_THREAD_H
