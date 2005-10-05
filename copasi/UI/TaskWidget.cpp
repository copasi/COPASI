/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/TaskWidget.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:51 $
   End CVS Header */

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
#include "plot/CPlotSpec2Vector.h"
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

  connect(mpBtnWidget->mpBtnRun, SIGNAL(clicked()), this, SLOT(runBtnClicked()));
  connect(mpBtnWidget->mpBtnRevert, SIGNAL(clicked()), this, SLOT(revertBtnClicked()));
  connect(mpBtnWidget->mpBtnReport, SIGNAL(clicked()), this, SLOT(reportBtnClicked()));
  connect(mpBtnWidget->mpBtnAssistant, SIGNAL(clicked()), this, SLOT(assistantBtnClicked()));
}

TaskWidget::~TaskWidget()
{}

//************************************************************

void TaskWidget::revertBtnClicked()
{
  loadTask();
}

void TaskWidget::runBtnClicked()
{
  runTask();
}

void TaskWidget::reportBtnClicked()
{
  CCopasiTask* task =
    dynamic_cast< CCopasiTask * >(GlobalKeys.get(mObjectKey));
  assert(task);

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(this); //TODO parent?
  pSelectDlg->setReport(&task->getReport());
  pSelectDlg->loadReportDefinitionVector();
  pSelectDlg->exec();

  delete pSelectDlg;
}

void TaskWidget::assistantBtnClicked()
{
  CCopasiTask* task =
    dynamic_cast< CCopasiTask * >(GlobalKeys.get(mObjectKey));
  assert(task);

  DefaultPlotDialog * pDlg = new DefaultPlotDialog(this);
  pDlg->setTask(task);
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

//************  executable button *******************

bool TaskWidget::loadExecutable()
{
  CCopasiTask* mpTask =
    dynamic_cast<CCopasiTask*>(GlobalKeys.get(mObjectKey));
  assert(mpTask);

  mpHeaderWidget->mpBoxExecutable->setChecked(mpTask->isScheduled());
  return true;
}

bool TaskWidget::saveExecutable()
{
  CCopasiTask* mpTask =
    dynamic_cast<CCopasiTask*>(GlobalKeys.get(mObjectKey));
  assert(mpTask);

  mpTask->setScheduled(mpHeaderWidget->mpBoxExecutable->isChecked());
  return true;
}

//************* parameter table ***********************

bool TaskWidget::formatMethodParameterTable(QTable * pParameterTable)
{
  pParameterTable->setNumRows(0);
  pParameterTable->setNumCols(1);
  pParameterTable->setColumnStretchable(0, true);
  QHeader *colHeader = pParameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  pParameterTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  return true;
}

bool TaskWidget::loadMethodParameters(QTable * pParameterTable)
{
  CCopasiTask* task =
    dynamic_cast<CCopasiTask *>(GlobalKeys.get(mObjectKey));
  if (!task) return false;

  CCopasiMethod* method = task->getMethod();
  if (!method) return false;

  QTableItem * pItem;
  QString value;
  QString strname;

  pParameterTable->setNumRows(method->size());
  QHeader *rowHeader = pParameterTable->verticalHeader();

  unsigned C_INT32 i;
  CCopasiParameter::Type Type;
  for (i = 0; i < method->size(); i++)
    {
      strname = FROM_UTF8(method->getName(i));
      rowHeader->setLabel(i, strname);

      value = getParameterValue(method, i, &Type);
      pItem = new QTableItem (pParameterTable, QTableItem::Always, value);
      pParameterTable->setItem(i, 0, pItem);
    }
  return true;
}

bool TaskWidget::saveMethodParameters(QTable * pParameterTable)
{
  CCopasiTask* task =
    dynamic_cast<CCopasiTask *>(GlobalKeys.get(mObjectKey));
  if (!task) return false;

  CCopasiMethod* method = task->getMethod();
  if (!method) return false;

  unsigned C_INT32 i;
  QTableItem * pItem;
  QString value;

  for (i = 0; i < method->size(); i++)
    {
      pItem = pParameterTable->item(i, 0);
      value = pItem->text();
      setParameterValue(method, i, value);
    }
  return true;
}

#ifdef XXXX
bool TaskWidget::addMethodpParameterTableToLayout(unsigned int row, unsigned int maxcol)
{
  methodParLabel = new QLabel(this, "methodParLabel");
  methodParLabel->setText(tr("Method parameters"));
  methodParLabel->setAlignment(int(QLabel::AlignVCenter
                                   | QLabel::AlignRight));
  methodParLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
  TaskWidgetLayout->addWidget(methodParLabel, row, 0);

  if (!constructMethodpParameterTable()) return false;
  TaskWidgetLayout->addMultiCellWidget(pParameterTable, row, row + 1, 1, maxcol);

  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Preferred);
  TaskWidgetLayout->addItem(spacer, row + 1, 0);

  return true;
}
#endif // XXXX

//*********************************************************************

bool TaskWidget::commonBeforeRunTask()
{
  // save the state of the widget
  if (!saveTask())
    {
      QMessageBox::warning(this, "Simulation Error",
                           CCopasiMessage::getAllMessageText().c_str(),
                           QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
      CCopasiMessage::clearDeque();
      return false;
    }

  CCopasiTask* task = dynamic_cast< CCopasiTask * >(GlobalKeys.get(mObjectKey));
  if (!task) return false;

  //set mouse cursor
  setCursor(Qt::WaitCursor);

  //handle autosave feature
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);

  //create progress bar
  mProgressBar = new CProgressBar();
  task->setCallBack(mProgressBar);

  return true;
}

bool TaskWidget::commonAfterRunTask()
{
  CCopasiTask* task = dynamic_cast< CCopasiTask * >(GlobalKeys.get(mObjectKey));
  if (!task) return false;

  if (mProgressBar)
  {mProgressBar->finish(); pdelete(mProgressBar);}
  task->setCallBack(NULL);

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

  if (!dynamic_cast< CCopasiTask * >(GlobalKeys.get(mObjectKey))) return false;

  return loadTask();
}
