// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQThread.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/05 15:26:00 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
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
