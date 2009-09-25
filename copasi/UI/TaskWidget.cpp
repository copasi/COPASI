// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/TaskWidget.cpp,v $
//   $Revision: 1.44 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/25 21:02:46 $
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
      mpMethodLayout = new QGridLayout();
      mpMethodLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertLayout(0, mpMethodLayout);
    }

  mpLblParameter = new QLabel(0, "mpLblParameter");
  mpLblParameter->setText(tr("Method Parameter"));
  mpLblParameter->setAlignment(int(Qt::AlignTop | Qt::AlignRight));

  mpTblParameter = new QTableWidget();
  mpTblParameter->setSelectionMode(QAbstractItemView::SingleSelection);

  // initial number of rows as well as columns
  mpTblParameter->setRowCount(1);
  mpTblParameter->setColumnCount(1);

  mpTblParameter->setHorizontalHeaderItem(0, new QTableWidgetItem());
  mpTblParameter->horizontalHeaderItem(0)->setText("Value");
  mpTblParameter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

  mpTblParameter->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblParameter->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  mpTblParameter->horizontalHeader()->hide();

  mpSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  QSpacerItem *mpSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

  mpMethodLayout->addWidget(mpLblParameter, row, 0);
  mpMethodLayout->addWidget(mpTblParameter, row, 1, row, 2);
  mpMethodLayout->addItem(mpSpacer1, row, 3);
  mpMethodLayout->addItem(mpSpacer2, row + 1, 1);

  return;
}

void TaskWidget::addMethodSelectionBox(const unsigned C_INT32 * validMethods, unsigned int row)
{
  if (!mpMethodLayout)
    {
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

  mpSpacer2 = new QSpacerItem(0, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

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
      QString strname;

      mpTblParameter->setRowCount(mpMethod->size());

      QAbstractItemModel* m = mpTblParameter->model();

      QHeaderView* vHeader = mpTblParameter->verticalHeader();
      QHeaderView* hHeader = mpTblParameter->horizontalHeader();

      std::cout << hHeader->length() << " A1 " << vHeader->width() << std::endl;
      std::cout << vHeader->length() << " B1 " << hHeader->height() << std::endl;

      std::cout << "hHeader->sizeHint().height() = " << hHeader->sizeHint().height() << std::endl;
      std::cout << "hHeader->sizeHint().width() = " << hHeader->sizeHint().width() << std::endl;
      std::cout << "hHeader->count() = " << hHeader->count() << std::endl;
      std::cout << "vHeader->sizeHint().height() = " << vHeader->sizeHint().height() << std::endl;
      std::cout << "vHeader->sizeHint().width() = " << vHeader->sizeHint().width() << std::endl;
      std::cout << "vHeader->count() = " << vHeader->count() << std::endl;

      unsigned C_INT32 i;
      CCopasiParameter::Type Type;

      for (i = 0; i < mpMethod->size(); i++)
        {
          strname = FROM_UTF8(mpMethod->getName(i));

          // create item of the current row and give it a name
          mpTblParameter->setVerticalHeaderItem(i, new QTableWidgetItem());
          mpTblParameter->verticalHeaderItem(i)->setText(strname);

          std::cout << "mpTblParameter->verticalHeaderItem(i)->sizeHint().height() = " << mpTblParameter->verticalHeaderItem(i)->sizeHint().height()
                    << "mpTblParameter->verticalHeaderItem(i)->sizeHint().width() = " << mpTblParameter->verticalHeaderItem(i)->sizeHint().width() << std::endl;

          std::cout << "rowCount at iteration " << i << " = " << mpTblParameter->rowCount() << std::endl;

          value = getParameterValue(mpMethod, i, &Type);

          QTableWidgetItem *itemValue = new QTableWidgetItem();
          itemValue->setData(Qt::EditRole, QVariant(value));
          itemValue->setTextAlignment(Qt::AlignRight);
          mpTblParameter->setItem(i, 0, itemValue);

          std::cout << "rowHeight(" << i << ") = " << mpTblParameter->rowHeight(i) << std::endl;
        }

      mpTblParameter->resizeColumnsToContents();
      mpTblParameter->resizeRowsToContents();

      std::cout << "columnWidth(0) = " << mpTblParameter->columnWidth(0) << "columnWidth(1) = " << mpTblParameter->columnWidth(1) << std::endl;

      unsigned C_INT32 singleFrame = mpTblParameter->frameWidth();
//  int doubleFrame = 2 * mpTblParameter->frameWidth();
      unsigned C_INT32 doubleFrame = 2 * singleFrame;
      std::cout << "doubleFrame = " << doubleFrame << std::endl;

      /*
        int doubleFrame = 2 * mpTblParameter->frameWidth();
        std::cout << "doubleFrame = " << doubleFrame << std::endl;

        int w = hHeader->length() + vHeader->width() + doubleFrame;
        int h = vHeader->length() + hHeader->height() + doubleFrame;
      */
      std::cout << hHeader->length() << " A2 " << vHeader->width() << std::endl;
      std::cout << vHeader->length() << " B2 " << hHeader->height() << std::endl;

      std::cout << "hHeader->sizeHint().height() = " << hHeader->sizeHint().height() << std::endl;
      std::cout << "hHeader->sizeHint().width() = " << hHeader->sizeHint().width() << std::endl;
      std::cout << "hHeader->count() = " << hHeader->count() << std::endl;
      std::cout << "vHeader->sizeHint().height() = " << vHeader->sizeHint().height() << std::endl;
      std::cout << "vHeader->sizeHint().width() = " << vHeader->sizeHint().width() << std::endl;
      std::cout << "vHeader->count() = " << vHeader->count() << std::endl;

      unsigned C_INT32 index;

      unsigned C_INT32 colCount = m->columnCount();
      unsigned C_INT32 w = 0;

      for (index = 0; index < colCount; index++)
        {
          w += mpTblParameter->columnWidth(index) + doubleFrame;
          std::cout << "i=" << index << ": w = " << w << std::endl;
//    std::cout << "sizeHintForColumn = " << mpTblParameter->sizeHintForColumn(i) << std::endl;
        }

      unsigned C_INT32 rowCount = m->rowCount();
      unsigned C_INT32 h = 0;

      for (index = 0; index < rowCount; index++)
        {
          h += mpTblParameter->rowHeight(index) + singleFrame;
          std::cout << "i=" << index << ": h = " << h << std::endl;
//    std::cout << "sizeHintForRow = " << mpTblParameter->sizeHintForRow(i) << std::endl;
        }

      /*
        w += mpTblParameter->verticalHeader()->width() + doubleFrame;
        h += mpTblParameter->horizontalHeader()->height() + doubleFrame;
      */

//  w += vHeader->sizeHint().width() + vHeader->width();
//  h += hHeader->sizeHint().height() + hHeader->height();
      w += vHeader->sizeHint().width();
      h += hHeader->sizeHint().height();

      std::cout << "colCount = " << colCount << " - rowCount = " << rowCount << std::endl;
      std::cout << "w = " << w << " - h = " << h << std::endl;

      /*
        std::cout << "mpTblParameter->sizeHint().height() = " << mpTblParameter->sizeHint().height() << std::endl;
        std::cout << "mpTblParameter->sizeHint().width() = " << mpTblParameter->sizeHint().width() << std::endl;
      */
      std::cout << "mpTblParameter->sizeHint().height() = " << mpTblParameter->sizeHint().height() << std::endl;
      std::cout << "mpTblParameter->sizeHint().width() = " << mpTblParameter->sizeHint().width() << std::endl;

      /*
        mpTblParameter->setFixedHeight(hHeader->length());
        mpTblParameter->setFixedWidth(vHeader->length());
      */
      /*
        mpTblParameter->setFixedHeight(230 );
        mpTblParameter->setFixedWidth(320);

        mpTblParameter->setFixedHeight(242);
        mpTblParameter->setFixedWidth(319);
      */
      // mpTblParameter->setMinimumHeight(h);
      mpTblParameter->setMinimumWidth(w);
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
      std::cout << "value = " << value.toFloat() << std::endl;

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
