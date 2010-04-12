// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskThread.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/04/12 19:26:58 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"
#include "utilities/CCopasiException.h"
#include "TaskWidget.h"


#include "CQTaskThread.h"

CQTaskThread::CQTaskThread(TaskWidget *tw):
    QThread(),
    mpTaskWidget(tw)
{}

CQTaskThread::~CQTaskThread()
{
}

void CQTaskThread::run()
{
  try
    {
      if (!mpTaskWidget->getTask()->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }
  catch (CCopasiException Exception)
    {
      emit exceptionOccured(&Exception);
    }
}
