// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQThread.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:46 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQThread
#define COPASI_CQThread

#include <QThread>
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
