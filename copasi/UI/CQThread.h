// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQThread
#define COPASI_CQThread

#include <QtCore/QThread>
#include "copasi/UI/DataModelGUI.h"

class CQThread : public QThread
{
  Q_OBJECT

private:
  CQThread();

public:
  CQThread(DataModelGUI * pClass, void (DataModelGUI::*pMethod)());

  ~CQThread();

  virtual void run();

private:
  DataModelGUI * mpClass;
  void (DataModelGUI::*mpMethod)();
};

#endif // COPASI_CQThread
