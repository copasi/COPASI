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

#include "SteadyStateWidget.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "model/CModel.h"
#include "listviews.h"
#include "utilities/CCopasiException.h"

/*
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
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
  bRunButton->setText(trUtf8("Run"));
  bRunButton->setEnabled(false);
  Layout2->addWidget(bRunButton);

  commitChange = new QPushButton(this, "commitChange");
  commitChange->setText(trUtf8("Commit"));
  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Cancel"));
  Layout2->addWidget(cancelChange);

  ExportFileButton = new QPushButton(this, "ExportFileButton");
  ExportFileButton->setText(trUtf8("Export To File"));
  Layout2->addWidget(ExportFileButton);

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
  connect(bExecutable, SIGNAL(clicked()), this, SLOT(RunButtonClicked()));
  connect(bRunButton, SIGNAL(clicked()), this, SLOT(RunTask()));
  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(ExportFileButton, SIGNAL(clicked()), this, SLOT(ExportToFile()));
  connect(this, SIGNAL(runFinished(CModel*)), (ListViews*)parent,
          SLOT(loadModelNodes(CModel*)));

  // tab order
  setTabOrder(taskName, bExecutable);
  setTabOrder(bExecutable, taskJacobian);
  setTabOrder(taskJacobian, taskStability);
  setTabOrder(taskStability, parameterTable);
  setTabOrder(parameterTable, bRunButton);
  setTabOrder(bRunButton, commitChange);
  setTabOrder(commitChange, cancelChange);

  mSteadyStateTask = NULL;
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void SteadyStateWidget::CancelChange()
{
  if (mSteadyStateTask == NULL)
    return;
  loadSteadyStateTask(mSteadyStateTask);
}

void SteadyStateWidget::CommitChange()
{
  if (mSteadyStateTask == NULL)
    return;
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
  loadSteadyStateTask(mSteadyStateTask);
}

void SteadyStateWidget::RunButtonClicked()
{
  if (mSteadyStateTask == NULL)
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

void SteadyStateWidget::RunTask()
{
  if (mSteadyStateTask == NULL)
    return;

  mSteadyStateTask->getProblem()->getModel()->compile();
  mSteadyStateTask->getProblem()->
  setInitialState(mSteadyStateTask->getProblem()->getModel()->getInitialState());

  std::ofstream output("steadystate.txt");
  mSteadyStateTask->initializeReporting(output);

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
  emit runFinished(mSteadyStateTask->getProblem()->getModel());

  unsetCursor();
}

void SteadyStateWidget::loadSteadyStateTask(CSteadyStateTask *steadystatetask)
{
  if (steadystatetask == NULL)
    return;
  mSteadyStateTask = steadystatetask;
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

void SteadyStateWidget::ExportToFile()
{
  if (!mSteadyStateTask) return;
  QString textFile = QFileDialog::getSaveFileName(
                       QString::null, "TEXT Files (*.txt)",
                       this, "save file dialog",
                       "Choose a file");

  if (mSteadyStateTask && textFile)
    {
      textFile += ".txt";
      CWriteConfig outbuf((const char *)textFile.utf8());
      mSteadyStateTask->save(outbuf);
    }
}
