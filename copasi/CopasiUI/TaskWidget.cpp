/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TaskWidget.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 13:47:33 $
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

  mainLayout = new QVBoxLayout(this, 11, 8, "TaskMainWidget");

  TaskWidgetLayout = new QGridLayout(mainLayout, 1, 1, 8, "TaskWidgetLayout");

  //*******************

  nameLayout = new QHBoxLayout();

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("<h2>??? Task</h2>"));
  taskNameLabel->setAlignment(int(QLabel::AlignVCenter
                                  | QLabel::AlignLeft));
  nameLayout->addWidget(taskNameLabel);

  QSpacerItem* tmpSpacer = new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);
  nameLayout->addItem(tmpSpacer);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("executable"));
  bExecutable->setChecked(parent == NULL);
  bExecutable->setEnabled(parent != NULL);
  nameLayout->addWidget(bExecutable);

  //  TaskWidgetLayout->addMultiCellLayout(tmpLayout, 0, 0, 1, 3);

  //*******************

  lineButton = new QFrame(this, "line");
  lineButton->setFrameShape(QFrame::HLine);
  lineButton->setFrameShadow(QFrame::Sunken);
  mainLayout->addWidget(lineButton);

  //*******************

  buttonLayout = new QHBoxLayout(0, 0, 6, "buttonLayout");

  runTaskButton = new QPushButton(this, "runTaskButton");
  runTaskButton->setText(trUtf8("Run"));
  buttonLayout->addWidget(runTaskButton);

  cancelChangeButton = new QPushButton(this, "cancelChangeButton");
  cancelChangeButton->setText(trUtf8("Revert"));
  buttonLayout->addWidget(cancelChangeButton);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("Report"));
  buttonLayout->addWidget(reportDefinitionButton);

  outputDefinitionButton = new QPushButton(this, "OutputDefinition");
  outputDefinitionButton->setText(trUtf8("Output Assistant"));
  buttonLayout->addWidget(outputDefinitionButton);

  mainLayout->addLayout(buttonLayout);

  //*******************

  //setTabOrder(bExecutable, setInitialState);
  //setTabOrder(parameterTable, bRunTask);
  //  setTabOrder(bRunTask, commitChange);
  //  setTabOrder(commitChange, cancelChangeButton);
  setTabOrder(runTaskButton, cancelChangeButton);
  setTabOrder(cancelChangeButton, reportDefinitionButton);

  // signals and slots connections
  connect(cancelChangeButton, SIGNAL(clicked()), this, SLOT(CancelChangeClicked()));
  connect(runTaskButton, SIGNAL(clicked()), this, SLOT(runTaskClicked()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));
  connect(outputDefinitionButton, SIGNAL(clicked()), this, SLOT(outputDefinitionClicked()));
  //connect(bExecutable, SIGNAL(clicked()), this, SLOT(EnableRunTask()));
  //connect(ComboBox1, SIGNAL(activated(int)), this, SLOT(UpdateMethod()));
}

TaskWidget::~TaskWidget()
{}

//************************************************************

void TaskWidget::CancelChangeClicked()
{
  loadTask();
}

void TaskWidget::runTaskClicked()
{
  runTask();
}

void TaskWidget::ReportDefinitionClicked()
{
  CCopasiTask* task =
    dynamic_cast< CCopasiTask * >(GlobalKeys.get(objKey));
  assert(task);

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(this); //TODO parent?
  pSelectDlg->setReport(&task->getReport());
  pSelectDlg->loadReportDefinitionVector();
  pSelectDlg->exec();

  delete pSelectDlg;
}

void TaskWidget::outputDefinitionClicked()
{
  CCopasiTask* task =
    dynamic_cast< CCopasiTask * >(GlobalKeys.get(objKey));
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
    dynamic_cast<CCopasiTask*>(GlobalKeys.get(objKey));
  assert(mpTask);

  bExecutable->setChecked(mpTask->isScheduled());
  return true;
}

bool TaskWidget::saveExecutable()
{
  CCopasiTask* mpTask =
    dynamic_cast<CCopasiTask*>(GlobalKeys.get(objKey));
  assert(mpTask);

  bool bScheduled = bExecutable->isChecked();
  mpTask->setScheduled(bScheduled);
  return true;
}

//************* parameter table ***********************

bool TaskWidget::constructMethodParameterTable()
{
  parameterTable = new QTable(this, "parameterTable");
  if (!parameterTable) return false;

  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  parameterTable->setColumnStretchable(0, true);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  parameterTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  return true;
}

bool TaskWidget::loadMethodParameters()
{
  CCopasiTask* task =
    dynamic_cast<CCopasiTask *>(GlobalKeys.get(objKey));
  if (!task) return false;

  CCopasiMethod* method = task->getMethod();
  if (!method) return false;

  QTableItem * pItem;
  QString value;
  QString strname;

  parameterTable->setNumRows(method->size());
  QHeader *rowHeader = parameterTable->verticalHeader();

  unsigned C_INT32 i;
  CCopasiParameter::Type Type;
  for (i = 0; i < method->size(); i++)
    {
      strname = FROM_UTF8(method->getName(i));
      rowHeader->setLabel(i, strname);

      value = getParameterValue(method, i, &Type);
      pItem = new QTableItem (parameterTable, QTableItem::Always, value);
      parameterTable->setItem(i, 0, pItem);
    }
  return true;
}

bool TaskWidget::saveMethodParameters()
{
  CCopasiTask* task =
    dynamic_cast<CCopasiTask *>(GlobalKeys.get(objKey));
  if (!task) return false;

  CCopasiMethod* method = task->getMethod();
  if (!method) return false;

  unsigned C_INT32 i;
  QTableItem * pItem;
  QString value;

  for (i = 0; i < method->size(); i++)
    {
      pItem = parameterTable->item(i, 0);
      value = pItem->text();
      setParameterValue(method, i, value);
    }
  return true;
}

bool TaskWidget::addMethodParameterTableToLayout(unsigned int row, unsigned int maxcol)
{
  methodParLabel = new QLabel(this, "methodParLabel");
  methodParLabel->setText(tr("Method parameters"));
  methodParLabel->setAlignment(int(QLabel::AlignVCenter
                                   | QLabel::AlignRight));
  methodParLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
  TaskWidgetLayout->addWidget(methodParLabel, row, 0);

  if (!constructMethodParameterTable()) return false;
  TaskWidgetLayout->addMultiCellWidget(parameterTable, row, row + 1, 1, maxcol);

  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Preferred);
  TaskWidgetLayout->addItem(spacer, row + 1, 0);

  return true;
}

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

  CCopasiTask* task = dynamic_cast< CCopasiTask * >(GlobalKeys.get(objKey));
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
  CCopasiTask* task = dynamic_cast< CCopasiTask * >(GlobalKeys.get(objKey));
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
  if (!dynamic_cast< CCopasiTask * >(GlobalKeys.get(key))) return false;

  objKey = key;

  return loadTask();
}
