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

#include "DataModel.h"

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

/*
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

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));

  SteadyStateWidgetLayout->addWidget(taskNameLabel, 0, 0);
  QSpacerItem* spacer = new QSpacerItem(91, 400, QSizePolicy::Minimum, QSizePolicy::Expanding);
  SteadyStateWidgetLayout->addItem(spacer, 5, 0);

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Parameter value"));

  SteadyStateWidgetLayout->addWidget(parameterValueLabel, 4, 0);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  bRunButton = new QPushButton(this, "bRunButton");

  if (parent == NULL)
    bRunButton->setText(trUtf8("OK"));
  else
    bRunButton->setText(trUtf8("Run"));

  //  bRunButton->setText(trUtf8("Run"));
  bRunButton->setEnabled((parent == NULL));
  Layout2->addWidget(bRunButton);

  //  commitChange = new QPushButton(this, "commitChange");
  //  commitChange->setText(trUtf8("Commit"));
  //  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Cancel"));
  Layout2->addWidget(cancelChange);

  ExportFileButton = new QPushButton(this, "ExportFileButton");
  ExportFileButton->setText(trUtf8("Export To File"));
  Layout2->addWidget(ExportFileButton);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("ReportDefinition"));
  Layout2->addWidget(reportDefinitionButton);

  SteadyStateWidgetLayout->addMultiCellLayout(Layout2, 7, 7, 0, 2);

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);

  SteadyStateWidgetLayout->addMultiCellWidget(line6, 6, 6, 0, 2);

  taskName = new QLineEdit(this, "taskName");
  taskName->setFrameShape(QLineEdit::LineEditPanel);
  taskName->setFrameShadow(QLineEdit::Sunken);

  SteadyStateWidgetLayout->addWidget(taskName, 0, 1);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("Task Executable"));

  // this is the child widget to edit an steadystatetask
  bExecutable->setChecked(parent == NULL);
  bExecutable->setEnabled(parent != NULL);

  SteadyStateWidgetLayout->addWidget(bExecutable, 0, 2);

  line8 = new QFrame(this, "line8");
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  SteadyStateWidgetLayout->addMultiCellWidget(line8, 1, 1, 0, 2);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));

  SteadyStateWidgetLayout->addMultiCellWidget(parameterTable, 4, 5, 1, 2);

  taskStability = new QRadioButton(this, "taskStability");
  taskStability->setText(trUtf8("Stability Analysis"));

  SteadyStateWidgetLayout->addWidget(taskStability, 2, 2);

  taskDescriptionLabel = new QLabel(this, "taskDescriptionLabel");
  taskDescriptionLabel->setText(trUtf8("Task Description"));

  SteadyStateWidgetLayout->addWidget(taskDescriptionLabel, 2, 0);

  taskJacobian = new QRadioButton(this, "taskJacobian");
  taskJacobian->setText(trUtf8("Jacobian"));

  SteadyStateWidgetLayout->addWidget(taskJacobian, 2, 1);

  line8_2 = new QFrame(this, "line8_2");
  line8_2->setFrameShape(QFrame::HLine);
  line8_2->setFrameShadow(QFrame::Sunken);
  line8_2->setFrameShape(QFrame::HLine);

  SteadyStateWidgetLayout->addMultiCellWidget(line8_2, 3, 3, 0, 2);

  // signals and slots connections
  connect(bRunButton, SIGNAL(clicked()), this, SLOT(RunButtonClicked()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelButtonClicked()));
  connect(ExportFileButton, SIGNAL(clicked()), this, SLOT(ExportToFileButtonClicked()));
  connect(bExecutable, SIGNAL(clicked()), this, SLOT(RunButtonChecked()));
  //  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitButtonClicked()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  //connect(this, SIGNAL(runFinished(CModel*)), (ListViews*)parent,
  //        SLOT(loadModelNodes(CModel*)));

  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));

  // tab order
  setTabOrder(taskName, bExecutable);
  setTabOrder(bExecutable, taskJacobian);
  setTabOrder(taskJacobian, taskStability);
  setTabOrder(taskStability, parameterTable);
  setTabOrder(parameterTable, bRunButton);
  setTabOrder(bRunButton, cancelChange);
  setTabOrder(cancelChange, ExportFileButton);
  setTabOrder(ExportFileButton, reportDefinitionButton);

  //  mSteadyStateTask = NULL;
  reportDefinitionButton->setEnabled(false);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{
  // no need to delete child widgets, Qt does it all for us
  if (!CKeyFactory::get(objKey)) return;
  CSteadyStateTask* mSteadyStateTask = (CSteadyStateTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  pdelete(mSteadyStateTask);
}

void SteadyStateWidget::CancelButtonClicked()
{
  loadSteadyStateTask();
}

void SteadyStateWidget::CommitButtonClicked()
{
  if (!CKeyFactory::get(objKey))
    return;

  CSteadyStateTask* mSteadyStateTask = (CSteadyStateTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  CSteadyStateProblem * steadystateproblem = mSteadyStateTask->getProblem();
  CSteadyStateMethod* steadystatemethod = mSteadyStateTask->getMethod();

  bool bJacobian = taskJacobian->isChecked ();
  bool bStatistics = taskStability->isChecked ();

  steadystateproblem->setJacobianRequested(bJacobian);
  steadystateproblem->setStabilityAnalysisRequested(bStatistics);

  QTableItem * pItem;
  QString substrate;
  QString strname;
  unsigned C_INT32 i;
  for (i = 0; i < steadystatemethod->size(); i++)
    {
      pItem = parameterTable->item(i, 0);
      substrate = pItem->text();
      strname = (steadystatemethod->getName(i)).c_str();
      switch (steadystatemethod->getType((const char *)strname.utf8()))
        {
        case CParameter::DOUBLE:
          steadystatemethod->setValue((const char *)strname.utf8(),
                                      substrate.toDouble());
          break;
        case CParameter::INT:
          steadystatemethod->setValue((const char *)strname.utf8(),
                                      (C_INT32) substrate.toInt());
          break;
        case CParameter::UINT:
          steadystatemethod->setValue((const char *)strname.utf8(),
                                      (unsigned C_INT32) substrate.toUInt());
          break;
        case CParameter::BOOL:;
          steadystatemethod->setValue((const char *)strname.utf8(),
                                      (bool) substrate.toUShort());
          break;
        }
    }
  loadSteadyStateTask();
}

void SteadyStateWidget::RunButtonChecked()
{
  if (!CKeyFactory::get(objKey))
    return;

  if (!bExecutable->isChecked())
    bRunButton->setEnabled(false);
  else
    bRunButton->setEnabled(true);
}

void SteadyStateWidget::parameterValueChanged()
{
  qWarning("SteadyStateWidget::parameterValueChanged(): Not implemented yet!");
}

void SteadyStateWidget::RunButtonClicked()
{
  if (!CKeyFactory::get(objKey))
    return;

  CommitButtonClicked();

  if (bRunButton->text() != "Run")
    {
      hide();
      return;
    }

  CSteadyStateTask* mSteadyStateTask = (CSteadyStateTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  mSteadyStateTask->getProblem()->getModel()->compile();
  mSteadyStateTask->getProblem()->
  setInitialState(mSteadyStateTask->getProblem()->getModel()->getInitialState());

  //  std::ofstream output("steadystate.txt");
  //  mSteadyStateTask->initializeReporting(output);

  if (mSteadyStateTask->getReport()->getTarget() != "")
    {
      std::ofstream output(mSteadyStateTask->getReport()->getTarget().c_str());
      mSteadyStateTask->initializeReporting(output);
    }

  setCursor(Qt::WaitCursor);

  try
    {
      mSteadyStateTask->process();
    }

  catch (CCopasiException Exception)
    {
      QMessageBox mb("Copasi",
                     "Could not find a Steady State",
                     QMessageBox::NoIcon,
                     QMessageBox::Ok | QMessageBox::Escape,
                     QMessageBox::NoButton,
                     QMessageBox::NoButton);
      mb.exec();
    }
  //  emit runFinished(mSteadyStateTask->getProblem()->getModel());
  ((ListViews*)pParent)->notify(ListViews::STATE, ListViews::CHANGE, dataModel->getModel()->getKey());

  unsetCursor();
}

//void SteadyStateWidget::setModel(CModel* newModel)
//{
//  if (!CKeyFactory::get(objKey)) return;
//  CSteadyStateTask* mSteadyStateTask = (CSteadyStateTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
//  CSteadyStateProblem * steadystateproblem = mSteadyStateTask->getProblem();
//  steadystateproblem->setModel(newModel);
//}

void SteadyStateWidget::loadSteadyStateTask()
{
  //  if (steadystatetask == NULL)
  //   return;
  CSteadyStateTask* steadystatetask = (CSteadyStateTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  CSteadyStateProblem * steadystateproblem = steadystatetask->getProblem();
  CSteadyStateMethod* steadystatemethod = steadystatetask->getMethod();

  taskName->setText(tr("Steady State Task"));
  taskName->setEnabled(false);

  bool bJacobian = steadystateproblem->isJacobianRequested();
  bool bStatistics = steadystateproblem->isStabilityAnalysisRequested();
  taskJacobian->setChecked(bJacobian);
  taskStability->setChecked(bStatistics);

  QTableItem * pItem;
  QString substrate;
  QString strname;

  parameterTable->setNumRows(steadystatemethod->size());
  QHeader *rowHeader = parameterTable->verticalHeader();

  int i;
  for (i = 0; i < steadystatemethod->size(); i++)
    {
      strname = (steadystatemethod->getName(i)).c_str();
      rowHeader->setLabel(i, tr(strname));
    }

  for (i = 0; i < steadystatemethod->size(); i++)
    {
      strname = (steadystatemethod->getName(i)).c_str();
      substrate = QString::number(steadystatemethod->getValue((const char *)strname.utf8()));
      pItem = new QTableItem (parameterTable, QTableItem::Always, substrate);
      parameterTable->setItem(i, 0, pItem);
    }

  if (!bExecutable->isChecked())
    bRunButton->setEnabled(false);
  else
    bRunButton->setEnabled(true);
}

void SteadyStateWidget::ExportToFileButtonClicked()
{
  if (!CKeyFactory::get(objKey)) return;
  QString textFile = QFileDialog::getSaveFileName(
                       QString::null, "TEXT Files (*.txt)",
                       this, "save file dialog",
                       "Choose a file");

  if (textFile)
    {
      textFile += ".txt";
      CWriteConfig outbuf((const char *)textFile.utf8());
      CSteadyStateTask* mSteadyStateTask = (CSteadyStateTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
      mSteadyStateTask->save(outbuf);
    }
}

bool SteadyStateWidget::enter(const std::string & key)
{
  if (!CKeyFactory::get(key)) return false;

  objKey = key;

  loadSteadyStateTask();;

  return true;
}

bool SteadyStateWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::FUNCTION:
      break;
    case ListViews::MODEL:
      CReportDefinitionVector* pReportDefinitionVector;
      pReportDefinitionVector = dataModel->getReportDefinitionVectorAddr();
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
  //let the user confirm?
  return true;
}

void SteadyStateWidget::ReportDefinitionClicked()
{
  CReportDefinitionSelect* pSelectDlg = new CReportDefinitionSelect(pParent);
  CSteadyStateTask* steadystateTask = (CSteadyStateTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  pSelectDlg->setReport(steadystateTask->getReport());
  pSelectDlg->loadReportDefinitionVector();
  if (pSelectDlg->exec () == QDialog::Rejected)
    {
      return;
    }
}
