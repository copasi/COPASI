// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQEFMWidget.ui.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/23 13:58:04 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qmessagebox.h>
#include <qcheckbox.h>

#include "UI/CQTaskBtnWidget.h"
#include "UI/CQTaskHeaderWidget.h"
#include "UI/CProgressBar.h"
#include "UI/qtUtilities.h"

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
  if (dynamic_cast< CEFMTask * >(mpTask) == NULL)
    return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

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

  return true;
}

CCopasiMethod * CQEFMWidget::createMethod(const CCopasiMethod::SubType & type)
{
  return CEFMMethod::createMethod(type);
}
