// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQCopasiApplication.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/02/22 16:28:45 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QFileOpenEvent>
#include <QString>

#include "CQCopasiApplication.h"
#include "copasiui3window.h"
#include "listviews.h"

CQCopasiApplication::CQCopasiApplication(int & argc, char ** argv):
    QApplication(argc, argv),
    mpMainWindow(NULL),
    mFile(),
    mStarting(true)
{}

CQCopasiApplication::~CQCopasiApplication()
{}

// virtual
bool CQCopasiApplication::event(QEvent * pEvent)
{
  switch (pEvent->type())
    {
      case QEvent::FileOpen:

        if (mStarting)
          {
            mFile = static_cast<QFileOpenEvent *>(pEvent)->file();
          }
        else
          {
            mpMainWindow->slotFileOpen(mFile);
          }

        pEvent->accept();
        return true;

        break;

      default:
        break;
    }

  return QApplication::event(pEvent);
}

void CQCopasiApplication::setMainWindow(CopasiUI3Window * pMainWindow)
{
  mpMainWindow = pMainWindow;

  processEvents();

  mpMainWindow->openInitialDocument(mFile);
  mStarting = false;
}
