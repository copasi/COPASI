/****************************************************************************
 ** Form implementation generated from reading ui file '.\SteadyStateWidget.ui'
 **
 ** Created: Tue Feb 4 16:45:46 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "SteadyStateWidget.h"

#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qsplitter.h>
#include <qtable.h>
#include <qlayout.h>

/*
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("SteadyStateWidget");
  resize(655, 639);
  setCaption(trUtf8("SteadyStateWidget"));

  QWidget* privateLayoutWidget = new QWidget(this, "layout15");
  privateLayoutWidget->setGeometry(QRect(10, 379, 580, 88));
  layout15 = new QVBoxLayout(privateLayoutWidget, 0, 6, "layout15");
  QSpacerItem* spacer = new QSpacerItem(628, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout15->addItem(spacer);

  line6 = new QFrame(privateLayoutWidget, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);
  layout15->addWidget(line6);
  QSpacerItem* spacer_2 = new QSpacerItem(628, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout15->addItem(spacer_2);

  splitter3 = new QSplitter(privateLayoutWidget, "splitter3");
  splitter3->setOrientation(QSplitter::Horizontal);

  commitChange = new QPushButton(splitter3, "commitChange");
  commitChange->setText(trUtf8("Commit Change"));

  cancelChange = new QPushButton(splitter3, "cancelChange");
  cancelChange->setText(trUtf8("Cancel Change"));
  layout15->addWidget(splitter3);

  splitter11 = new QSplitter(this, "splitter11");
  splitter11->setGeometry(QRect(14, 205, 570, 160));
  splitter11->setOrientation(QSplitter::Horizontal);

  parameterValueLabel = new QLabel(splitter11, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Parameter value"));

  parameterTable = new QTable(splitter11, "parameterTable");
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

  QWidget* privateLayoutWidget_2 = new QWidget(this, "layout14");
  privateLayoutWidget_2->setGeometry(QRect(10, 70, 570, 122));
  layout14 = new QVBoxLayout(privateLayoutWidget_2, 0, 6, "layout14");

  line8 = new QFrame(privateLayoutWidget_2, "line8");
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);
  layout14->addWidget(line8);
  QSpacerItem* spacer_3 = new QSpacerItem(628, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout14->addItem(spacer_3);

  splitter12 = new QSplitter(privateLayoutWidget_2, "splitter12");
  splitter12->setOrientation(QSplitter::Horizontal);

  taskDescriptionLabel = new QLabel(splitter12, "taskDescriptionLabel");
  taskDescriptionLabel->setText(trUtf8("Task Description"));

  QWidget* privateLayoutWidget_3 = new QWidget(splitter12, "Layout2");
  Layout2 = new QHBoxLayout(privateLayoutWidget_3, 0, 6, "Layout2");

  taskJacobian = new QRadioButton(privateLayoutWidget_3, "taskJacobian");
  taskJacobian->setText(trUtf8("Jacobian"));
  Layout2->addWidget(taskJacobian);

  taskStability = new QRadioButton(privateLayoutWidget_3, "taskStability");
  taskStability->setText(trUtf8("Stability Analysis"));
  Layout2->addWidget(taskStability);
  layout14->addWidget(splitter12);
  QSpacerItem* spacer_4 = new QSpacerItem(628, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout14->addItem(spacer_4);

  line7 = new QFrame(privateLayoutWidget_2, "line7");
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  line7->setFrameShape(QFrame::HLine);
  layout14->addWidget(line7);
  QSpacerItem* spacer_5 = new QSpacerItem(628, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout14->addItem(spacer_5);

  splitter7 = new QSplitter(this, "splitter7");
  splitter7->setGeometry(QRect(12, 19, 570, 19));
  splitter7->setOrientation(QSplitter::Horizontal);

  taskNameLabel = new QLabel(splitter7, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));

  taskName = new QLineEdit(splitter7, "taskName");

  // signals and slots connections
  connect(taskName, SIGNAL(textChanged(const QString&)), this, SLOT(taskNameChanged()));
  connect(taskJacobian, SIGNAL(stateChanged(int)), this, SLOT(methodJacob()));
  connect(taskStability, SIGNAL(stateChanged(int)), this, SLOT(methodStability()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));

  // tab order
  setTabOrder(taskStability, taskName);
  setTabOrder(taskName, parameterTable);
  setTabOrder(parameterTable, commitChange);
  setTabOrder(commitChange, cancelChange);
  setTabOrder(cancelChange, taskJacobian);
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void SteadyStateWidget::taskNameChanged()
{
  qWarning("SteadyStateWidget::taskNameChanged(): Not implemented yet!");
}

void SteadyStateWidget::methodJacob()
{
  qWarning("SteadyStateWidget::methodJacob(): Not implemented yet!");
}

void SteadyStateWidget::methodStability()
{
  qWarning("SteadyStateWidget::methodStability(): Not implemented yet!");
}

void SteadyStateWidget::parameterValueChanged()
{
  qWarning("SteadyStateWidget::parameterValueChanged(): Not implemented yet!");
}

void SteadyStateWidget::CommitChange()
{
  if (mSteadyStateTask == NULL)
    return;
  CSteadyStateProblem * steadystateproblem = mSteadyStateTask->getProblem();
  CSteadyStateMethod* steadystatemethod = mSteadyStateTask->getMethod();

  taskName->setText(tr("Steady State Task"));
  taskName->setEnabled(false);

  bool bJacobian = taskJacobian->isChecked();
  steadystateproblem->setJacobianRequested(bJacobian);
  bool bStatistics = taskStability->isChecked();
  steadystateproblem->setStabilityAnalysisRequested(bStatistics);

  QTableItem * pItem;

  pItem = (QTableItem *)parameterTable->item(0, 0);
  steadystatemethod->setValue("Newton.UseNewton", (bool) pItem->text().toInt());

  pItem = (QTableItem *)parameterTable->item(1, 0);
  steadystatemethod->setValue("Newton.UseIntegration", (bool) pItem->text().toInt());

  pItem = (QTableItem *)parameterTable->item(2, 0);
  steadystatemethod->setValue("Newton.UseBackIntegration", (bool) pItem->text().toInt());

  pItem = (QTableItem *)parameterTable->item(3, 0);
  steadystatemethod->setValue("Newton.IterationLimit", (unsigned C_INT32) pItem->text().toInt());

  pItem = (QTableItem *)parameterTable->item(4, 0);
  steadystatemethod->setValue("Newton.DerivationFactor", pItem->text().toDouble());

  pItem = (QTableItem *)parameterTable->item(5, 0);
  steadystatemethod->setValue("Newton.Resolution", pItem->text().toDouble());

  pItem = (QTableItem *)parameterTable->item(6, 0);
  steadystatemethod->setValue("Newton.LSODA.RelativeTolerance", pItem->text().toDouble());

  pItem = (QTableItem *)parameterTable->item(7, 0);
  steadystatemethod->setValue("Newton.LSODA.AbsoluteTolerance", pItem->text().toDouble());

  pItem = (QTableItem *)parameterTable->item(8, 0);
  steadystatemethod->setValue("Newton.LSODA.AdamsMaxOrder", (unsigned C_INT32) pItem->text().toInt());

  pItem = (QTableItem *)parameterTable->item(9, 0);
  steadystatemethod->setValue("Newton.LSODA.BDFMaxOrder", (unsigned C_INT32) pItem->text().toInt());

  /*
    CWriteConfig outbuf(mSteadyStateTask->getFileName());
    mSteadyStateTask->save(outbuf);
   
    CReadConfig inbuf(mSteadyStateTask->getFileName());
    mSteadyStateTask->load(inbuf,mSteadyStateTask->getFileName());
  */

  QString name = "gps//CSteadyStateTask";
  std::string filename = ((std::string) name.latin1()) + ".gps";
  CWriteConfig *Rtn = new CWriteConfig(filename);
  mSteadyStateTask->save(*Rtn);
  delete Rtn;
}

void SteadyStateWidget::CancelChange()
{
  if (mSteadyStateTask == NULL)
    return;
  CSteadyStateProblem * steadystateproblem = mSteadyStateTask->getProblem();
  CSteadyStateMethod* steadystatemethod = mSteadyStateTask->getMethod();

  taskName->setText(tr("Steady State Task"));
  taskName->setEnabled(false);

  bool bJacobian = steadystateproblem->isJacobianRequested();
  bool bStatistics = steadystateproblem->isStabilityAnalysisRequested();
  taskJacobian->setChecked(bJacobian);
  taskStability->setChecked(bStatistics);

  parameterTable->setText(0, 0, QString::number(steadystatemethod->getValue("Newton.UseNewton")));
  parameterTable->updateCell(0, 0);

  parameterTable->setText(1, 0, QString::number(steadystatemethod->getValue("Newton.UseIntegration")));
  parameterTable->updateCell(1, 0);

  parameterTable->setText(2, 0, QString::number(steadystatemethod->getValue("Newton.UseBackIntegration")));
  parameterTable->updateCell(2, 0);

  parameterTable->setText(3, 0, QString::number(steadystatemethod->getValue("Newton.IterationLimit")));
  parameterTable->updateCell(3, 0);

  parameterTable->setText(4, 0, QString::number(steadystatemethod->getValue("Newton.DerivationFactor")));
  parameterTable->updateCell(4, 0);

  parameterTable->setText(5, 0, QString::number(steadystatemethod->getValue("Newton.Resolution")));
  parameterTable->updateCell(5, 0);

  parameterTable->setText(6, 0, QString::number(steadystatemethod->getValue("Newton.LSODA.RelativeTolerance")));
  parameterTable->updateCell(6, 0);

  parameterTable->setText(7, 0, QString::number(steadystatemethod->getValue("Newton.LSODA.AbsoluteTolerance")));
  parameterTable->updateCell(7, 0);

  parameterTable->setText(8, 0, QString::number(steadystatemethod->getValue("Newton.LSODA.AdamsMaxOrder")));
  parameterTable->updateCell(8, 0);

  parameterTable->setText(9, 0, QString::number(steadystatemethod->getValue("Newton.LSODA.BDFMaxOrder")));
  parameterTable->updateCell(9, 0);
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

  //Liang Reach Here finalfantasy
}
