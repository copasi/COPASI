// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/TaskWidget.cpp,v $
//   $Revision: 1.66 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/20 16:26:55 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtDebug>
#include <QFrame>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QComboBox>
#include <qapplication.h>

#include "TaskWidget.h"
#include "qtUtilities.h"

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
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiMethod.h"
#include "utilities/CCopasiException.h"
#include "utilities/COutputHandler.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "UI/CQTaskThread.h"
#include "plotUI/CopasiPlot.h"
#include "plotUI/plotwindow.h"


/*
 *  Constructs a TaskWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TaskWidget::TaskWidget(QWidget* parent, const char* name, Qt::WFlags fl):
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

//************************************************************
#ifdef XXXX
void TaskWidget::addHeaderToGrid(unsigned int row)
{
  if (!mpMethodLayout)
    {
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertStretch(0, 0);

      mpMethodLayout = new QGridLayout();
      mpMethodLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertLayout(0, mpMethodLayout);
    }

  mpMethodLayout->addMultiCellWidget(mpHeaderWidget, row, row, 1, 2);
}

bool TaskWidget::addHLineToGrid(QGridLayout* grid, unsigned int row, unsigned int maxcol)
{
  QFrame * line = new QFrame(this, "line");
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  grid->addMultiCellWidget(line, row, row, 0, maxcol);

  return true;
}

void TaskWidget::addMethodParameterTable(unsigned int row)
{
  if (mpTblParameter) return;

  if (!mpMethodLayout)
    {
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertStretch(0, 0);

      mpMethodLayout = new QGridLayout();
      mpMethodLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertLayout(0, mpMethodLayout);
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->setStretchFactor(mpMethodLayout, 10);
    }

  mpLblParameter = new QLabel(this, "mpLblParameter");
  mpLblParameter->setText(tr("Parameter"));
  mpLblParameter->setAlignment(int(Qt::AlignTop | Qt::AlignRight));

  mpTblParameter = new QTableWidget(this);
  mpTblParameter->setSelectionMode(QAbstractItemView::SingleSelection);
  mpTblParameter->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  mpTblParameter->setColumnCount(1);

  mpTblParameter->setHorizontalHeaderItem(0, new QTableWidgetItem());
  mpTblParameter->horizontalHeaderItem(0)->setText("Value");
  mpTblParameter->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);

  mpTblParameter->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblParameter->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblParameter->horizontalHeader()->hide();

  mpMethodLayout->addWidget(mpLblParameter, row, 0);
  mpMethodLayout->addWidget(mpTblParameter, row, 1, row, 2);

#ifdef DEBUG_UI
  qDebug() << "row = " << row;
#endif

  connect(mpTblParameter, SIGNAL(cellChanged(int, int)), this, SLOT(adjustTable()));

  return;
}

void TaskWidget::addMethodSelectionBox(const unsigned C_INT32 * validMethods, unsigned int row)
{
  if (!mpMethodLayout)
    {
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertStretch(0, 0);

      mpMethodLayout = new QGridLayout();
      mpMethodLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertLayout(0, mpMethodLayout);
    }

  mpLblMethod = new QLabel(0, "mpLblMethod");
  mpLblMethod->setText(tr("Method"));
  mpLblMethod->setAlignment(int(Qt::AlignTop | Qt::AlignRight));

  mpBoxMethod = new QComboBox(this);

  unsigned C_INT32 i;

  for (i = 0; validMethods[i] != CCopasiMethod::unset; i++)
    mpBoxMethod->insertItem(QString::fromUtf8(CCopasiMethod::SubTypeName[validMethods[i]]));

  mpSpacer2 = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

  mpMethodLayout->addWidget(mpLblMethod, row, 0);
  mpMethodLayout->addWidget(mpBoxMethod, row, 1);
  mpMethodLayout->addItem(mpSpacer2, row, 2);

  connect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));

  return;
}
#endif // XXXX

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

  //set mouse cursor
  setCursor(Qt::WaitCursor);

  //handle autosave feature
  CopasiUI3Window::getMainWindow()->autoSave();
  CopasiUI3Window::getMainWindow()->suspendAutoSave(true);
  CopasiUI3Window::getMainWindow()->disableSliders(true);

  //create progress bar
  mProgressBar = CProgressBar::create();
  mpTask->setCallBack(mProgressBar);

  CCopasiMessage::clearDeque();
  return true;
}

bool TaskWidget::commonAfterRunTask()
{
  if (!mpTask) return false;

  if (mProgressBar != NULL)
    {
      mProgressBar->finish();
      mProgressBar->deleteLater();
      mProgressBar = NULL;
    }

  mpTask->setCallBack(NULL);

  CCopasiMessage::clearDeque();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  (*CCopasiRootContainer::getDatamodelList())[0]->finish();

  // Update all values shown in the GUI
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  pModel->updateSimulatedValues(true);
  pModel->updateNonSimulatedValues();

  protectedNotify(ListViews::STATE, ListViews::CHANGE, (*CCopasiRootContainer::getDatamodelList())[0]->getModel()->getKey());
  unsetCursor();
  CopasiUI3Window::getMainWindow()->suspendAutoSave(false);
  CopasiUI3Window::getMainWindow()->disableSliders(false);

  return loadTask();
}

bool TaskWidget::commonRunTask()
{
  // Initialize the task
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if (!mpTask->initialize(CCopasiTask::OUTPUT_UI, (*CCopasiRootContainer::getDatamodelList())[0], NULL))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
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

  catch (CCopasiException Exception)
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

bool TaskWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
      case ListViews::MODEL:
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
