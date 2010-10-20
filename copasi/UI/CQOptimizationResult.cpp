// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQOptimizationResult.cpp,v $
//   $Revision: 1.9.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/10/20 15:14:28 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"
#include "qregexp.h"

#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptItem.h"
#include "report/CCopasiRootContainer.h"
#include "UI/CopasiFileDialog.h"
#include "UI/CQMessageBox.h"
#include "UI/qtUtilities.h"
#include "CQOptimizationResult.h"
#include "commandline/CLocaleString.h"

/*
 *  Constructs a CQOptimizationResult which is a child of 'parent', with the
 *  name 'name'.'
 */
CQOptimizationResult::CQOptimizationResult(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
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

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQOptimizationResult::languageChange()
{
  retranslateUi(this);
}

void CQOptimizationResult::init()
{
  unsigned C_INT32 i, imax;

  // Set up the parameters table
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Parameter"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Value"));
  mpParameters->setNumCols(mpParameters->numCols() + 1);
  mpParameters->horizontalHeader()->setLabel(mpParameters->numCols() - 1, tr("Gradient"));
  mpParameters->setNumRows(0);
  mpParameters->setNumCols(3);
  mpParameters->setReadOnly(true);

  for (i = 0, imax = mpParameters->numCols(); i != imax; i++)
    mpParameters->adjustColumn(i);
}

bool CQOptimizationResult::update(ListViews::ObjectType /* objectType */,
                                  ListViews::Action /* action */,
                                  const std::string & /* key */)
{
  // :TODO:
  return true;
}

bool CQOptimizationResult::leave()
{
  // :TODO:
  return true;
}

bool CQOptimizationResult::enterProtected()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  mpTask =
    dynamic_cast<COptTask *>((*(*CCopasiRootContainer::getDatamodelList())[0]->getTaskList())["Optimization"]);

  if (!mpTask) return false;

  mpProblem = dynamic_cast<const COptProblem *>(mpTask->getProblem());

  if (!mpProblem) return false;

  // Objective Value
  mpEditObjectiveValue->setText(QString::number(mpProblem->getSolutionValue()));

  // Performance Statistics
  const unsigned C_INT32 & FunctionEvaluations = mpProblem->getFunctionEvaluations();
  mpEditEvaluations->setText(QString::number(FunctionEvaluations));
  const C_FLOAT64 & ExecutionTime = mpProblem->getExecutionTime();
  mpEditCPUTime->setText(QString::number(ExecutionTime));
  mpEditSpeed->setText(QString::number(FunctionEvaluations / ExecutionTime));

  unsigned C_INT32 i, imax;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpParameters->setNumRows(imax);
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  for (i = 0; i != imax; i++)
    {
      const CCopasiObject *pObject =
        pDataModel->getObject(Items[i]->getObjectCN());

      if (pObject)
        mpParameters->setText(i, 0, FROM_UTF8(pObject->getObjectDisplayName()));
      else
        mpParameters->setText(i, 0, "Not Found");

      const C_FLOAT64 & Solution = Solutions[i];
      mpParameters->setText(i, 1, QString::number(Solution));
      mpParameters->setText(i, 2, QString::number(Gradients[i]));
    }

  for (i = 0, imax = mpParameters->numCols(); i != imax; i++)
    mpParameters->adjustColumn(i);

  return true;
}

void CQOptimizationResult::slotSave(void)
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

  unsigned C_INT32 i, imax;

  // The global result and statistics
  file << "Objective Value" << std::endl;
  file << mpProblem->getSolutionValue() << std::endl;

  file << "Function Evaluations\tCPU Time [s]\tEvaluations/second [1/s]" << std::endl;
  const unsigned C_INT32 & FunctionEvaluations = mpProblem->getFunctionEvaluations();
  const C_FLOAT64 & ExecutionTime = mpProblem->getExecutionTime();
  file << FunctionEvaluations << "\t";
  file << ExecutionTime << "\t";
  file << FunctionEvaluations / ExecutionTime << std::endl;

  // Set up the parameters table
  file << std::endl << "Parameters:" << std::endl;
  file << "Parameter\tValue\tGradient" << std::endl;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  for (i = 0; i != imax; i++)
    {
      const CCopasiObject *pObject =
        pDataModel->getObject(Items[i]->getObjectCN());

      if (pObject)
        file << pObject->getObjectDisplayName() << "\t";
      else
        file << "Not Found\t";

      const C_FLOAT64 & Solution = Solutions[i];
      file << Solution << "\t";
      file << Gradients[i] << std::endl;
    }
}

void CQOptimizationResult::slotUpdateModel()
{
  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  std::vector<COptItem * >::const_iterator it = Items.begin();
  std::vector<COptItem * >::const_iterator end = Items.end();

  const C_FLOAT64 * pTmp;

  pTmp = mpProblem->getSolutionVariables().array();

  for (; it != end; ++it, pTmp++)
    {
      (*(*it)->COptItem::getUpdateMethod())(*pTmp);
      (*it)->setStartValue(*pTmp);
    }
}
