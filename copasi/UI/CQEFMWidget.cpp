// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMWidget.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/29 16:35:36 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQEFMWidget.h"

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CProgressBar.h"
#include "qtUtilities.h"
#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "CQEFMResultWidget.h"

#include "copasi.h"

#include "elementaryFluxModes/CEFMMethod.h"
#include "elementaryFluxModes/CEFMTask.h"
#include "utilities/utility.h"

/*
 *  Constructs a CQEFMWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQEFMWidget::CQEFMWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  setupUi(this);

  mpHeaderWidget->setTaskName("Elementary Flux Modes");
  mpHeaderWidget->mpUpdateModel->hide();

  addMethodSelectionBox(CEFMTask::ValidMethods, 0);

  verticalLayout->insertWidget(0, mpHeaderWidget);
  verticalLayout->addWidget(mpBtnWidget);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQEFMWidget::~CQEFMWidget()
{}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQEFMWidget::languageChange()
{
  retranslateUi(this);
}

bool CQEFMWidget::runTask()
{
  if (dynamic_cast< CEFMTask * >(mpTask) == NULL)
    return false;

  if (!commonBeforeRunTask()) return false;

  bool success = commonRunTask();

  commonAfterRunTask();

  if (success)
    {
      // We need to load the result here as this is the only place where
      // we know that it is correct.
      CQEFMResultWidget * pResult =
        dynamic_cast< CQEFMResultWidget * >(CopasiWidget::mpListView->findWidgetFromId(2211));

      if (pResult == NULL)
        return false;

      success &= pResult->loadResult(mpTask);

      if (success && isShown())
        CopasiWidget::mpListView->switchToOtherWidget(2211, ""); //change to the results window
    }

  return success;
}

bool CQEFMWidget::saveTask()
{
  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);

  if (!pTask) return false;

  saveCommon();
  saveMethod();

  return true;
}

bool CQEFMWidget::loadTask()
{
  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >(mpTask);

  if (!pTask) return false;

  loadCommon();
  loadMethod();

  return true;
}

CCopasiMethod * CQEFMWidget::createMethod(const CCopasiMethod::SubType & type)
{
  mpTask->setMethodType(type);
  return mpTask->getMethod();
}

void CQEFMWidget::slotSave()
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          "untitled.txt", "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(utf8ToLocale(TO_UTF8(fileName)).c_str());

  if (file.fail())
    return;

  if (mpTask != NULL)
    file << mpTask->getResult();

  return;
}
