// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/TaskWidget.cpp,v $
//   $Revision: 1.45 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/28 17:06:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QFrame>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QComboBox>

#include "TaskWidget.h"
#include "qtUtilities.h"

#include "listviews.h"
#include "DataModelGUI.h"
#include "CQMessageBox.h"
#include "MyLineEdit.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "CReportDefinitionSelect.h"
#include "DefaultplotDialog.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskBtnWidget.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiMethod.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiException.h"

/*
 *  Constructs a TaskWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TaskWidget::TaskWidget(QWidget* parent, const char* name, Qt::WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("TaskWidget");

  setCaption(trUtf8("TaskWidget"));

  mpHeaderWidget = new CQTaskHeaderWidget(this);
  mpBtnWidget = new CQTaskBtnWidget(this);

  mpMethodLayout = NULL;
  mpLblParameter = NULL;
  mpTblParameter = NULL;
  mpSpacer1 = NULL;
  mpLblMethod = NULL;
  mpBoxMethod = NULL;
  mpSpacer2 = NULL;

  mpTask = NULL;
  mpMethod = NULL;;

  connect(mpBtnWidget->mpBtnRun, SIGNAL(clicked()), this, SLOT(runBtnClicked()));
  connect(mpBtnWidget->mpBtnRevert, SIGNAL(clicked()), this, SLOT(revertBtnClicked()));
  connect(mpBtnWidget->mpBtnReport, SIGNAL(clicked()), this, SLOT(reportBtnClicked()));
  connect(mpBtnWidget->mpBtnAssistant, SIGNAL(clicked()), this, SLOT(assistantBtnClicked()));
}

TaskWidget::~TaskWidget()
{}

//************************************************************

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

  mpLblParameter = new QLabel(0, "mpLblParameter");
  mpLblParameter->setText(tr("Parameter"));
  mpLblParameter->setAlignment(int(Qt::AlignTop | Qt::AlignRight));

  mpTblParameter = new QTableWidget();
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

  if (row == 0)
    {
      mpSpacer1 = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
      mpMethodLayout->addItem(mpSpacer1, row + 1, 2);
    }

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

//  QWidget* pParent = mpMethodLayout->mainWidget();

//  mpLblMethod = new QLabel(pParent, "mpLblMethod");
  mpLblMethod = new QLabel(0, "mpLblMethod");
  mpLblMethod->setText(tr("Method"));
  mpLblMethod->setAlignment(int(Qt::AlignTop | Qt::AlignRight));

//  mpBoxMethod = new QComboBox(false, pParent, "mpBoxMethod");
  mpBoxMethod = new QComboBox();

  unsigned C_INT32 i;

  for (i = 0; validMethods[i] != CCopasiMethod::unset; i++)
    mpBoxMethod->insertItem(FROM_UTF8(CCopasiMethod::SubTypeName[validMethods[i]]));

  mpSpacer2 = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

  mpMethodLayout->addWidget(mpLblMethod, row, 0);
  mpMethodLayout->addWidget(mpBoxMethod, row, 1);
  mpMethodLayout->addItem(mpSpacer2, row, 2);

  connect(mpBoxMethod, SIGNAL(activated(int)), this, SLOT(changeMethod(int)));

  return;
}

void TaskWidget::revertBtnClicked()
{
  if (!mpTask) return;

  CCopasiMethod* method = mpTask->getMethod();

  if (method != mpMethod)
    {
      pdelete(mpMethod);
      mpMethod = method;
    }

  loadTask();
}

void TaskWidget::runBtnClicked()
{
  // Assure that all edits to the current widget are commited.
  mpBtnWidget->mpBtnRun->setFocus();

  runTask();
}

void TaskWidget::reportBtnClicked()
{
  if (!mpTask) return;

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(mpListView);
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

void TaskWidget::changeMethod(int /* index */)
{
  if (mpMethod != mpTask->getMethod())
    pdelete(mpMethod);

  CCopasiMethod::SubType Type =
    CCopasiMethod::TypeNameToEnum(TO_UTF8(mpBoxMethod->currentText()));

  mpMethod = createMethod(Type);

  loadMethod();

  return;
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

  if (!mpMethod) return false;

  if (mpBoxMethod)
    mpBoxMethod->setCurrentText(FROM_UTF8(CCopasiMethod::SubTypeName[mpMethod->getSubType()]));

  if (mpTblParameter)
    {
      QString value;

      mpTblParameter->setRowCount(mpMethod->size());

      unsigned C_INT32 i;
      CCopasiParameter::Type Type;

      for (i = 0; i < mpMethod->size(); i++)
        {
          // create item of the current row and give it a name
          mpTblParameter->setVerticalHeaderItem(i, new QTableWidgetItem());
          mpTblParameter->verticalHeaderItem(i)->setText(FROM_UTF8(mpMethod->getName(i)));

          value = getParameterValue(mpMethod, i, &Type);

          QTableWidgetItem *itemValue = new QTableWidgetItem();
          itemValue->setData(Qt::EditRole, QVariant(value));
          itemValue->setTextAlignment(Qt::AlignRight);
          mpTblParameter->setItem(i, 0, itemValue);
        }

      mpTblParameter->resizeColumnsToContents();
      mpTblParameter->resizeRowsToContents();

      mpTblParameter->horizontalHeaderItem(0)->setSizeHint(QSize(mpTblParameter->columnWidth(0), 22));

      QHeaderView* vHeader = mpTblParameter->verticalHeader();

      if (mpTblParameter->sizePolicy().verticalPolicy() == QSizePolicy::Maximum)
        {
          mpTblParameter->setMaximumHeight(vHeader->sizeHint().height() * mpTblParameter->rowCount() + 5);
        }
      else
        {
          mpTblParameter->setMinimumHeight(vHeader->sizeHint().height() * mpTblParameter->rowCount() + 5);
        }

      mpTblParameter->setMinimumWidth(mpTblParameter->columnWidth(0) + vHeader->sizeHint().width() + 22);
    }

  return true;
}

bool TaskWidget::saveMethod()
{
  if (!mpTask) return false;

  CCopasiMethod* method = mpTask->getMethod();

  if (!method) return false;

  if (method->getSubType() != mpMethod->getSubType())
    {
      mpTask->setMethodType(mpMethod->getSubType());
      mChanged = true;
    }

  mpMethod = mpTask->getMethod();

  unsigned C_INT32 i;
  QString value;
  CCopasiParameter::Type Type;

  for (i = 0; i < mpMethod->size(); i++)
    {
      if (!mpTblParameter)
        break;

      if (!mpTblParameter->item(i, 0))
        continue;

      value = mpTblParameter->item(i, 0)->text();

      if (value != getParameterValue(mpMethod, i, &Type))
        {
          setParameterValue(mpMethod, i, value);
          mChanged = true;
        }
    }

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
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);

  //create progress bar
  mProgressBar = new CProgressBar();
  mpTask->setCallBack(mProgressBar);

  CCopasiMessage::clearDeque();
  return true;
}

bool TaskWidget::commonAfterRunTask()
{
  if (!mpTask) return false;

  if (mProgressBar)
    {
      mProgressBar->finish();
      pdelete(mProgressBar);
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
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(false);

  return loadTask();
}

bool TaskWidget::commonRunTask()
{
  bool success = true;

  // Initialize the task
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

      if (!mpTask->initialize(CCopasiTask::OUTPUT_COMPLETE, (*CCopasiRootContainer::getDatamodelList())[0], NULL))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          CQMessageBox::critical(this, "Initialization Error",
                                 CCopasiMessage::getAllMessageText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

          success = false;
          goto finish;
        }
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::ERROR)
    {
      mProgressBar->finish();
      CQMessageBox::critical(this, "Initialization Error",
                             CCopasiMessage::getAllMessageText().c_str(),
                             QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

      success = false;
      goto finish;
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      C_INT Result =
        CQMessageBox::question(this, "Initialization Warning",
                               CCopasiMessage::getAllMessageText().c_str(),
                               QMessageBox::Ignore | QMessageBox::Abort, QMessageBox::Ignore);

      if (Result == QMessageBox::Abort)
        {
          success = false;
          goto finish;
        }
    }

  CCopasiMessage::clearDeque();

  // Execute the task
  try
    {
      if (!mpTask->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
          CQMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
        }

      success = false;
      goto finish;
    }

  if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
    {
      CQMessageBox::information(this, "Calculation Warning",
                                CCopasiMessage::getAllMessageText().c_str(),
                                QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
    }

finish:

  CCopasiMessage::clearDeque();

  try {mpTask->restore();}

  catch (CCopasiException Exception)
    {
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          mProgressBar->finish();
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

  return success;
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
