// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskThread.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/04/09 16:48:20 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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

  void run();

protected:
  TaskWidget *mpTaskWidget;

signals:
  void exceptionOccured(CCopasiException* pException);
};

#endif //CQTaskThread_H

