/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQOptimizationWidget.ui.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:21 $
   End CVS Header */

#include <qlabel.h>
#include <qtoolbutton.h>
#include <qmessagebox.h>

#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CQFittingItemWidget.h"
#include "CProgressBar.h"
#include "CCopasiSelectionDialog.h"

#include "report/CKeyFactory.h"
#include "optimization/COptTask.h"
#include "optimization/COptItem.h"
#include "optimization/COptMethod.h"
#include "optimization/COptProblem.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiException.h"

bool CQOptimizationWidget::saveTask()
{
  COptTask * pTask =
    dynamic_cast< COptTask * >(mpTask);
  if (!pTask) return false;

  saveCommon();
  saveMethod();

  COptProblem * pProblem =
    dynamic_cast<COptProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  // Save parameters
  CCopasiParameterGroup * pGroup = pProblem->getGroup("OptimizationItemList");

  std::vector< COptItem * > * pVector =
    static_cast<std::vector< COptItem * > *>(pGroup->CCopasiParameter::getValue().pVOID);

  unsigned C_INT32 i, imax =
    std::min<unsigned C_INT32>(pVector->size(), mpParameters->numRows());

  for (i = 0; i < imax; i++)
    if (static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->save(*(*pVector)[i]))
      mChanged = true;

  // Remove exceeding parameters
  imax = pVector->size();
  if (i < imax)
    {
      mChanged = true;

      for (; i < imax; i++)
        pGroup->removeParameter(i);
    }

  // Add missing parameters
  imax = mpParameters->numRows();
  if (i < imax)
    {
      mChanged = true;

      COptItem * pFitItem;

      for (; i < imax; i++)
        {
          pFitItem = new COptItem();
          static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->save(*pFitItem);
          pGroup->addParameter(pFitItem);
        }
    }

  // Save constraints
  pGroup = pProblem->getGroup("OptimizationConstraintList");
  pVector =
    static_cast<std::vector< COptItem * > *>(pGroup->CCopasiParameter::getValue().pVOID);

  imax =
    std::min<unsigned C_INT32>(pVector->size(), mpConstraints->numRows());

  for (i = 0; i < imax; i++)
    if (static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->save(*(*pVector)[i]))
      mChanged = true;

  // Remove exceeding constraints
  imax = pVector->size();
  if (i < imax)
    {
      mChanged = true;

      for (; i < imax; i++)
        pGroup->removeParameter(i);
    }

  // Add missing constraints
  imax = mpConstraints->numRows();
  if (i < imax)
    {
      mChanged = true;

      COptItem * pFitItem;

      for (; i < imax; i++)
        {
          pFitItem = new COptItem();
          static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->save(*pFitItem);
          pGroup->addParameter(pFitItem);
        }
    }

  if (mChanged) CCopasiDataModel::Global->changed();

  mChanged = false;
  return true;
}

bool CQOptimizationWidget::loadTask()
{
  COptTask * pTask =
    dynamic_cast< COptTask * >(mpTask);
  if (!pTask) return false;

  loadCommon();
  loadMethod();

  COptProblem * pProblem =
    dynamic_cast<COptProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  CQFittingItemWidget * pFitItemWidget;

  std::vector< COptItem * >::const_iterator it =
    pProblem->getOptItemList().begin();
  std::vector< COptItem * >::const_iterator end =
    pProblem->getOptItemList().end();

  mpParameters->clearWidgetList();
  for (; it != end; ++it)
    {
      pFitItemWidget = new CQFittingItemWidget(mpParameters);
      pFitItemWidget->load(*static_cast<const COptItem *>(*it));
      mpParameters->addWidget(pFitItemWidget);
    }

  QString TabLabel = "Parameters (" + QString::number(mpParameters->numRows()) + ")";
  mpTabWidget->setTabLabel(mpParametersPage, TabLabel);

  it = pProblem->getConstraintList().begin();
  end = pProblem->getConstraintList().end();

  mpConstraints->clearWidgetList();
  for (; it != end; ++it)
    {
      pFitItemWidget = new CQFittingItemWidget(mpConstraints);
      pFitItemWidget->load(*static_cast<const COptItem *>(*it));
      mpConstraints->addWidget(pFitItemWidget);
    }

  TabLabel = "Constraints (" + QString::number(mpConstraints->numRows()) + ")";
  mpTabWidget->setTabLabel(mpConstraintsPage, TabLabel);

  mChanged = false;
  return true;
}

CCopasiMethod * CQOptimizationWidget::createMethod(const CCopasiMethod::SubType & type)
{return COptMethod::createMethod(type);}

bool CQOptimizationWidget::runTask()
{
  COptTask * pTask =
    dynamic_cast< COptTask * >(GlobalKeys.get(mObjectKey));
  if (!pTask) return false;

  if (!commonBeforeRunTask()) return false;

  pTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);

  try
    {
      if (!pTask->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      mProgressBar->finish();
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  pTask->restore();

  commonAfterRunTask();

  return true;
}

void CQOptimizationWidget::slotBtnAdd()
{
  CQFittingItemWidget * tmp = new CQFittingItemWidget(mpCurrentList);
  mpCurrentList->addWidget(tmp);

  int totalRows = mpCurrentList->numRows();
  mpCurrentList->ensureCellVisible(totalRows - 1, 0);
  tmp->mpBtnObject->setFocus();

  QString TabLabel = mpTabWidget->tabLabel(mpTabWidget->currentPage());
  TabLabel.replace(QString::number(totalRows - 1), QString::number(totalRows));
  mpTabWidget->setTabLabel(mpTabWidget->currentPage(), TabLabel);

  return;
}

void CQOptimizationWidget::slotItemDeleted()
{
  int totalRows = mpCurrentList->numRows();

  QString TabLabel = mpTabWidget->tabLabel(mpTabWidget->currentPage());
  TabLabel.replace(QString::number(totalRows + 1), QString::number(totalRows));
  mpTabWidget->setTabLabel(mpTabWidget->currentPage(), TabLabel);
}

void CQOptimizationWidget::slotPageChange(QWidget * currentPage)
{
  if (mpTabWidget->tabLabel(currentPage).contains("Parameters", true))
    {
      mpBtnAdd->setText("Add Parameter");
      mpCurrentList = mpParameters;
    }
  else
    {
      mpBtnAdd->setText("Add Constraint");
      mpCurrentList = mpConstraints;
    }
}

void CQOptimizationWidget::slotCopyItemWidget(int index)
{
  CQFittingItemWidget * tmp =
    static_cast<CQFittingItemWidget *>(mpCurrentList->getWidgetList()[index])->copy();

  mpCurrentList->insertWidget(tmp, index + 1);

  int totalRows = mpCurrentList->numRows();
  mpCurrentList->ensureCellVisible(index + 1, 0);
  tmp->mpBtnObject->setFocus();

  QString TabLabel = mpTabWidget->tabLabel(mpTabWidget->currentPage());
  TabLabel.replace(QString::number(totalRows - 1), QString::number(totalRows));
  mpTabWidget->setTabLabel(mpTabWidget->currentPage(), TabLabel);
}

void CQOptimizationWidget::slotTypeChanged(bool steadystate)
{
  mTypeChanged = !mTypeChanged;

  if (!mTypeChanged)
    {
      mpBtnSteadystate->setPaletteBackgroundColor(mSavedColor);
      mpBtnTimeCourse->setPaletteBackgroundColor(mSavedColor);
    }
  else if (steadystate & mTypeChanged)
    mpBtnSteadystate->setPaletteBackgroundColor(mChangedColor);
  else
    mpBtnTimeCourse->setPaletteBackgroundColor(mChangedColor);
}

void CQOptimizationWidget::slotExpression()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      // :TODO: Implement insertion of the object Selection[0].
    }
}

void CQOptimizationWidget::init()
{
  mpHeaderWidget->setTaskName("Parameter Estimation");

  CQOptimizationWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQOptimizationWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(COptTask::ValidMethods);
  addMethodParameterTable();

  mpParameterPageLayout = new QHBoxLayout(mpParametersPage, 0, 6, "mpParameterPageLayout");
  mpParameters = new CScanContainerWidget(mpParametersPage);
  mpParameters->enableCopy(true);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(itemDeleted()), this, SLOT(slotItemDeleted()));
  connect(mpParameters, SIGNAL(copyWidget(int)), this, SLOT(slotCopyItemWidget(int)));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CScanContainerWidget(mpConstraintsPage);
  mpConstraints->enableCopy(true);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(itemDeleted()), this, SLOT(slotItemDeleted()));
  connect(mpConstraints, SIGNAL(copyWidget(int)), this, SLOT(slotCopyItemWidget(int)));

  mpCurrentList = mpParameters;

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;
  mChangedColor.setHsv(240, s, v);

  mpBtnSteadystate->setChecked(true);
  mTypeChanged = false;
}
