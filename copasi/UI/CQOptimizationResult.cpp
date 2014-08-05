// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "copasi.h"

#include "optimization/COptTask.h"
#include "optimization/COptProblem.h"
#include "optimization/COptItem.h"
#include "report/CCopasiRootContainer.h"
#include "commandline/CLocaleString.h"
#include "model/CModel.h"

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

void CQOptimizationResult::init()
{}

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
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

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

  size_t i, imax;

  // Loop over the optimization items
  const std::vector< COptItem * > & Items = mpProblem->getOptItemList();
  const CVector< C_FLOAT64 > & Solutions = mpProblem->getSolutionVariables();
  const CVector< C_FLOAT64 > & Gradients = mpProblem->getVariableGradients();

  imax = Items.size();
  QTableWidgetItem * pItem;

  if (mpProblem->getFunctionEvaluations() == 0)
    imax = 0;

  mpParameters->setRowCount((int) imax);

  QColor BackgroundColor = mpParameters->palette().brush(QPalette::Active, QPalette::Base).color();

  int h, s, v;
  BackgroundColor.getHsv(&h, &s, &v);

  if (s < 20)
    {
      s = 20;
    }

  BackgroundColor.setHsv(0, s, v);

  for (i = 0; i != imax; i++)
    {
      //1st column: parameter name
      const CCopasiObject *pObject =
        pDataModel->getDataObject(Items[i]->getObjectCN());

      if (pObject)
        pItem = new QTableWidgetItem(FROM_UTF8(pObject->getObjectDisplayName()));
      else
        pItem = new QTableWidgetItem("Not Found");

      mpParameters->setItem((int) i, 0, pItem);

      const C_FLOAT64 & Solution = Solutions[i];

      //2nd column: lower bound
      pItem = new QTableWidgetItem(FROM_UTF8(Items[i]->getLowerBound()));
      mpParameters->setItem((int) i, 1, pItem);

      if (1.01 * *Items[i]->getLowerBoundValue() > Solution)
        {
          pItem->setBackgroundColor(BackgroundColor);
        }

      //3rd column: start value
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Items[i]->getLastStartValue());
      pItem->setForeground(QColor(120, 120, 140));
      mpParameters->setItem((int) i, 2, pItem);

      //4th column: solution value
      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Solution);
      mpParameters->setItem((int) i, 3, pItem);

      //5th column: upper bound
      pItem = new QTableWidgetItem(FROM_UTF8(Items[i]->getUpperBound()));
      mpParameters->setItem((int) i, 4, pItem);

      if (0.99 * *Items[i]->getUpperBoundValue() < Solution)
        {
          pItem->setBackgroundColor(BackgroundColor);
        }

      pItem = new QTableWidgetItem(QVariant::Double);
      pItem->setData(Qt::DisplayRole, Gradients[i]);
      mpParameters->setItem((int) i, 5,  pItem);
    }

  mpParameters->resizeColumnsToContents();
  mpParameters->resizeRowsToContents();

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

  size_t i, imax;

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
  file << "Parameter\tLower Bound\tStart Value\tValue\tUpper Bound\tGradient" << std::endl;

  // Loop over the fitted values objects
  imax = mpParameters->rowCount();

  for (i = 0; i != imax; i++)
    {
      file << TO_UTF8(mpParameters->item((int) i, 0)->text()) << "\t";
      file << TO_UTF8(mpParameters->item((int) i, 1)->text()) << "\t";
      file << TO_UTF8(mpParameters->item((int) i, 2)->text()) << "\t";
      file << TO_UTF8(mpParameters->item((int) i, 3)->text()) << "\t";
      file << TO_UTF8(mpParameters->item((int) i, 4)->text()) << "\t";
      file << TO_UTF8(mpParameters->item((int) i, 5)->text()) << std::endl;
    }

  file << std::endl;
}

void CQOptimizationResult::slotUpdateModel()
{
  const_cast< COptProblem * >(mpProblem)->restoreModel(true);
}
