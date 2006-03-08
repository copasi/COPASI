/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQOptimizationWidget.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/08 19:01:10 $
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

  assert (false); // :TODO: Fixme

#ifdef XXXX
  unsigned C_INT32 i, imax =
    std::min<unsigned C_INT32>(pVector->size(), mpParameters->numRows());

  for (i = 0; i < imax; i++)
    if (static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->saveItem(*(*pVector)[i]))
      mChanged = true;

  // Remove exceeding parameters
  imax = pVector->size();
  if (i < imax)
    {
      mChanged = true;

      for (imax--; i <= imax && imax != C_INVALID_INDEX; imax--)
        pGroup->removeParameter(imax);
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
          static_cast<CQFittingItemWidget *>(mpParameters->getWidgetList()[i])->saveItem(*pFitItem);
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
    if (static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->saveItem(*(*pVector)[i]))
      mChanged = true;

  // Remove exceeding constraints starting from the last.
  imax = pVector->size();
  if (i < imax)
    {
      mChanged = true;

      for (imax--; i <= imax && imax != C_INVALID_INDEX; imax--)
        pGroup->removeParameter(imax);
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
          static_cast<CQFittingItemWidget *>(mpConstraints->getWidgetList()[i])->saveItem(*pFitItem);
          pGroup->addParameter(pFitItem);
        }
    }
#endif // XXXX

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

  if (*pProblem->getValue("Steady-State").pSTRING != "")
    mpBtnSteadystate->setChecked(true);
  else
    mpBtnSteadystate->setChecked(false);

  mpParameters->load(pProblem->getGroup("OptimizationItemList"), NULL);

  mpConstraints->load(pProblem->getGroup("OptimizationConstraintList"), NULL);

  mChanged = false;

  return true;
}

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

void CQOptimizationWidget::slotPageChange(QWidget * currentPage)
{
  if (mpTabWidget->tabLabel(currentPage).contains("Parameters", true))
    mpCurrentList = mpParameters;
  else
    mpCurrentList = mpConstraints;
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

CCopasiMethod * CQOptimizationWidget::createMethod(const CCopasiMethod::SubType & type)
{return COptMethod::createMethod(type);}

void CQOptimizationWidget::slotParameterNumberChanged(int number)
{
  QString TabLabel = "Parameters (" + QString::number(number) + ")";
  mpTabWidget->setTabLabel(mpParametersPage, TabLabel);
}

void CQOptimizationWidget::slotConstraintNumberChanged(int number)
{
  QString TabLabel = "Constraints (" + QString::number(number) + ")";
  mpTabWidget->setTabLabel(mpConstraintsPage, TabLabel);
}

void CQOptimizationWidget::init()
{
  mpParseList = new std::vector< CCopasiObject * >;

  mpHeaderWidget->setTaskName("Optimization");

  CQOptimizationWidgetLayout->insertWidget(0, mpHeaderWidget);
  CQOptimizationWidgetLayout->addWidget(mpBtnWidget);

  addMethodSelectionBox(COptTask::ValidMethods);
  addMethodParameterTable();

  mpParameterPageLayout = new QHBoxLayout(mpParametersPage, 0, 6, "mpParameterPageLayout");
  mpParameters = new CQFittingItemWidget(mpParametersPage);
  mpParameters->enableFitItem(true);
  mpParameterPageLayout->addWidget(mpParameters);
  connect(mpParameters, SIGNAL(numberChanged(int)), this, SLOT(slotParameterNumberChanged(int)));

  mpConstraintPageLayout = new QHBoxLayout(mpConstraintsPage, 0, 6, "mpConstraintsPageLayout");
  mpConstraints = new CQFittingItemWidget(mpConstraintsPage);
  mpConstraints->enableFitItem(true);
  mpConstraintPageLayout->addWidget(mpConstraints);
  connect(mpConstraints, SIGNAL(numberChanged(int)), this, SLOT(slotConstraintNumberChanged(int)));

  mpCurrentList = mpParameters;
}

void CQOptimizationWidget::destroy()
{
  pdelete(mpParseList);
}

void CQOptimizationWidget::slotObjectSelect()
{
}

bool CQOptimizationWidget::saveExpression()
{
  COptProblem * pProblem =
    dynamic_cast<COptProblem *>(mpTask->getProblem());
  if (!pProblem) return false;

  std::string DisplayName = "";
  std::string InfixCN = "";

  std::string InfixDispayName = (const char *)mpEditExpression->text().utf8();
  std::vector<CCopasiObject *>::iterator it = mpParseList->begin();

  for (unsigned int i = 0; i < InfixDispayName.length(); i++)
    {
      InfixCN += InfixDispayName[i];
      DisplayName = "";

      if (InfixDispayName[i] == '<')
        {
          i++;
          while (i < InfixDispayName.length() && InfixDispayName[i] != '>')
            {
              if (InfixDispayName[i] == '\\') // '\' is an escape character.
                DisplayName += InfixDispayName[i++];

              DisplayName += InfixDispayName[i++];
            }

          it = mpParseList->begin();
          while (it < mpParseList->end())
            {
              if ((*it)->getObjectDisplayName() == DisplayName)
                {
                  InfixCN += (*it)->getCN();
                  break;
                }

              it++;
            }

          if (it == mpParseList->end())
            {
              CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
              return false;
            }

          InfixCN += ">";
        }
    }

  if (!pProblem->setObjectiveFunction(InfixCN))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCOptimization + 5);
      return false;
    }

  // :TODO: need to handle errors.
  return true;
}
