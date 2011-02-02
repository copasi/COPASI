// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskThread.h,v $
//   $Revision: 1.3.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/02/02 16:29:27 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQTaskThread_H
#define CQTaskThread_H

#include <QThread>

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

