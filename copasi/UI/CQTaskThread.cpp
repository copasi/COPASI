// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"
#include "utilities/CCopasiException.h"
#include "TaskWidget.h"

#include "CQTaskThread.h"
#include "utilities/CCopasiTask.h"

CQTaskThread::CQTaskThread(TaskWidget *tw):
  QThread(),
  mpTaskWidget(tw),
  mSuccess(false)
{}

CQTaskThread::~CQTaskThread()
{
}

void CQTaskThread::run()
{
  try
    {
      mSuccess = mpTaskWidget->getTask()->process(true);
    }
  catch (CCopasiException & /*Exception*/)
    {
      mSuccess = false;
    }
}

const bool & CQTaskThread::success() const
{
  return mSuccess;
}
