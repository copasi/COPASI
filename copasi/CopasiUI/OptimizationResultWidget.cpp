/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationResultWidget.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/02 02:21:43 $
   End CVS Header */

#include <qpushbutton.h>
 #include <qlayout.h>
 #include <qtextedit.h>
 #include "copasi.h"

#include "OptimizationResultWidget.h"
 #include "StateSubwidget.h" 
//#include "OptimizationWidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
 #include "report/CKeyFactory.h"
 #include "steadystate/CSteadyStateTask.h"
 #include "model/CModel.h"
 #include "trajectory/CTrajectoryTask.h"
 #include "CTimeSeriesTable.h"

//#include "report/CKeyFactory.h"
#include "qtUtilities.h"

/*
 *  Constructs a OptimizationResultWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
OptimizationResultWidget::OptimizationResultWidget(QWidget* parent, const char* name, WFlags fl, const int comingFrom)
    : CopasiWidget(parent, name, fl), objKey("")
{
  if (!name)
    setName("OptimizationResultWidget");
  setCaption(trUtf8("OptimizationResultWidget"));

  parentLayout = new QVBoxLayout(this, 0, 0, "parentLayout");
  stateLayout = new QHBoxLayout(0, 0 , 6, "StateLayout");
  mWidgetLayout = new QGridLayout(NULL, 1, 1, 0, -1, "Layout");

  if (comingFrom == 0)
    {
      mCentralWidgetTime = NULL;
      mCentralWidgetSteady = new StateSubwidget(this, "StateSubwidget", 0);
      mWidgetLayout->addWidget(mCentralWidgetSteady, 0, 0);
      mCentralWidgetSteady->displayOptimizationTab(true);
    }
  else
    {
      mCentralWidgetSteady = NULL;
      mCentralWidgetTime = new TimeSeriesSubWidget(this, "TimeSeriesSubWidget", 0);
      mWidgetLayout->addWidget(mCentralWidgetTime, 0, 0);
      mCentralWidgetTime->displayOptimizationTab(true);
    }

  //parentLayout->addLayout(stateLayout);
  parentLayout->addLayout(mWidgetLayout);
}

/*
 *  Destroys the object and frees any allocated resources
 */
OptimizationResultWidget::~OptimizationResultWidget()
{}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
bool OptimizationResultWidget::loadFromBackend()
{
  std::ostringstream os;
  const COptProblem *opt;

  CCopasiVectorN< CCopasiTask > & TaskList = * CCopasiDataModel::Global->getTaskList();

  unsigned C_INT32 p, pmax = TaskList.size();
  for (p = 0; p < pmax; p++)
    {
      opt = dynamic_cast< COptProblem *>(TaskList[ p ]->getProblem());
      if (!opt) continue;
      {
        TaskList[ p ]->getProblem()->printResult(&os);
        break;
      }
    }

  if (mCentralWidgetSteady == NULL)
    {
      mCentralWidgetTime->table()->setTimeSeries(dynamic_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"])->getTimeSeries());
      mCentralWidgetTime->optimizationResultText->setText(FROM_UTF8(os.str()));
      return true;
    }
  else
    {
      CSteadyStateTask * pSteadyStateTask = dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);
      //mCentralWidgetSteady->loadAll(pSteadyStateTask);
      mCentralWidgetSteady->showUnits();

      if (!pSteadyStateTask) return false;
      if (!pSteadyStateTask->getState()) return mCentralWidgetSteady->clear();
      mCentralWidgetSteady->optimizationResultText->setText(FROM_UTF8(os.str()));
      return mCentralWidgetSteady->loadAll(pSteadyStateTask);
    }
}

bool OptimizationResultWidget::saveToBackend()
{
  return true;
}

bool OptimizationResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                      C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (this->isShown())
    return loadFromBackend();
  else
    return true;
}

bool OptimizationResultWidget::leave()
{
  //return saveToCompartment();
  return true;
}

bool OptimizationResultWidget::enter(const std::string & C_UNUSED(key))
{
  //objKey = key;
  return loadFromBackend();
  /*CCompartment* comp = dynamic_cast< CCompartment * >(GlobalKeys.get(key));

  if (comp) return loadFromCompartment(comp);
  else return false;*/
}

void OptimizationResultWidget::runSetInitialState()
{
  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get("Task_2"));
  const CState *currentState = mSteadyStateTask->getState();
  if (currentState)
    CCopasiDataModel::Global->getModel()->setInitialState(*currentState);
}

/*
//========================
bool TimeSeriesWidget::loadFromBackend()
{
  mCentralWidget->table()->setTimeSeries(dynamic_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"])->getTimeSeries());
  return true;
}
 
bool TimeSeriesWidget::saveToBackend()
{
  return true;
}
 
bool TimeSeriesWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (this->isShown())
    return loadFromBackend();
  else
    return true;
}
 
bool TimeSeriesWidget::leave()
{
  return true;
}
 
bool TimeSeriesWidget::enter(const std::string & C_UNUSED(key))
{
  return loadFromBackend();
}*/
