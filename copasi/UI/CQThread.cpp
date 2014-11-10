// Copyright (C) 2011 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQThread.h"

CQThread::CQThread():
  QThread(),
  mpClass(NULL),
  mpMethod(NULL)
{}

CQThread::CQThread(DataModelGUI * pClass, void (DataModelGUI::*pMethod)()):
  QThread(),
  mpClass(pClass),
  mpMethod(pMethod)
{}

CQThread::~CQThread()
{}

//  virtual
void CQThread::run()
{
  try
    {
      (*mpClass.*mpMethod)();
    }

  catch (...)
    {}
}
