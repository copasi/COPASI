// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "UI/CopasiFileDialog.h"
#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"
#include "CQSteadyStateResult.h"

#include "copasi.h"

#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "commandline/CLocaleString.h"

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

bool CQSteadyStateResult::update(ListViews::ObjectType objectType,
                                 ListViews::Action /* action */,
                                 const std::string & /* key */)
{
  if (objectType != ListViews::STATE)
    mUpToDate = false;

  return true;
}

bool CQSteadyStateResult::leave()
{
  return true;
}

bool CQSteadyStateResult::enterProtected()
{
  return true;
}

void CQSteadyStateResult::loadResult()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  mpTask =
    dynamic_cast<CSteadyStateTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Steady-State"]);

  if (!mpTask) return;

  mpProblem = dynamic_cast<const CSteadyStateProblem *>(mpTask->getProblem());

  if (!mpProblem) return;

  if (!mpTask) return;

  if (!mpTask->getState())
    {
      mpCentralWidget->clear();
      mUpToDate = false;
      return;
    }

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
                                          "untitled.txt", "TEXT Files (*.txt)", "Save to");

      if (fileName.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(fileName);

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
      mpTask != NULL &&
      mpProblem != NULL &&
      mpTask->getState() != NULL)
    {
      CModel *pModel = mpProblem->getModel();

      if (pModel != NULL)
        {
          pModel->compileIfNecessary(NULL);

          if (mpTask->isUpdateModel())
            {
              mpTask->restore();
            }
          else
            {
              mpTask->setUpdateModel(true);
              mpTask->restore();
              mpTask->setUpdateModel(false);
            }

          protectedNotify(ListViews::STATE, ListViews::CHANGE, pModel->getKey());
        }
    }
}
