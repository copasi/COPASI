/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQEFMWidget.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/31 16:49:19 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qmessagebox.h>
#include <qcheckbox.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CProgressBar.h"
#include "qtUtilities.h"

#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "elementaryFluxModes/CEFMMethod.h"
#include "elementaryFluxModes/CEFMTask.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"

void CQEFMWidget::init()
{
  mpHeaderWidget->setTaskName("Elementary Flux Modes");
  mpHeaderWidget->mpUpdateModel->hide();

  CQEFMWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQEFMWidgetLayout->addWidget(mpBtnWidget);
}

void CQEFMWidget::destroy()
{}

void CQEFMWidget::loadFluxModes()
{
  mpListView->clear();

  QListViewItem* item;

  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);

  if (pTask)
    {
      unsigned C_INT32 const noOfModesRows = pTask->getFluxModeSize();
      mpEditFluxModes->setText(QString::number(noOfModesRows));

      unsigned C_INT32 j;
      for (j = 0; j < noOfModesRows; j++)
        {
          if (pTask->isFluxModeReversible(j) == true)
            {
              item = new QListViewItem(mpListView, "Reversible");
            }
          else
            {
              item = new QListViewItem(mpListView, "Irreversible");
            }
          item->setMultiLinesEnabled(true);

          item->setText(1, FROM_UTF8(pTask->getFluxModeDescription(j)));
          std::string reactionEq = "";
          unsigned int x, xmax = pTask->getFluxModeSize(j);
          //const CFluxMode & mode = pTask->getFluxMode(j);
          for (x = 0; x < xmax; x++)
            {
              reactionEq += pTask->getReactionEquation(j, x);
              reactionEq += "\n";
            }
          item->setText(2, FROM_UTF8(reactionEq).stripWhiteSpace() + "\n");
        }
    }
}

bool CQEFMWidget::runTask()
{
  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);
  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  bool success = true;

  // Initialize the task
  try
    {
      if (!pTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::critical(this, "Initialization Error",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();

          success = false;
          goto finish;
        }
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        QMessageBox::warning(this, "Initialization Warning",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ignore | QMessageBox::Default,
                             QMessageBox::Abort);
      CCopasiMessage::clearDeque();

      if (Result == QMessageBox::Abort)
        {
          success = false;
          goto finish;
        }
    }

  // Execute the task
  try
    {
      if (!pTask->process(true) &&
          CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }

      success = false;
      goto finish;
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        QMessageBox::warning(this, "Calculation Warning",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

finish:
  try {pTask->restore();}

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  catch (...) {}

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        QMessageBox::warning(this, "Calculation Warning",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
    }

  commonAfterRunTask();
  if (success) loadFluxModes();

  return success;
}

bool CQEFMWidget::saveTask()
{
  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);
  if (!pTask) return false;

  saveCommon();
  return true;
}

bool CQEFMWidget::loadTask()
{
  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);
  if (!pTask) return false;

  loadCommon();
  loadFluxModes();

  return true;
}

CCopasiMethod * CQEFMWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return CEFMMethod::createMethod(type);
}
