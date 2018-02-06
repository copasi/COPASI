// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtCore/QtDebug>
#include <QFrame>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QComboBox>
#include <QApplication>

#include "TaskWidget.h"
#include "qtUtilities.h"
#include "copasiui3window.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "CQMessageBox.h"
#include "MyLineEdit.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "CQReportDefinitionSelect.h"
#include "DefaultplotDialog.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskMethodWidget.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskThread.h"
#include "CQOptPopulation.h"

#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/plotUI/CopasiPlot.h"
#include "copasi/plotUI/plotwindow.h"
#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptPopulationMethod.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

/*
 *  Constructs a TaskWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TaskWidget::TaskWidget(QWidget* parent, const char* name, Qt::WindowFlags fl):
  CopasiWidget(parent, name, fl),
  mProgressBar(NULL),
  mpHeaderWidget(NULL),
  mpMethodWidget(NULL),
  mpBtnWidget(NULL),
  mpMethodLayout(NULL),
  mpSpacer1(NULL),
  mpSpacer2(NULL),
  mpTask(NULL),
  mpMethod(NULL),
  mChanged(false)
{
  if (!name)
    setObjectName("TaskWidget");

  setWindowTitle(trUtf8("TaskWidget"));

  mpTaskThread = new CQTaskThread(this);

  mpHeaderWidget = new CQTaskHeaderWidget(this);
  mpMethodWidget = new CQTaskMethodWidget(this);
  mpBtnWidget = new CQTaskBtnWidget(this);

  connect(mpBtnWidget->mpBtnRun, SIGNAL(clicked()), this, SLOT(runBtnClicked()));
  connect(mpBtnWidget->mpBtnRevert, SIGNAL(clicked()), this, SLOT(revertBtnClicked()));
  connect(mpBtnWidget->mpBtnReport, SIGNAL(clicked()), this, SLOT(reportBtnClicked()));
  connect(mpBtnWidget->mpBtnAssistant, SIGNAL(clicked()), this, SLOT(assistantBtnClicked()));

  connect(mpTaskThread, SIGNAL(finished()), this, SLOT(slotFinishThread()));
}

TaskWidget::~TaskWidget()
{
  pdelete(mpTaskThread);
}

void TaskWidget::revertBtnClicked()
{
  if (!mpTask) return;

  CCopasiMethod* pMethod = mpTask->getMethod();

  if (pMethod != mpMethod)
    {
      pdelete(mpMethod);
      mpMethod = pMethod;
    }

  loadTask();
}

void TaskWidget::runBtnClicked()
{
  // Assure that all edits to the current widget are committed.
  mpBtnWidget->mpBtnRun->setFocus();

  runTask();
}

void TaskWidget::reportBtnClicked()
{
  if (!mpTask) return;

  CQReportDefinitionSelect * pSelectDlg = new CQReportDefinitionSelect(mpListView);
  pSelectDlg->setReport(&mpTask->getReport());
  pSelectDlg->loadReportDefinitionVector();
  pSelectDlg->exec();

  delete pSelectDlg;
}

void TaskWidget::assistantBtnClicked()
{
  if (!mpTask) return;

  saveTask(); //this is necessary since the output may use information from the problem

  DefaultPlotDialog * pDlg = new DefaultPlotDialog(this);
  pDlg->setTask(mpTask);

  if (pDlg->exec() == QDialog::Accepted)
    {
      protectedNotify(ListViews::PLOT, ListViews::ADD, "");
    }

  if (pDlg)delete pDlg;
}

//************  executable button *******************

bool TaskWidget::loadCommon()
{
  if (!mpTask) return false;

  mpHeaderWidget->mpBoxExecutable->setChecked(mpTask->isScheduled());
  mpHeaderWidget->mpUpdateModel->setChecked(mpTask->isUpdateModel());

  mpHeaderWidget->saved();
  return true;
}

bool TaskWidget::saveCommon()
{
  if (!mpTask) return false;

  bool Value = mpHeaderWidget->mpBoxExecutable->isChecked();

  if (mpTask->isScheduled() != Value)
    {
      mpTask->setScheduled(Value);
      mChanged = true;
    }

  Value = mpHeaderWidget->mpUpdateModel->isChecked();

  if (mpTask->isUpdateModel() != Value)
    {
      mpTask->setUpdateModel(Value);
      mChanged = true;
    }

  mpHeaderWidget->saved();
  return true;
}

//************* parameter table ***********************

bool TaskWidget::loadMethod()
{
  if (!mpTask) return false;

  mpMethodWidget->setTask(mpTask);

  return mpMethodWidget->loadMethod();
}

void TaskWidget::adjustTable()
{
#ifdef DEBUG_UI
  qDebug() << "--> TaskWidget::adjustTable <--";
#endif

  // mpTblParameter->resizeColumnsToContents();
  // mpTblParameter->resizeRowsToContents();

  /*
  mpTblParameter->setFixedSize(mpTblParameter->columnWidth(0) + mpTblParameter->verticalHeader()->sizeHint().width() + 5,
                               mpTblParameter->verticalHeader()->sizeHint().height() * mpTblParameter->rowCount() + 5);
                               */
}

bool TaskWidget::saveMethod()
{
  if (!mpTask) return false;

  mChanged &= mpMethodWidget->saveMethod();

  return true;
}

bool TaskWidget::commonBeforeRunTask()
{
  // save the state of the widget
  if (!saveTask())
    {
      CQMessageBox::critical(this, "Simulation Error",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      return false;
    }

  if (!mpTask) return false;

  if (mProgressBar != NULL)
    {
      //CQMessageBox::critical(this, "Task in Progress",
      //                       "A task is currently running, another cannot be started before the current task ended.",
      //                       QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      return false;
    }

  // if overwrite is enabled and the file exists, then ask
  if (!mpTask->getReport().getTarget().empty() &&
      mpTask->getReport().confirmOverwrite())
    {
      // The target might be a relative path
      std::string Target = mpTask->getReport().getTarget();

      if (CDirEntry::isRelativePath(Target) &&
          !CDirEntry::makePathAbsolute(Target, mpDataModel->getReferenceDirectory()))
        Target = CDirEntry::fileName(Target);

      if (CDirEntry::exist(Target) &&
          QMessageBox::question(this,
                                QString("Confirm Overwrite"),
                                QString("The report file already exists. Would you like to overwrite it? \n\n(You can disable this dialog by clicking the 'Report' button.)"),
                                QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return false;
    }

  //set mouse cursor
  setCursor(Qt::WaitCursor);

  //handle autosave feature
  CopasiUI3Window::getMainWindow()->autoSave();
  CopasiUI3Window::getMainWindow()->suspendAutoSave(true);

  //create progress bar
  mProgressBar = CProgressBar::create();
  mpTask->setCallBack(mProgressBar);

  CCopasiMessage::clearDeque();

  // create population display if needed
  if (CRootContainer::getConfiguration()->displayPopulations())
    {

      if (dynamic_cast<COptTask*>(mpTask) != NULL || dynamic_cast<CFitTask*>(mpTask) != NULL)
        {
          CopasiUI3Window* pWindow = CopasiUI3Window::getMainWindow();
          CQOptPopulation* pPopWidget = pWindow->getPopulationDisplay();
          COptPopulationMethod* pMethod = dynamic_cast<COptPopulationMethod*>(mpTask->getMethod());
          pPopWidget->setMethod(pMethod);

          if (pMethod != NULL)
            {
              pPopWidget->addToMainWindow(pWindow);
              pPopWidget->show();
              mpDataModel->addInterface(pPopWidget);
            }
        }
    }

  return true;
}

bool TaskWidget::commonAfterRunTask()
{
  if (!mpTask) return false;

  if (CRootContainer::getConfiguration()->displayPopulations())
    {

      if (dynamic_cast<COptTask*>(mpTask) != NULL || dynamic_cast<CFitTask*>(mpTask) != NULL)
        {
          CopasiUI3Window* pWindow = CopasiUI3Window::getMainWindow();
          CQOptPopulation* pPopWidget = pWindow->getPopulationDisplay();
          COptPopulationMethod* pMethod = dynamic_cast<COptPopulationMethod*>(mpTask->getMethod());
          pPopWidget->setMethod(NULL);

          if (pMethod != NULL)
            {
              mpDataModel->removeInterface(pPopWidget);
            }
        }
    }

  if (mProgressBar != NULL)
    {
      mProgressBar->finish();
      mProgressBar->deleteLater();
      mProgressBar = NULL;
    }

  mpTask->setCallBack(NULL);

  CCopasiMessage::clearDeque();

  assert(mpDataModel != NULL);
  mpDataModel->finish();

  CMathContainer * pContainer = mpTask->getMathContainer();
  protectedNotify(ListViews::STATE, ListViews::CHANGE, pContainer->getModel().getKey());

  unsetCursor();
  CopasiUI3Window::getMainWindow()->suspendAutoSave(false);

  return loadTask();
}

bool TaskWidget::commonRunTask()
{
  // Initialize the task
  try
    {
      assert(mpDataModel != NULL);

      if (!mpTask->initialize(CCopasiTask::OUTPUT_UI, mpDataModel, NULL))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException & /*Exception*/)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          if (mProgressBar != NULL) mProgressBar->finish();

          CQMessageBox::critical(this, "Initialization Error",
                                 CCopasiMessage::getAllMessageText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

          finishTask();
          return false;
        }
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::ERROR)
    {
      if (mProgressBar != NULL) mProgressBar->finish();

      CQMessageBox::critical(this, "Initialization Error",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

      finishTask();
      return false;
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        CQMessageBox::question(this, "Initialization Warning",
                               CCopasiMessage::getAllMessageText().c_str(),
                               QMessageBox::Ignore | QMessageBox::Abort, QMessageBox::Ignore);

      if (Result == QMessageBox::Abort)
        {
          finishTask();
          return false;
        }
    }

  CCopasiMessage::clearDeque();

  // Execute the task
  mpTaskThread->start();

  return true;
}

void TaskWidget::slotFinishThread()
{
  if (!mpTaskThread->success() &&
      CCopasiMessage::size() != 0)
    {
      CQMessageBox::critical(this, "Calculation Error",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
    }
  else if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      CQMessageBox::information(this, "Calculation Warning",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
    }

  finishTask();
}

void TaskWidget::finishTask()
{
  CCopasiMessage::clearDeque();

  try {mpTask->restore();}

  catch (CCopasiException & /*Exception*/)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          if (mProgressBar != NULL) mProgressBar->finish();

          CQMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  catch (...) {}

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      CQMessageBox::information(this, "Calculation Warning",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
    }

  CCopasiMessage::clearDeque();

  commonAfterRunTask();

  taskFinishedEvent();
}

bool TaskWidget::taskFinishedEvent()
{
  return true;
}

CCopasiTask* TaskWidget::getTask()
{
  return mpTask;
}
//*********************************************************************

bool TaskWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates)
    {
      return true;
    }

  switch (objectType)
    {
      case ListViews::MODEL:

        if (action == ListViews::ADD &&
            mpMethodWidget != NULL)
          {
            mpMethodWidget->clearHistory();
          }

        break;

      default:
        break;
    }

  return true;
}

bool TaskWidget::leave()
{
  return saveTask();
}

bool TaskWidget::enterProtected()
{
  mpTask = dynamic_cast< CCopasiTask * >(mpObject);

  // :TODO: We need a message here.
  if (!mpTask) return false;

  mpMethod = mpTask->getMethod();

  return loadTask();
}

CCopasiMethod * TaskWidget::createMethod(const CTaskEnum::Method & type)
{
  CCopasiMethod * pMethod = NULL;

  if (mpTask != NULL)
    {
      pMethod = mpTask->createMethod(type);
    }

  return pMethod;
}
