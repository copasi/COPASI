// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CQThread.h"

#include "copasi/OpenMP/COpenMPConfig.h"

CQThread::CQThread():
  QThread(),
  mpClass(NULL),
  mpMethod(NULL)
{
  COpenMPConfig::Apply();
}

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
  COpenMPConfig::Apply();

  try
    {
      (*mpClass.*mpMethod)();
    }

  catch (...)
    {}
}
