// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQOptimizationResult.h"

#include "CopasiFileDialog.h"
#include "CQMessageBox.h"
#include "qtUtilities.h"

#include "copasi/copasi.h"

#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/optimization/COptItem.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/model/CModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"

#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/optimization/COptItem.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/optimization/COptLog.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/model/CModel.h"
#include "copasi/math/CMathContainer.h"

#include <copasi/UI/CQParameterResultItemModel.h>
#include <QSortFilterProxyModel>

#ifdef DELETE
#  undef DELETE
#endif

/*
 *  Constructs a CQOptimizationResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQOptimizationResult::CQOptimizationResult(QWidget* parent, const char* name):
  CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQOptimizationResult::~CQOptimizationResult()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQOptimizationResult::init()
{}

bool CQOptimizationResult::updateProtected(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn)
{

  if (objectType == ListViews::ObjectType::MODEL && action == ListViews::DELETE)
    mpParameters->setModel(NULL);

  return true;
}

bool CQOptimizationResult::leaveProtected()
{
  // :TODO:
  return true;
}

bool CQOptimizationResult::enterProtected()
{
  assert(mpDataModel != NULL);
  mpTask =
    dynamic_cast<COptTask *>(&mpDataModel->getTaskList()->operator[]("Optimization"));

  if (!mpTask) return false;

  mpProblem = dynamic_cast<const COptProblem *>(mpTask->getProblem());

  if (!mpProblem) return false;

  // Objective Value
  mpEditObjectiveValue->setText(convertToQString(mpProblem->getSolutionValue()));

  // Performance Statistics
  const unsigned C_INT32 & FunctionEvaluations = mpProblem->getFunctionEvaluations();
  mpEditEvaluations->setText(QString::number(FunctionEvaluations));
  const C_FLOAT64 & ExecutionTime = mpProblem->getExecutionTime();
  mpEditCPUTime->setText(convertToQString(ExecutionTime));
  mpEditSpeed->setText(convertToQString(FunctionEvaluations / ExecutionTime));
  const unsigned C_INT32 & FailedEvaluationsExc = mpProblem->getFailedEvaluationsExc();
  mpEditFailedEvaluationsExc->setText(QString::number(FailedEvaluationsExc));
  const unsigned C_INT32 & FailedEvaluationsNaN = mpProblem->getFailedEvaluationsNaN();
  mpEditFailedEvaluationsNaN->setText(QString::number(FailedEvaluationsNaN));

  mpEditConstraint->setText(QString::number(mpProblem->getConstraintEvaluations()));
  mpEditFailedConstraint->setText(QString::number(mpProblem->geFailedConstraintCounter()));

  QColor BackgroundColor = mpParameters->palette().brush(QPalette::Active, QPalette::Base).color();

  int h, s, v;
  BackgroundColor.getHsv(&h, &s, &v);

  if (s < 20)
    {
      s = 20;
    }

  BackgroundColor.setHsv(0, s, v);

  mpParameters->setModel(NULL);
  CQParameterResultItemModel* model = new CQParameterResultItemModel(mpProblem, BackgroundColor, this);
  QSortFilterProxyModel* sortModel = new QSortFilterProxyModel(this);
  sortModel->setSourceModel(model);
  mpParameters->setModel(sortModel);

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpParameters->resizeColumnsToContents();
      mpParameters->resizeRowsToContents();
    }

  // clear log
  mpLogTree->clear();

  return true;
}

void CQOptimizationResult::loadTab(int index)
{
  if (index != mpTabWidget->indexOf(mpLogPage))
    return;

  const COptMethod* pMethod = dynamic_cast<const COptMethod*>(mpTask->getMethod());

  if (pMethod == NULL)
    return;

  if (mpLogTree->topLevelItemCount() != 0)
    return;

  loadLog(pMethod);
}

void CQOptimizationResult::loadLog(const COptMethod * pMethod)
{
  mpLogTree->clear();

  if (pMethod == NULL)
    {
      mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpLogPage), false);
      return;
    }

  mpTabWidget->setTabEnabled(mpTabWidget->indexOf(mpLogPage), true);

  const COptLog &log = pMethod->getMethodLog();

  auto it = log.begin();

  for (; it != log.end(); ++it)
    {
      QTreeWidgetItem* item = new QTreeWidgetItem(mpLogTree->invisibleRootItem(), QStringList() << FROM_UTF8(it->getHeader()));

      if (!it->getSubtext().empty())
        {
          QTreeWidgetItem* subTextItem = new QTreeWidgetItem(item, QStringList() << FROM_UTF8(it->getSubtext()));
        }

      if (!it->getStatusDetails().empty())
        {
          QTreeWidgetItem* statusDetailItem = new QTreeWidgetItem(item, QStringList() << FROM_UTF8(it->getStatusDetails()));
        }
    }
}

void CQOptimizationResult::slotSave(void)
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

  // The global result and statistics
  file << "Objective Value" << std::endl;
  file << mpProblem->getSolutionValue() << std::endl;

  file << "Function Evaluations\tCPU Time [s]\tEvaluations/second [1/s]" << std::endl;
  const size_t & FunctionEvaluations = mpProblem->getFunctionEvaluations();
  const C_FLOAT64 & ExecutionTime = mpProblem->getExecutionTime();
  file << FunctionEvaluations << "\t";
  file << ExecutionTime << "\t";
  file << FunctionEvaluations / ExecutionTime << std::endl << std::endl;

  // Set up the parameters table
  file << "Parameters:" << std::endl;
  file << TO_UTF8(toTsvString(mpParameters->model(), true, false))
       << std::endl;

  // log
  const COptMethod * pMethod = dynamic_cast<const COptMethod *>(mpTask->getMethod());

  if (pMethod)
    {

      file << std::endl;

      // Set up log output
      file << "Method Log:" << std::endl;

      file << pMethod->getMethodLog().getPlainLog().c_str();

      file << std::endl;
    }

  file << std::endl;
}

void CQOptimizationResult::slotUpdateModel()
{
  const_cast< COptProblem * >(mpProblem)->restore(true);

  // We need to notify the GUI to update all values
  protectedNotify(ListViews::ObjectType::STATE, ListViews::CHANGE, mpTask->getMathContainer()->getModel().getCN());
}
