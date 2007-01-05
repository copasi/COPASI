/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/SSAWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/09/12 15:16:20 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qtoolbutton.h>
#include <qlayout.h>
#include <qmessagebox.h>

#include "SSAWidget.h"

#include "ssa/CSSATask.h"

#include "qtUtilities.h"

#include "report/CKeyFactory.h"
#include "DataModelGUI.h"
#include "listviews.h"
#include "copasiui3window.h"
#include "CProgressBar.h"

#include "utilities/CCopasiException.h"

SSAWidget::SSAWidget(QWidget * parent, const char* name, WFlags fl)
    : TaskWidget(parent, name, fl)
{
  mpMethodLayout = new QGridLayout(this, 0, 1, 11, 6, "mpMethodLayout");
}

SSAWidget::~SSAWidget()
{}

void
SSAWidget::on_RunButton_clicked()
{
  runTask();
}

bool
SSAWidget::runTask()
{
  bool success = true;
  CCopasiMessage::clearDeque();

  if (!commonBeforeRunTask()) return false;

  CSSATask* mSSATask =
    dynamic_cast<CSSATask *>(GlobalKeys.get(mObjectKey));
  assert(mSSATask);

  try
    {
      success = mSSATask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);
    }
  catch (CCopasiException)
    {
      success = false;
    }

  if (!success &&
      CCopasiMessage::getHighestSeverity() > CCopasiMessage::WARNING)
    {
      mProgressBar->finish();
      QMessageBox::warning(this, "Simulation Error",
                           CCopasiMessage::getAllMessageText().c_str(),
                           QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      commonAfterRunTask();

      return success;
    }

  if (CCopasiMessage::getHighestSeverity() >= CCopasiMessage::WARNING &&
      QMessageBox::warning (this, "Simulation Warning",
                            CCopasiMessage::getAllMessageText().c_str(),
                            "Continue", "Stop", NULL,
                            0, 1) == 1)
    {
      // mProgressBar->finish();
      commonAfterRunTask();

      return success;
    }

  CCopasiMessage::clearDeque();
  success = true;

  try
    {
      if (!mSSATask->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      success = false;
      mProgressBar->finish();
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(),
                               QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  //mSteadyStateTask->restore();

  commonAfterRunTask();

  //if (success && isShown()) pListView->switchToOtherWidget(211, ""); //change to the results window

  return success;
}

bool
SSAWidget::loadTask()
{return true;}

bool
SSAWidget::saveTask()
{return true;}

CCopasiMethod *
SSAWidget::createMethod(const CCopasiMethod::SubType& subtype)
{return NULL;}
