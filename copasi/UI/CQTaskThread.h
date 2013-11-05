// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQTaskThread_H
#define CQTaskThread_H

#include <QtCore/QThread>

class TaskWidget;
class CCopasiException;

class CQTaskThread : public QThread
{
  Q_OBJECT

public:
  CQTaskThread(TaskWidget *tw);
  ~CQTaskThread();

  virtual void run();

  const bool & success() const;

protected:
  TaskWidget *mpTaskWidget;
  bool mSuccess;
};

#endif //CQTaskThread_H
