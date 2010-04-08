// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.cpp,v $
//   $Revision: 1.24 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2010/04/08 15:45:14 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <q3progressdialog.h>
#include <qapplication.h>
#include <qlayout.h>
#include <qwaitcondition.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <QMutex>

#include "copasi.h"
#include "qtUtilities.h"
#include "utilities/CVector.h"
#include "CProgressBar.h"
#include "DataModelGUI.h"
#include "CQProgressItemText.h"
#include "CQProgressItemBar.h"
#include "CQMessageBox.h"

extern QApplication *pApp;

CProgressBar::CProgressBar(QWidget* parent, const char* name,
                           bool modal, Qt::WFlags fl):
    CProcessReport(),
    CQProgressDialog(parent, name, modal, fl | Qt::WStyle_Minimize),
    mProgressItemList(1),
    mNextEventProcessing(QDateTime::currentDateTime()),
    mpMainWidget(NULL)
{
  mProgressItemList[0] = NULL;

  // Whenever a progress bar is active we do not want any user
  // intervention.
  if ((mpMainWidget = qApp->mainWidget()) != NULL)
    {
      mpMainWidget->setEnabled(false);
      qApp->processEvents();
    }

  connect(this, SIGNAL(processEvents()), this, SLOT(slotProcessEvents()), Qt::QueuedConnection);


  connect(this, SIGNAL(addProgressItem(QString, const int,
                                       const void *, const void *)), this, SLOT(slotAddItem(QString, const int,
                                           const void *, const void *)), Qt::QueuedConnection);

  connect(this, SIGNAL(setProgressBarName(QString)),
          this, SLOT(slotSetName(QString)), Qt::QueuedConnection);
}

CProgressBar::~CProgressBar()
{
  finish();

  // We need to activate the user interface again.
  if (mpMainWidget != NULL)
    {
      mpMainWidget->setEnabled(true);
      qApp->processEvents();
    }

  unsigned C_INT32 i, imax = mProgressItemList.size();

  for (i = 0; i < imax; i++)
    pdelete(mProgressItemList[i]);
}


unsigned C_INT32 CProgressBar::addItem(const std::string & name,
                                       const CCopasiParameter::Type & type,
                                       const void * pValue,
                                       const void * pEndValue)

{
  emit addProgressItem(FROM_UTF8(name), type, pValue, pEndValue);
  return 0;
}


void CProgressBar::slotAddItem(QString name, const int type,
                               const void * pValue, const void * pEndValue)
{
  unsigned C_INT32 hItem = CProcessReport::addItem(TO_UTF8(name),
                           static_cast<const CCopasiParameter::Type>(type),
                           pValue,
                           pEndValue);

  if (hItem == C_INVALID_INDEX) return;

  if (hItem >= mProgressItemList.size()) // we need to resize
    {
      unsigned C_INT32 i, imax = mProgressItemList.size();

      CVector< CQProgressItem * > tmp = mProgressItemList;
      mProgressItemList.resize(2 * imax); // Note, imax is never zero

      for (i = 0; i < imax; i++)  // Copy existing items
        mProgressItemList[i] = tmp[i];

      imax *= 2;

      while (i < imax) mProgressItemList[i++] = NULL;
    }

  if (mProcessReportItemList[hItem]->hasEndValue())
    mProgressItemList[hItem] = new CQProgressItemBar(static_cast<CQProgressDialog *>(this));
  else
    mProgressItemList[hItem] = new CQProgressItemText(static_cast<CQProgressDialog *>(this));

  mProgressItemList[hItem]->initFromProcessReportItem(mProcessReportItemList[hItem]);
  insertProgressItem(mProgressItemList[hItem]);

  return;
}

bool CProgressBar::reset(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  return (mProgressItemList[handle]->reset() && mProceed);
}

bool CProgressBar::progress(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  bool Proceed = mProgressItemList[handle]->process() && mProceed;

  if (mNextEventProcessing < QDateTime::currentDateTime())
    {
      mNextEventProcessing = QDateTime::currentDateTime().addSecs(1);
      //qApp->processEvents();
      emit processEvents();
    }

  while (mPause)
    {
      QMutex mutex;
      QWaitCondition Pause;
      Pause.wait(&mutex, 500);
      //qApp->processEvents();
      emit processEvents();
    }

  return Proceed;
}

bool CProgressBar::finish()
{
  unsigned C_INT32 i, imax = mProgressItemList.size();

  for (i = 0; i < imax; i++)
    if (mProgressItemList[i]) finish(i);

  CProcessReport::finish();
  done(1);

  return mProceed;
}

bool CProgressBar::finish(const unsigned C_INT32 & handle)
{
  if (!isValidHandle(handle) || mProgressItemList[handle] == NULL) return false;

  removeProgressItem(mProgressItemList[handle]);
  pdelete(mProgressItemList[handle]);

  return (CProcessReport::finish(handle) && mProceed);
}

bool CProgressBar::proceed()
{
  if (mNextEventProcessing < QDateTime::currentDateTime())
    {
      mNextEventProcessing = QDateTime::currentDateTime().addSecs(1);
      qApp->processEvents();
    }

  while (mPause)
    {
      QMutex mutex;
      QWaitCondition Pause;
      Pause.wait(&mutex, 500);
      qApp->processEvents();
    }

  return mProceed;
}

bool CProgressBar::setName(const std::string & name)
{
  emit setProgressBarName(FROM_UTF8(name));
  return true;
}
void CProgressBar::slotSetName(QString name)
{
  setCaption(name);
  CProcessReport::setName(TO_UTF8(name));
}

void CProgressBar::closeEvent(QCloseEvent *e)
{
  CQMessageBox::information(this, "COPASI", "COPASI is currently executing tasks.\n"
                            "Please stop them first before closing COPASI.");

  e->ignore();
}

void CProgressBar::slotProcessEvents()
{
  qApp->processEvents();
}
