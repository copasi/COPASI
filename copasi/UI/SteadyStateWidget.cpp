/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SteadyStateWidget.cpp,v $
   $Revision: 1.102 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/11 08:55:37 $
   End CVS Header */

#include <qfiledialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h> 
//#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h> 
//#include <qapplication.h>

#include "DataModelGUI.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "qtUtilities.h"

#include "SteadyStateWidget.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "model/CModel.h"
#include "listviews.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h" 
//#include "report/CReportDefinitionVector.h"
//#include "report/CReport.h"
//#include "report/CReportDefinition.h"
//#include "CReportDefinitionSelect.h"
#include "CProgressBar.h" 
//#include "copasiui3window.h"

/**
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, WFlags fl)
    : TaskWidget(parent, name, fl)
{
  if (!name)
    setName("SteadyStateWidget");
  setCaption(trUtf8("SteadyStateWidget"));

  //if a mpMethodLayout is created here, it will be used by addMethodXXX() below.
  mpMethodLayout = new QGridLayout(this, 1, 1, 11, 6, "mpMethodLayout");

  //set the task name and add the name widget to the layout
  mpHeaderWidget->setTaskName("Steady State");
  addHeaderToGrid();

  QSpacerItem* spacer2 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  mpMethodLayout->addItem(spacer2, 1, 1);

  //*************************

  /*setInitialState = new QCheckBox(this, "setInitialState");
  setInitialState->setText(trUtf8("Use result as new initial state"));
  setInitialState->setChecked(parent == NULL);
  setInitialState->setEnabled(parent != NULL);
  mpMethodLayout->addWidget(setInitialState, 2, 1);*/

  taskJacobian = new QCheckBox(this, "taskJacobian");
  taskJacobian->setText(trUtf8("calculate Jacobian"));
  mpMethodLayout->addWidget(taskJacobian, 3, 1);

  taskStability = new QCheckBox(this, "taskStability");
  taskStability->setText(trUtf8("perform Stability Analysis"));
  mpMethodLayout->addWidget(taskStability, 3, 2);
  taskStability->setEnabled(false);

  addHLineToGrid(mpMethodLayout, 4, 2);

  /*line_ss = new QFrame(this, "line_ss");
  line_ss->setFrameShape(QFrame::HLine);
  line_ss->setFrameShadow(QFrame::Sunken);
  TaskWidgetLayout->addMultiCellWidget(line_ss, 4, 4, 0, 2);*/

  //************* parameter table ****************
  addMethodParameterTable(10, 5);
  //addMethodParameterTableToLayout(5, 2);

  /*QSpacerItem* spacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TaskWidgetLayout->addMultiCell(spacer_3, 7, 7, 0, 2);*/

  //*******************************************

  mpMethodLayout->addMultiCellWidget(mpBtnWidget, 11, 11, 0, 2);

  // signals and slots connections
  //connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(taskJacobian, SIGNAL(toggled(bool)), this, SLOT(taskJacobianToggled()));

  // tab order
  //setTabOrder(taskName, bExecutable);
  //setTabOrder(bExecutable, setInitialState);
  //setTabOrder(setInitialState, taskJacobian);
  setTabOrder(taskJacobian, taskStability);
  //setTabOrder(taskStability, parameterTable);
  //setTabOrder(parameterTable, bRunButton);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{}

/*void SteadyStateWidget::parameterValueChanged()
{
  qWarning("SteadyStateWidget::parameterValueChanged(): Not implemented yet!");
}*/

CCopasiMethod * SteadyStateWidget::createMethod(const CCopasiMethod::SubType & type)
{return NULL; /*CTSSMethod::createTSSMethod(type);*/}

bool SteadyStateWidget::runTask()
{
  if (!commonBeforeRunTask()) return false;

  /*
  saveTask();

  static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);

  setCursor(Qt::WaitCursor);
  CProgressBar * tmpBar = new CProgressBar();
  mSteadyStateTask->setCallBack(tmpBar);
  */

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(mObjectKey));
  assert(mSteadyStateTask);

  mSteadyStateTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);

  try
    {
      if (!mSteadyStateTask->process(true))
        {
          mProgressBar->finish();
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              mProgressBar->finish();
              QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      else if (mpHeaderWidget->mpUpdateModel->isChecked())
        {
          const CState *currentState = mSteadyStateTask->getState();
          if (currentState)
            (CCopasiDataModel::Global->getModel())->setInitialState(currentState);
        }
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

  mSteadyStateTask->restore();

  /*
  tmpBar->finish(); pdelete(tmpBar);

  protectedNotify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());
  unsetCursor();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(false);
  */

  commonAfterRunTask();

  pListView->switchToOtherWidget(211, ""); //change to the results window

  return true;
}

bool SteadyStateWidget::loadTask()
{
  loadCommon();
  loadMethod();
  //loadExecutable();
  //loadMethodParameters();

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(mObjectKey));
  assert(mSteadyStateTask);

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());
  assert(steadystateproblem);

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());
  assert(steadystatemethod);

  bool bJacobian = steadystateproblem->isJacobianRequested();
  bool bStatistics = steadystateproblem->isStabilityAnalysisRequested();
  taskJacobian->setChecked(bJacobian);
  if (bJacobian)
    {
      taskStability->setEnabled(true);
      taskStability->setChecked(bStatistics);
    }

  return true;
}

bool SteadyStateWidget::saveTask()
{
  saveCommon();
  saveMethod();
  //saveExecutable();
  //saveMethodParameters();

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(mObjectKey));
  assert(mSteadyStateTask);

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());
  assert(steadystateproblem);

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());
  assert(steadystatemethod);

  CCopasiDataModel::Global->getModel()->compileIfNecessary();
  //steadystateproblem->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

  bool bJacobian = taskJacobian->isChecked();
  bool bStatistics = taskStability->isChecked();

  steadystateproblem->setJacobianRequested(bJacobian);
  steadystateproblem->setStabilityAnalysisRequested(bStatistics);

  //loadSteadyStateTask();

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();
  return true;
}

/*bool SteadyStateWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action),
                               const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;
 
  switch (objectType)
    {
    case ListViews::FUNCTION:
      break;
    case ListViews::MODEL:
      CReportDefinitionVector* pReportDefinitionVector;
      pReportDefinitionVector = CCopasiDataModel::Global->getReportDefinitionList();
      if (pReportDefinitionVector)
        reportDefinitionButton->setEnabled(true);
      break;
    default:
      break;
    }
  return true;
}*/

void SteadyStateWidget::taskJacobianToggled()
{
  if (!taskJacobian->isChecked())
    {
      taskStability->setChecked(false);
      taskStability->setEnabled(false);
    }
  else taskStability->setEnabled(true);
}
