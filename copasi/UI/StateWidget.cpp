/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/StateWidget.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/03/14 12:14:36 $
   End CVS Header */

#include <qpushbutton.h>
#include <qlayout.h>
#include "copasi.h"

#include "StateWidget.h"
#include "StateSubwidget.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "steadystate/CSteadyStateTask.h"
#include "model/CModel.h"

//#include "report/CKeyFactory.h"
#include "qtUtilities.h"

/*
 *  Constructs a StateWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
StateWidget::StateWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name)
    setName("StateWidget");
  setCaption(trUtf8("StateWidget"));

  setInitialState = new QPushButton(this, "setInitialState");
  setInitialState->setText(trUtf8("SetResultsAsNextInitialState"));
  connect(setInitialState, SIGNAL(clicked()), this, SLOT(runSetInitialState()));

  parentLayout = new QVBoxLayout(this, 0, 0, "parentLayout");
  stateLayout = new QHBoxLayout(0, 0 , 6, "StateLayout");
  mWidgetLayout = new QGridLayout(this, 1, 1, 0, -1, "Layout");

  mCentralWidget = new StateSubwidget(this, "StateSubwidget");
  mWidgetLayout->addWidget(mCentralWidget, 0, 0);

  //parentLayout->addLayout(stateLayout);
  parentLayout->addLayout(mWidgetLayout);
  stateLayout->addWidget(setInitialState);

  /*commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout5->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Revert"));
  Layout5->addWidget(cancelChanges);*/

  // signals and slots connections
  //connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
  //connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
StateWidget::~StateWidget()
{}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
bool StateWidget::loadFromBackend()
{
  mCentralWidget->showUnits();
  CSteadyStateTask * pSteadyStateTask
  = dynamic_cast<CSteadyStateTask *>((*CCopasiDataModel::Global->getTaskList())["Steady-State"]);

  if (!pSteadyStateTask) return false;
  if (!pSteadyStateTask->getState()) return false;
  return mCentralWidget->loadAll(pSteadyStateTask);
}

bool StateWidget::saveToBackend()
{
  return true;
}

/*void StateWidget::slotBtnCancelClicked()
{
  enter(objKey); // reload
}*/

/*void StateWidget::slotBtnOKClicked()
{
  saveToCompartment();
}*/

bool StateWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                         C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (this->isShown())
    return loadFromBackend();
  else
    return true;
}

bool StateWidget::leave()
{
  //return saveToCompartment();
  return true;
}

bool StateWidget::enter(const std::string & C_UNUSED(key))
{
  //objKey = key;
  return loadFromBackend();
  /*CCompartment* comp = dynamic_cast< CCompartment * >(GlobalKeys.get(key));

  if (comp) return loadFromCompartment(comp);
  else return false;*/
}

void StateWidget::runSetInitialState()
{
  CSteadyStateTask* mSteadyStateTask =
    //dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(objKey));
    //I need to remove this hardcoding -- sameer
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get("Task_2"));
  const CState *currentState = mSteadyStateTask->getState();
  if (currentState)
    CCopasiDataModel::Global->getModel()->setInitialState(currentState);
}
