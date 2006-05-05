/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TaskWidget.cpp,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/05 19:18:07 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qvalidator.h>
#include <qhbox.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qcombobox.h>

#include "TaskWidget.h"
#include "qtUtilities.h"

#include "listviews.h"
#include "DataModelGUI.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiMethod.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "MyLineEdit.h"
#include "utilities/CCopasiException.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "CReportDefinitionSelect.h"
#include "DefaultplotDialog.h"
#include "CQTaskHeaderWidget.h"
#include "CQTaskBtnWidget.h"

/*
 *  Constructs a TaskWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TaskWidget::TaskWidget(QWidget* parent, const char* name, WFlags fl)
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
      mpMethodLayout = new QGridLayout(0, 2, 2, 0, 6, "mpMethodLayout");
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

void TaskWidget::addMethodParameterTable(const unsigned C_INT32 & rows, unsigned int row)
{
  if (mpTblParameter) return;

  if (!mpMethodLayout)
    {
      mpMethodLayout = new QGridLayout(0, 1, 1, 0, 6, "mpMethodLayout");
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertLayout(0, mpMethodLayout);
      //Row = 0;
    }

  QWidget* pParent = mpMethodLayout->mainWidget();

  mpLblParameter = new QLabel(pParent, "mpLblParameter");
  mpLblParameter->setText(tr("Method Parameter"));
  mpLblParameter->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpTblParameter = new QTable(pParent, "mpTblParameter");
  mpTblParameter->setNumRows(rows);
  mpTblParameter->setNumCols(1);

  mpTblParameter->horizontalHeader()->setLabel(0, tr("Value"));
  mpTblParameter->verticalHeader()->setMovingEnabled(false);

  mpTblParameter->setFixedHeight(mpTblParameter->sizeHint().height() + 2);
  mpTblParameter->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed, 0, 0, mpTblParameter->sizePolicy().hasHeightForWidth()));

  mpSpacer1 = new QSpacerItem(0, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

  mpMethodLayout->addWidget(mpLblParameter, row, 0);
  mpMethodLayout->addWidget(mpTblParameter, row, 1);
  mpMethodLayout->addItem(mpSpacer1, row, 2);

  return;
}

void TaskWidget::addMethodSelectionBox(const unsigned C_INT32 * validMethods, unsigned int row)
{
  if (!mpMethodLayout)
    {
      mpMethodLayout = new QGridLayout(0, 1, 1, 0, 6, "mpMethodLayout");
      static_cast<QVBoxLayout *>(mpBtnWidget->layout())->insertLayout(0, mpMethodLayout);
    }

  QWidget* pParent = mpMethodLayout->mainWidget();

  mpLblMethod = new QLabel(pParent, "mpLblMethod");
  mpLblMethod->setText(tr("Method"));
  mpLblMethod->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpBoxMethod = new QComboBox(FALSE, pParent, "mpBoxMethod");

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
  runTask();
}

void TaskWidget::reportBtnClicked()
{
  if (!mpTask) return;

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(pListView);
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
      //std::cout << "plot created" << std::endl;
      protectedNotify(ListViews::PLOT, ListViews::ADD, "");
    }
  else
    {
      //std::cout << "no plot created" << std::endl;
    }

  if (pDlg)delete pDlg;
}

void TaskWidget::changeMethod(int /* index */)
{
  if (mpMethod != mpTask->getMethod())
    pdelete(mpMethod);

  CCopasiMethod::SubType Type =
    CCopasiMethod::TypeNameToEnum((const char *) mpBoxMethod->currentText().utf8());

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
      QTableItem * pItem;
      QString value;
      QString strname;

      mpTblParameter->setNumRows(mpMethod->size());
      QHeader *rowHeader = mpTblParameter->verticalHeader();

      unsigned C_INT32 i;
      CCopasiParameter::Type Type;
      for (i = 0; i < mpMethod->size(); i++)
        {
          strname = FROM_UTF8(mpMethod->getName(i));
          rowHeader->setLabel(i, strname);

          value = getParameterValue(mpMethod, i, &Type);
          pItem = new QTableItem (mpTblParameter, QTableItem::Always, value);
          mpTblParameter->setItem(i, 0, pItem);
        }
    }

  mpTblParameter->setFixedWidth(mpTblParameter->sizeHint().width() + 20);

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
  QTableItem * pItem;
  QString value;
  CCopasiParameter::Type Type;

  for (i = 0; i < mpMethod->size(); i++)
    {
      pItem = mpTblParameter->item(i, 0);
      value = pItem->text();
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
      QMessageBox::warning(this, "Simulation Error",
                           CCopasiMessage::getAllMessageText().c_str(),
                           QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      return false;
    }

  CCopasiMessage::clearDeque();
  if (!mpTask) return false;

  //set mouse cursor
  setCursor(Qt::WaitCursor);

  //handle autosave feature
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);

  //create progress bar
  mProgressBar = new CProgressBar();
  mpTask->setCallBack(mProgressBar);

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

  CCopasiDataModel::Global->finish();
  protectedNotify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());
  unsetCursor();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(false);

  return true;
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

bool TaskWidget::enter(const std::string & key)
{
  if (key != "") mObjectKey = key;

  mpTask = dynamic_cast< CCopasiTask * >(GlobalKeys.get(mObjectKey));

  // :TODO: We need a message here.
  if (!mpTask) return false;

  mpMethod = mpTask->getMethod();

  return loadTask();
}
