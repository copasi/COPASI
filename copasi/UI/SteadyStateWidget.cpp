/****************************************************************************
 ** Form implementation generated from reading ui file '.\SteadyStateWidget.ui'
 **
 ** Created: Sun Mar 2 13:39:33 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "SteadyStateWidget.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"

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

/*
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("SteadyStateWidget");
  resize(532, 527);
  setMinimumSize(QSize(0, 0));
  QFont f(font());
  f.setFamily("Times New Roman");
  f.setPointSize(9);
  setFont(f);
  setCaption(trUtf8("SteadyStateWidget"));
  SteadyStateWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "SteadyStateWidgetLayout");

  line7 = new QFrame(this, "line7");
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  line7->setFrameShape(QFrame::HLine);

  SteadyStateWidgetLayout->addMultiCellWidget(line7, 6, 6, 0, 6);
  QSpacerItem* spacer = new QSpacerItem(500, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addMultiCell(spacer, 7, 7, 0, 6);
  QSpacerItem* spacer_2 = new QSpacerItem(490, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addMultiCell(spacer_2, 5, 5, 0, 6);
  QSpacerItem* spacer_3 = new QSpacerItem(390, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addMultiCell(spacer_3, 3, 3, 0, 4);
  QSpacerItem* spacer_4 = new QSpacerItem(500, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addMultiCell(spacer_4, 1, 1, 0, 6);
  QSpacerItem* spacer_5 = new QSpacerItem(500, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addMultiCell(spacer_5, 11, 11, 0, 6);

  Layout6 = new QHBoxLayout(0, 0, 6, "Layout6");

  bRunButton = new QPushButton(this, "bRunButton");
  bRunButton->setText(trUtf8("Run"));
  Layout6->addWidget(bRunButton);
  bRunButton->setEnabled(false);

  commitChange = new QPushButton(this, "commitChange");
  commitChange->setText(trUtf8("Commit Change"));
  Layout6->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Cancel Change"));
  Layout6->addWidget(cancelChange);

  SteadyStateWidgetLayout->addMultiCellLayout(Layout6, 12, 12, 0, 6);
  QSpacerItem* spacer_6 = new QSpacerItem(490, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addMultiCell(spacer_6, 9, 9, 0, 6);

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);

  SteadyStateWidgetLayout->addMultiCellWidget(line6, 10, 10, 0, 6);

  line8 = new QFrame(this, "line8");
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  SteadyStateWidgetLayout->addMultiCellWidget(line8, 2, 2, 0, 6);

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));

  SteadyStateWidgetLayout->addWidget(taskNameLabel, 0, 0);

  taskJacobian = new QRadioButton(this, "taskJacobian");
  taskJacobian->setText(trUtf8("Jacobian"));

  SteadyStateWidgetLayout->addWidget(taskJacobian, 4, 1);

  taskDescriptionLabel = new QLabel(this, "taskDescriptionLabel");
  taskDescriptionLabel->setText(trUtf8("Task Description"));

  SteadyStateWidgetLayout->addWidget(taskDescriptionLabel, 4, 0);

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Parameter value"));

  SteadyStateWidgetLayout->addWidget(parameterValueLabel, 8, 0);
  QSpacerItem* spacer_7 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addItem(spacer_7, 4, 2);

  taskStability = new QRadioButton(this, "taskStability");
  taskStability->setText(trUtf8("Stability Analysis"));

  SteadyStateWidgetLayout->addMultiCellWidget(taskStability, 4, 4, 3, 5);
  QSpacerItem* spacer_8 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addItem(spacer_8, 4, 6);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("Task Executable"));

  SteadyStateWidgetLayout->addMultiCellWidget(bExecutable, 0, 0, 5, 6);

  taskName = new QLineEdit(this, "taskName");
  taskName->setFrameShape(QLineEdit::LineEditPanel);
  taskName->setFrameShadow(QLineEdit::Sunken);

  SteadyStateWidgetLayout->addMultiCellWidget(taskName, 0, 0, 1, 3);
  QSpacerItem* spacer_9 = new QSpacerItem(61, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  SteadyStateWidgetLayout->addItem(spacer_9, 0, 4);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));

  SteadyStateWidgetLayout->addMultiCellWidget(parameterTable, 8, 8, 1, 4);

  // signals and slots connections
  connect(bExecutable, SIGNAL(clicked()), this, SLOT(RunButtonClicked()));
  connect(bRunButton, SIGNAL(clicked()), this, SLOT(RunTask()));
  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));

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
        case CMethodParameter::DOUBLE:
          steadystatemethod->setValue((const char *)strname.utf8(),
                                      substrate.toDouble());
          break;
        case CMethodParameter::INT:
          steadystatemethod->setValue((const char *)strname.utf8(),
                                      (C_INT32) substrate.toInt());
          break;
        case CMethodParameter::UINT:
          steadystatemethod->setValue((const char *)strname.utf8(),
                                      (unsigned C_INT32) substrate.toUInt());
          break;
        case CMethodParameter::BOOL:;
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
  mSteadyStateTask->process();
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
