/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLyapResultWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/12 13:49:16 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qpushbutton.h>
#include <qlayout.h>
#include <qtextedit.h>
#include <qlabel.h>

#include "copasi.h"

#include "CQLyapResultWidget.h"
//#include "StateSubwidget.h"
//#include "CTimeSeriesTable.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "model/CModel.h"
#include "lyap/CLyapTask.h"

//#include "report/CKeyFactory.h"

/*
 *  Constructs a CQLyapResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQLyapResultWidget::CQLyapResultWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
    //objKey("")
{
  if (!name)
    setName("CQLyapResultWidget");
  setCaption("CQLyapResultWidget");

  //parentLayout = new QVBoxLayout(this, 0, 0, "parentLayout");

  //stateLayout = new QHBoxLayout(0, 0 , 6, "StateLayout");
  //mWidgetLayout = new QGridLayout(NULL, 1, 1, 0, -1, "Layout");

  //   if (comingFrom == 0)
  //     {
  //       mCentralWidgetTime = NULL;
  //       mCentralWidgetSteady = new StateSubwidget(this, "StateSubwidget", 0);
  //       mWidgetLayout->addWidget(mCentralWidgetSteady, 0, 0);
  //       mCentralWidgetSteady->displayOptimizationTab(true);
  //}
  //   else
  //     {
  //       mCentralWidgetSteady = NULL;
  //       mCentralWidgetTime = new TimeSeriesSubWidget(this, "TimeSeriesSubWidget", 0);
  //       mWidgetLayout->addWidget(mCentralWidgetTime, 0, 0);
  //       mCentralWidgetTime->displayOptimizationTab(true);
  //}

  //parentLayout->addLayout(stateLayout);
  //parentLayout->addLayout(mWidgetLayout);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQLyapResultWidget::~CQLyapResultWidget()
{}

/* This function loads the optimization result widget when its name is
  clicked in the tree   */
bool CQLyapResultWidget::loadFromBackend()
{
  bool success = true;
  std::ostringstream os;

  /*
  CCopasiTask * pTask = (*CCopasiDataModel::Global->getTaskList())["Optimization"];
  if (!pTask) return false;

  COptProblem * pProblem = dynamic_cast< COptProblem * >(pTask->getProblem());
  if (!pProblem) return false;

  // We need to use the solution and run Steady-State or Time-Course.
  const CVector< C_FLOAT64 > & Solution = pProblem->getSolutionVariables();
  const std::vector< UpdateMethod * > & SetCalculateVariable =
    pProblem->getCalculateVariableUpdateMethods();

  const C_FLOAT64 * pIt = Solution.array();
  const C_FLOAT64 * pEnd = pIt + Solution.size();
  std::vector< UpdateMethod * >::const_iterator itUpdate = SetCalculateVariable.begin();

  success = (pIt != pEnd);

  for (; pIt != pEnd; ++pIt, ++itUpdate) (**itUpdate)(*pIt);

  if (success)
    {
      pProblem->calculate();
      success = (pProblem->getCalculateValue() != DBL_MAX);
    }

  if (success)
    pProblem->printResult(&os);
  else
    os << "<h2>No result available, please execute the optimization task.</h2>";

  if (mCentralWidgetSteady == NULL)
    {
      mCentralWidgetTime->table()->setTimeSeries(dynamic_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"])->getTimeSeries());
      mCentralWidgetTime->optimizationResultText->setText(FROM_UTF8(os.str()));
    }
  else
    {
      CSteadyStateTask * pSteadyStateTask =
        dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);

      mCentralWidgetSteady->showUnits();
      mCentralWidgetSteady->optimizationResultText->setText(FROM_UTF8(os.str()));

      if (!pSteadyStateTask || !success || !pSteadyStateTask->getState())
        {
          mCentralWidgetSteady->clear();
          success = false;
        }
      else
        success = mCentralWidgetSteady->loadAll(pSteadyStateTask);
    }

  try
    {
      if (Solution.size()) pProblem->restore(pTask->isUpdateModel());
    }

  catch (...) {}
  */
  return success;
}

bool CQLyapResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (this->isShown())
    return loadFromBackend();
  else
    return true;
}

bool CQLyapResultWidget::leave()
{
  //return saveToCompartment();
  return true;
}

bool CQLyapResultWidget::enter(const std::string & C_UNUSED(key))
{
  //objKey = key;
  return loadFromBackend();
  /*CCompartment* comp = dynamic_cast< CCompartment * >(GlobalKeys.get(key));

  if (comp) return loadFromCompartment(comp);
  else return false;*/
}
