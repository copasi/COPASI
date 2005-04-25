/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/SteadyStateWidget.cpp,v $
   $Revision: 1.91 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:16:14 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 02/03 
Comment : SteadyStateWidget
Contact: Please contact lixu1@vt.edu.
 *********************************************************/
#include <qfiledialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>

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
#include "report/CReportDefinitionVector.h"
#include "report/CReport.h"
#include "report/CReportDefinition.h"
#include "CReportDefinitionSelect.h"
#include "CProgressBar.h"
#include "copasiui3window.h"
#include "qmessagebox.h"
#include "qapplication.h"

/**
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    pParent(parent)
{
  if (!name)
    setName("SteadyStateWidget");
  setCaption(trUtf8("SteadyStateWidget"));

  SteadyStateWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "SteadyStateWidgetLayout");

  //********** name ********************
  QHBoxLayout* tmpLayout = new QHBoxLayout();

  taskNameLabel = new QLabel(this, "taskNameLabel");
  //taskNameLabel->setText(trUtf8("Task Name"));
  taskNameLabel->setText(trUtf8("<h2>Steady state</h2>"));
  //taskNameLabel->setAlignment(int(QLabel::AlignVCenter
  //                                | QLabel::AlignRight));
  //SteadyStateWidgetLayout->addWidget(taskNameLabel, 0, 0);
  tmpLayout->addWidget(taskNameLabel);

  //taskName = new QLineEdit(this, "taskName");
  //taskName->setFrameShape(QLineEdit::LineEditPanel);
  //taskName->setFrameShadow(QLineEdit::Sunken);
  //SteadyStateWidgetLayout->addWidget(taskName, 0, 1);

  QSpacerItem* tmpSpacer = new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);
  tmpLayout->addItem(tmpSpacer);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("Task Executable"));
  // this is the child widget to edit an steadystatetask
  bExecutable->setChecked(parent == NULL);
  bExecutable->setEnabled(parent != NULL);
  //SteadyStateWidgetLayout->addWidget(bExecutable, 0, 2);
  tmpLayout->addWidget(bExecutable);

  SteadyStateWidgetLayout->addMultiCellLayout(tmpLayout, 0, 0, 1, 2);

  QSpacerItem* spacer2 = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);
  SteadyStateWidgetLayout->addItem(spacer2, 1, 1);

  //*************************

  setInitialState = new QCheckBox(this, "setInitialState");
  setInitialState->setText(trUtf8("Use result as new initial state"));
  setInitialState->setChecked(parent == NULL);
  setInitialState->setEnabled(parent != NULL);
  SteadyStateWidgetLayout->addWidget(setInitialState, 2, 1);

  taskJacobian = new QCheckBox(this, "taskJacobian");
  taskJacobian->setText(trUtf8("calculate Jacobian"));
  SteadyStateWidgetLayout->addWidget(taskJacobian, 3, 1);

  taskStability = new QCheckBox(this, "taskStability");
  taskStability->setText(trUtf8("perform Stability Analysis"));
  SteadyStateWidgetLayout->addWidget(taskStability, 3, 2);
  taskStability->setEnabled(false);

  line8_2 = new QFrame(this, "line8_2");
  line8_2->setFrameShape(QFrame::HLine);
  //line8_2->setFrameShadow(QFrame::Sunken);
  //line8_2->setFrameShape(QFrame::HLine);
  SteadyStateWidgetLayout->addMultiCellWidget(line8_2, 4, 4, 0, 2);

  //line8 = new QFrame(this, "line8");
  //line8->setFrameShape(QFrame::HLine);
  //line8->setFrameShadow(QFrame::Sunken);
  //line8->setFrameShape(QFrame::HLine);
  //SteadyStateWidgetLayout->addMultiCellWidget(line8, 1, 1, 0, 2);

  //************* parameter table ****************
  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Method parameters"));
  parameterValueLabel->setAlignment(int(QLabel::AlignVCenter
                                        | QLabel::AlignRight));
  SteadyStateWidgetLayout->addWidget(parameterValueLabel, 5, 0);
  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  SteadyStateWidgetLayout->addItem(spacer, 6, 0);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  parameterTable->setColumnStretchable(0, true);
  parameterTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  SteadyStateWidgetLayout->addMultiCellWidget(parameterTable, 5, 6, 1, 2);

  QSpacerItem* spacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  SteadyStateWidgetLayout->addMultiCell(spacer_3, 7, 7, 0, 2);

  //************ line ********************
  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  //line6->setFrameShape(QFrame::HLine);
  SteadyStateWidgetLayout->addMultiCellWidget(line6, 8, 8, 0, 2);

  //*************** buttons ********************
  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  bRunButton = new QPushButton(this, "bRunButton");
  if (parent == NULL)
    bRunButton->setText(trUtf8("OK"));
  else
    bRunButton->setText(trUtf8("Run"));
  bRunButton->setEnabled(true /*(parent == NULL)*/);
  Layout2->addWidget(bRunButton);

  //  commitChange = new QPushButton(this, "commitChange");
  //  commitChange->setText(trUtf8("Commit"));
  //  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Revert"));
  Layout2->addWidget(cancelChange);

  //ExportFileButton = new QPushButton(this, "ExportFileButton");
  //ExportFileButton->setText(trUtf8("Export To File"));
  //Layout2->addWidget(ExportFileButton);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("ReportDefinition"));
  Layout2->addWidget(reportDefinitionButton);

  SteadyStateWidgetLayout->addMultiCellLayout(Layout2, 9, 9, 0, 2);

  //*********************
  //taskDescriptionLabel = new QLabel(this, "taskDescriptionLabel");
  //taskDescriptionLabel->setText(trUtf8(""));
  //SteadyStateWidgetLayout->addWidget(taskDescriptionLabel, 2, 0);

  // signals and slots connections
  connect(bRunButton, SIGNAL(clicked()), this, SLOT(runSteadyStateTask()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelButtonClicked()));
  //connect(ExportFileButton, SIGNAL(clicked()), this, SLOT(ExportToFileButtonClicked()));
  //connect(bExecutable, SIGNAL(clicked()), this, SLOT(RunButtonChecked()));
  //  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitButtonClicked()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));
  connect(taskJacobian, SIGNAL(toggled(bool)), this, SLOT(taskJacobianToggled()));

  // tab order
  //setTabOrder(taskName, bExecutable);
  setTabOrder(bExecutable, setInitialState);
  setTabOrder(setInitialState, taskJacobian);
  setTabOrder(taskJacobian, taskStability);
  setTabOrder(taskStability, parameterTable);
  setTabOrder(parameterTable, bRunButton);
  setTabOrder(bRunButton, cancelChange);
  //setTabOrder(cancelChange, ExportFileButton);
  //setTabOrder(ExportFileButton, reportDefinitionButton);

  //  mSteadyStateTask = NULL;
  reportDefinitionButton->setEnabled(false);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{
  //I believe this should not be done in this place. Sven
  /*CSteadyStateTask* mSteadyStateTask =
    dynamic_cast< CSteadyStateTask * >(GlobalKeys.get(objKey));
  pdelete(mSteadyStateTask);*/
}

void SteadyStateWidget::CancelButtonClicked()
{
  loadSteadyStateTask();
}

void SteadyStateWidget::CommitButtonClicked()
{
  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(objKey));
  assert(mSteadyStateTask);

  bool bScheduled = bExecutable->isChecked();
  mSteadyStateTask->setScheduled(bScheduled);

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());
  assert(steadystateproblem);

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());
  assert(steadystatemethod);

  CCopasiDataModel::Global->getModel()->compileIfNecessary();
  steadystateproblem->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

  bool bJacobian = taskJacobian->isChecked();
  bool bStatistics = taskStability->isChecked();

  steadystateproblem->setJacobianRequested(bJacobian);
  steadystateproblem->setStabilityAnalysisRequested(bStatistics);

  QTableItem * pItem;
  QString value;
  QString strname;

  unsigned C_INT32 i;

  for (i = 0; i < steadystatemethod->size(); i++)
    {
      pItem = parameterTable->item(i, 0);
      value = pItem->text();
      setParameterValue(steadystatemethod, i, value);
    }
  loadSteadyStateTask();
}

/*void SteadyStateWidget::RunButtonChecked()
{
  if (!dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(objKey)))
    return;
 
  if (!bExecutable->isChecked())
    bRunButton->setEnabled(false);
  else
    bRunButton->setEnabled(true);
}*/

void SteadyStateWidget::parameterValueChanged()
{
  qWarning("SteadyStateWidget::parameterValueChanged(): Not implemented yet!");
}

void SteadyStateWidget::runSteadyStateTask()
{
  if (CCopasiDataModel::Global->isChanged())
    {
      const QApplication* qApp = dataModel->getQApp();
      if (qApp)
        {
          CopasiUI3Window* mainWidget = dynamic_cast<CopasiUI3Window*>(qApp->mainWidget());
          if (mainWidget)
            {
              if (QMessageBox::question(mainWidget, "Model Changed", "Your model contains unsaved changes.\nDo you want to save those changes?", QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape) == QMessageBox::Yes)
                {
                  mainWidget->saveFile();
                }
            }
        }
    }
  CommitButtonClicked();

  if (bRunButton->text() != "Run")
    {
      hide();
      return;
    }

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(objKey));
  assert(mSteadyStateTask);

  mSteadyStateTask->initialize();

  setCursor(Qt::WaitCursor);
  CProgressBar * tmpBar = new CProgressBar();
  mSteadyStateTask->setProgressHandler(tmpBar);
  tmpBar->show();

  try
    {
      if (!mSteadyStateTask->process())
        {
          tmpBar->finish();
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
            {
              tmpBar->finish();
              QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
              CCopasiMessage::clearDeque();
            }
        }
      else if (setInitialState->isChecked())
        {
          const CState *currentState = mSteadyStateTask->getState();
          if (currentState)
            (CCopasiDataModel::Global->getModel())->setInitialState(currentState);
        }
    }

  catch (CCopasiException Exception)
    {
      tmpBar->finish();
      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          tmpBar->finish();
          QMessageBox::warning(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  tmpBar->finish(); pdelete(tmpBar);

  protectedNotify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());

  unsetCursor();

  pListView->switchToOtherWidget(211, ""); //change to the results window
}

void SteadyStateWidget::loadSteadyStateTask()
{
  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(objKey));
  assert(mSteadyStateTask);

  bExecutable->setChecked(mSteadyStateTask->isScheduled());

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());
  assert(steadystateproblem);

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());
  assert(steadystatemethod);

  //taskName->setText(tr("Steady State Task"));
  //taskName->setEnabled(false);

  bool bJacobian = steadystateproblem->isJacobianRequested();
  bool bStatistics = steadystateproblem->isStabilityAnalysisRequested();
  taskJacobian->setChecked(bJacobian);
  if (bJacobian)
    {
      taskStability->setEnabled(true);
      taskStability->setChecked(bStatistics);
    }

  QTableItem * pItem;
  QString value;
  QString strname;

  parameterTable->setNumRows(steadystatemethod->size());
  QHeader *rowHeader = parameterTable->verticalHeader();

  unsigned C_INT32 i;
  CCopasiParameter::Type Type;
  for (i = 0; i < steadystatemethod->size(); i++)
    {
      strname = FROM_UTF8(steadystatemethod->getName(i));
      rowHeader->setLabel(i, tr(strname));

      value = getParameterValue(steadystatemethod, i, &Type);
      pItem = new QTableItem (parameterTable, QTableItem::Always, value);
      parameterTable->setItem(i, 0, pItem);
    }

  /*if (!bExecutable->isChecked())
    bRunButton->setEnabled(false);
  else
    bRunButton->setEnabled(true);*/
}

//void SteadyStateWidget::ExportToFileButtonClicked()
//{}

bool SteadyStateWidget::enter(const std::string & key)
{
  if (!dynamic_cast<CSteadyStateTask *>(GlobalKeys.get(key))) return false;

  objKey = key;

  loadSteadyStateTask();;

  return true;
}

bool SteadyStateWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action),
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
}

bool SteadyStateWidget::leave()
{
  CommitButtonClicked();
  return true;
}

void SteadyStateWidget::ReportDefinitionClicked()
{
  CSteadyStateTask* steadystateTask =
    dynamic_cast< CSteadyStateTask * >(GlobalKeys.get(objKey));
  assert(steadystateTask);

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(pParent);
  pSelectDlg->setReport(&steadystateTask->getReport());
  pSelectDlg->loadReportDefinitionVector();
  pSelectDlg->exec();

  delete pSelectDlg;
}

void SteadyStateWidget::taskJacobianToggled()
{
  if (!taskJacobian->isChecked())
    {
      taskStability->setChecked(false);
      taskStability->setEnabled(false);
    }
  else taskStability->setEnabled(true);
}
