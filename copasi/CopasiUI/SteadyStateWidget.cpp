/****************************************************************************
<<<<<<< SteadyStateWidget.cpp
 ** Form implementation generated from reading ui file '.\SteadyStateWidget.ui'
 **
 ** Created: Thu Feb 13 12:57:19 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

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

SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("SteadyStateWidget");
  resize(655, 639);
  setCaption(trUtf8("SteadyStateWidget"));

  line8 = new QFrame(this, "line8");
  line8->setGeometry(QRect(11, 71, 568, 16));
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  line7 = new QFrame(this, "line7");
  line7->setGeometry(QRect(11, 162, 568, 16));
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  line7->setFrameShape(QFrame::HLine);

  taskDescriptionLabel = new QLabel(this, "taskDescriptionLabel");
  taskDescriptionLabel->setGeometry(QRect(10, 108, 90, 20));
  taskDescriptionLabel->setText(trUtf8("Task Description"));

  taskJacobian = new QRadioButton(this, "taskJacobian");
  taskJacobian->setGeometry(QRect(105, 109, 186, 18));
  taskJacobian->setText(trUtf8("Jacobian"));

  taskStability = new QRadioButton(this, "taskStability");
  taskStability->setGeometry(QRect(297, 109, 185, 18));
  taskStability->setText(trUtf8("Stability Analysis"));

  line6 = new QFrame(this, "line6");
  line6->setGeometry(QRect(11, 398, 578, 16));
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setGeometry(QRect(12, 15, 90, 19));
  taskNameLabel->setText(trUtf8("Task Name"));

  QWidget* privateLayoutWidget = new QWidget(this, "Layout5");
  privateLayoutWidget->setGeometry(QRect(10, 440, 570, 25));
  Layout5 = new QHBoxLayout(privateLayoutWidget, 0, 6, "Layout5");

  bRunButton = new QPushButton(privateLayoutWidget, "bRunButton");
  bRunButton->setText(trUtf8("Run"));
  Layout5->addWidget(bRunButton);

  commitChange = new QPushButton(privateLayoutWidget, "commitChange");
  commitChange->setText(trUtf8("Commit Change"));
  Layout5->addWidget(commitChange);

  cancelChange = new QPushButton(privateLayoutWidget, "cancelChange");
  cancelChange->setText(trUtf8("Cancel Change"));
  Layout5->addWidget(cancelChange);

  taskName = new QLineEdit(this, "taskName");
  taskName->setGeometry(QRect(102, 15, 240, 20));

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setGeometry(QRect(14, 205, 80, 160));
  parameterValueLabel->setText(trUtf8("Parameter value"));

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setGeometry(QRect(100, 205, 484, 160));
  QHeader *rowHeader = parameterTable->verticalHeader();
  parameterTable->setNumRows(10);
  parameterTable->setNumCols(1);
  rowHeader->setLabel(0, tr("UseNewton:mUseNewton"));
  rowHeader->setLabel(1, tr("UseIntegration:mUseIntegration"));
  rowHeader->setLabel(2, tr("UseBackIntegration:mUseBackIntegration"));
  rowHeader->setLabel(3, tr("IterationLimit:mIterationLimit"));
  rowHeader->setLabel(4, tr("DerivationFactor:mFactor"));
  rowHeader->setLabel(5, tr("Resolution:mResolution:"));
  rowHeader->setLabel(6, tr("LSODA.RelativeTolerance:"));
  rowHeader->setLabel(7, tr("LSODA.AbsoluteTolerance:"));
  rowHeader->setLabel(8, tr("LSODA.AdamsMaxOrder:"));
  rowHeader->setLabel(9, tr("LSODA.BDFMaxOrder:"));
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setGeometry(QRect(399, 15, 141, 21));
  bExecutable->setText(trUtf8("Task Executable"));

  // signals and slots connections
  connect(taskName, SIGNAL(textChanged(const QString&)), this, SLOT(taskNameChanged()));
  connect(taskJacobian, SIGNAL(stateChanged(int)), this, SLOT(methodJacob()));
  connect(taskStability, SIGNAL(stateChanged(int)), this, SLOT(methodStability()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));
  connect(bRunButton, SIGNAL(clicked()), this, SLOT(RunTask()));
  connect(bExecutable, SIGNAL(clicked()), this, SLOT(RunButtonClicked()));

  // tab order
  setTabOrder(bExecutable, taskJacobian);
  setTabOrder(taskJacobian, taskStability);
  setTabOrder(taskStability, parameterTable);
  setTabOrder(parameterTable, taskName);
  setTabOrder(taskName, bRunButton);
  setTabOrder(bRunButton, commitChange);
  setTabOrder(commitChange, cancelChange);
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
  qWarning("SteadyStateWidget::CommitChange(): Not implemented yet!");
}

void SteadyStateWidget::methodJacob()
{
  qWarning("SteadyStateWidget::methodJacob(): Not implemented yet!");
}

void SteadyStateWidget::methodStability()
{
  qWarning("SteadyStateWidget::methodStability(): Not implemented yet!");
}

void SteadyStateWidget::RunButtonClicked()
{
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
  qWarning("SteadyStateWidget::RunTask(): Not implemented yet!");
}

void SteadyStateWidget::taskNameChanged()
{
  qWarning("SteadyStateWidget::taskNameChanged(): Not implemented yet!");
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

  QString substrates1;
  substrates1 = QString::number(steadystatemethod->getValue("Newton.UseNewton"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates1);
  parameterTable->setItem(0, 0, pItem);

  QString substrates2;
  substrates2 = QString::number(steadystatemethod->getValue("Newton.UseIntegration"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates2);
  parameterTable->setItem(1, 0, pItem);

  QString substrates3;
  substrates3 = QString::number(steadystatemethod->getValue("Newton.UseBackIntegration"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates3);
  parameterTable->setItem(2, 0, pItem);

  QString substrates4;;
  substrates4 = QString::number(steadystatemethod->getValue("Newton.IterationLimit"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates4);
  parameterTable->setItem(3, 0, pItem);

  QString substrates5;
  substrates5 = QString::number(steadystatemethod->getValue("Newton.DerivationFactor"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates5);
  parameterTable->setItem(4, 0, pItem);

  QString substrates6;
  substrates6 = QString::number(steadystatemethod->getValue("Newton.Resolution"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates6);
  parameterTable->setItem(5, 0, pItem);

  QString substrates7;
  substrates7 = QString::number(steadystatemethod->getValue("Newton.LSODA.RelativeTolerance"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates7);
  parameterTable->setItem(6, 0, pItem);

  QString substrates8;
  substrates8 = QString::number(steadystatemethod->getValue("Newton.LSODA.AbsoluteTolerance"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates8);
  parameterTable->setItem(7, 0, pItem);

  QString substrates9;
  substrates9 = QString::number(steadystatemethod->getValue("Newton.LSODA.AdamsMaxOrder"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates9);
  parameterTable->setItem(8, 0, pItem);

  QString substrates10;
  substrates10 = QString::number(steadystatemethod->getValue("Newton.LSODA.BDFMaxOrder"));
  pItem = new QTableItem (parameterTable, QTableItem::Always, substrates10);
  parameterTable->setItem(9, 0, pItem);

  if (!bExecutable->isChecked())
    bRunButton->setEnabled(false);
  else
    bRunButton->setEnabled(true);
}
