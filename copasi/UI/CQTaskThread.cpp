// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"
#include "copasi/utilities/CCopasiException.h"
#include "TaskWidget.h"

#include "CQTaskThread.h"
#include "copasi/utilities/CCopasiTask.h"

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
