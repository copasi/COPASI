// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

#include "copasi/UI/CopasiFileDialog.h"
#include "copasi/UI/CQMessageBox.h"
#include "CQSteadyStateResult.h"
#include "qtUtilities.h"

#include "copasi/copasi.h"

#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/steadystate/CSteadyStateProblem.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/*
 *  Constructs a CQSteadyStateResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQSteadyStateResult::CQSteadyStateResult(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSteadyStateResult::~CQSteadyStateResult()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQSteadyStateResult::init()
{
  mpProblem = NULL;
  mpTask = NULL;
  mUpToDate = false;
}

bool CQSteadyStateResult::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{
  if (objectType != ListViews::ObjectType::STATE)
    mUpToDate = false;

  return true;
}

bool CQSteadyStateResult::leaveProtected()
{
  return true;
}

bool CQSteadyStateResult::enterProtected()
{
  return true;
}

void CQSteadyStateResult::loadResult()
{
  assert(mpDataModel != NULL);
  mpTask =
    dynamic_cast<CSteadyStateTask *>(&mpDataModel->getTaskList()->operator[]("Steady-State"));

  if (!mpTask) return;

  mpProblem = dynamic_cast<const CSteadyStateProblem *>(mpTask->getProblem());

  if (!mpProblem) return;

  if (!mpTask) return;

  mpCentralWidget->loadAll(mpTask);
  mUpToDate = true;

  return;
}

void CQSteadyStateResult::slotSave(void)
{
  C_INT32 Answer = QMessageBox::No;
  QString fileName;

  while (Answer == QMessageBox::No)
    {
      fileName =
        CopasiFileDialog::getSaveFileName(this, "Save File Dialog",
                                          CopasiFileDialog::getDefaultFileName(".txt"), "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, fileName);

      if (Answer == QMessageBox::Cancel) return;
    }

  std::ofstream file(CLocaleString::fromUtf8(TO_UTF8(fileName)).c_str());

  if (file.fail()) return;

  if (mpTask != NULL)
    file << *mpTask;

  return;
}

void CQSteadyStateResult::slotUpdateModel()
{
  if (mUpToDate &&
      mpTask != NULL)
    {
      bool updateModel = mpTask->isUpdateModel();

      mpTask->setUpdateModel(true);
      mpTask->restore();
      mpTask->setUpdateModel(updateModel);

      protectedNotify(ListViews::ObjectType::STATE, ListViews::CHANGE, mpTask->getMathContainer()->getModel().getCN());
    }
}
