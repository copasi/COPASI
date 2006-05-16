/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQLyapWidget.cpp,v $
   $Revision: 1.4.2.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/05/16 16:30:31 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qvariant.h>
#include <qcheckbox.h>
#include <qcombobox.h>
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

#include "CQLyapWidget.h"
#include "qtUtilities.h"

#include "lyap/CLyapTask.h"
#include "lyap/CLyapProblem.h"
#include "model/CModel.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "CReportDefinitionSelect.h"
#include "MyLineEdit.h"
#include "utilities/CCopasiException.h"
#include "CProgressBar.h"
#include "plot/COutputDefinitionVector.h"

#include "copasiui3window.h"
#include "DefaultplotDialog.h"

/*
 *  Constructs a CQLyapWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQLyapWidget::CQLyapWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
    //pParent(parent),
    //mpProblem(NULL)
{
  if (!name)
    setName("CQLyapWidget");
  setCaption(trUtf8("CQLyapWidget"));
  CQLyapWidgetLayout = new QGridLayout(this, 1, 1, 11, 8, "CQLyapWidgetLayout");

  QHBoxLayout* tmpLayout = new QHBoxLayout();

  taskNameLabel = new QLabel(this, "taskNameLabel");
  //taskNameLabel->setText(trUtf8("Task Name"));
  taskNameLabel->setText(trUtf8("<h2>Lyapunov Exponents</h2>"));
  taskNameLabel->setAlignment(int(QLabel::AlignVCenter
                                  | QLabel::AlignLeft));
  //SteadyStateWidgetLayout->addWidget(taskNameLabel, 0, 0);
  tmpLayout->addWidget(taskNameLabel);

  QSpacerItem* tmpSpacer = new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);
  tmpLayout->addItem(tmpSpacer);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("executable"));
  // this is the child widget to edit an steadystatetask
  bExecutable->setChecked(parent == NULL);
  bExecutable->setEnabled(parent != NULL);
  //SteadyStateWidgetLayout->addWidget(bExecutable, 0, 2);
  tmpLayout->addWidget(bExecutable);

  CQLyapWidgetLayout->addMultiCellLayout(tmpLayout, 0, 0, 1, 3);

  QSpacerItem* spacer2 = new QSpacerItem(0, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);
  CQLyapWidgetLayout->addItem(spacer2, 1, 1);

  //****

  lineNum = new MyLineEdit(this, "lineNum");
  lineNum->setValidator(new QIntValidator(1, 50, lineNum));
  CQLyapWidgetLayout->addWidget(lineNum, 2, 1);

  TextLabelNum = new QLabel(this, "TextLabelNum");
  TextLabelNum->setText("Number of exponents");
  TextLabelNum->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));
  CQLyapWidgetLayout->addWidget(TextLabelNum, 2, 0);

  //***********************

  tmpLayout = new QHBoxLayout();
  //QHBox* tmpBox = new QHBox(this);

  mCheckBoxStartOutput = new QCheckBox(this);
  mCheckBoxStartOutput->setText(trUtf8("Start output after t="));
  tmpLayout->addWidget(mCheckBoxStartOutput);

  mLineEditStartOutput = new QLineEdit(this);
  mLineEditStartOutput->setValidator(new QDoubleValidator(mLineEditStartOutput));
  tmpLayout->addWidget(mLineEditStartOutput);

  tmpSpacer = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
  tmpLayout->addItem(tmpSpacer);

  CQLyapWidgetLayout->addMultiCellLayout(tmpLayout, 4, 4, 1, 3);

  //*******************

  //
  //bStoreTimeSeries = new QCheckBox(this, "bStoreTimeSeries");
  //bStoreTimeSeries->setText(trUtf8("store time series in memory "));
  //CQLyapWidgetLayout->addMultiCellWidget(bStoreTimeSeries, 5, 5, 1, 3);

  //
  bDivergence = new QCheckBox(this, "bDivergence");
  bDivergence->setText(trUtf8("calculate Divergence "));
  CQLyapWidgetLayout->addMultiCellWidget(bDivergence, 5, 5, 1, 3);

  //
  setInitialState = new QCheckBox(this, "setInitialState");
  setInitialState->setText(trUtf8("Use result as new initial state"));
  CQLyapWidgetLayout->addMultiCellWidget(setInitialState, 6, 6, 1, 3, Qt::AlignLeft);

  //****
  line7_2 = new QFrame(this, "line7_2");
  line7_2->setFrameShape(QFrame::HLine);
  line7_2->setFrameShadow(QFrame::Sunken);
  CQLyapWidgetLayout->addMultiCellWidget(line7_2, 7, 7, 0, 3);

  //***** method *************************
  TextLabel1_3_2 = new QLabel(this, "TextLabel1_3_2");
  TextLabel1_3_2->setText(trUtf8("Method"));
  TextLabel1_3_2->setAlignment(int(QLabel::AlignVCenter
                                   | QLabel::AlignRight));
  CQLyapWidgetLayout->addWidget(TextLabel1_3_2, 8, 0);

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");
  CQLyapWidgetLayout->addMultiCellWidget(ComboBox1, 8, 8, 1, 2);

  /*line7 = new QFrame(this, "line7");
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  CQLyapWidgetLayout->addMultiCellWidget(line7, 6, 6, 0, 3);*/

  //**********
  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Method parameters"));
  parameterValueLabel->setAlignment(int(QLabel::AlignVCenter
                                        | QLabel::AlignRight));
  CQLyapWidgetLayout->addWidget(parameterValueLabel, 9, 0);

  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQLyapWidgetLayout->addItem(spacer, 10, 0);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  parameterTable->setColumnStretchable(0, true);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  parameterTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  CQLyapWidgetLayout->addMultiCellWidget(parameterTable, 9, 10, 1, 3);

  QSpacerItem* spacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  CQLyapWidgetLayout->addMultiCell(spacer_3, 11, 11, 0, 2);

  //

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  CQLyapWidgetLayout->addMultiCellWidget(line6, 12, 12, 0, 3);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  bRunTask = new QPushButton(this, "bRunTask");

  bRunTask->setText(trUtf8("Run"));

  //bRunTask->setEnabled(parent == NULL);
  Layout2->addWidget(bRunTask);

  //  commitChange = new QPushButton(this, "commitChange");
  //  commitChange->setText(trUtf8("Commit"));
  //  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Revert"));
  Layout2->addWidget(cancelChange);

  //ExportToFileButton = new QPushButton(this, "ExportToFileButton");
  //ExportToFileButton->setText(trUtf8("Export To File"));
  //Layout2->addWidget(ExportToFileButton);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("Report"));
  Layout2->addWidget(reportDefinitionButton);

  outputDefinitionButton = new QPushButton(this, "OutputDefinition");
  outputDefinitionButton->setText(trUtf8("Output Assistant"));
  Layout2->addWidget(outputDefinitionButton);

  CQLyapWidgetLayout->addMultiCellLayout(Layout2, 13, 13, 0, 3);

  //setTabOrder(taskName, bExecutable);
  setTabOrder(bExecutable, setInitialState);
  //setTabOrder(setInitialState, nDuration);
  //setTabOrder(nDuration, nStepSize);
  //setTabOrder(nStepSize, nStepNumber);
  //setTabOrder(nStepNumber, ComboBox1);
  setTabOrder(ComboBox1, parameterTable);
  setTabOrder(parameterTable, bRunTask);
  //  setTabOrder(bRunTask, commitChange);
  //  setTabOrder(commitChange, cancelChange);
  setTabOrder(bRunTask, cancelChange);
  //setTabOrder(cancelChange, ExportToFileButton);
  //setTabOrder(ExportToFileButton, reportDefinitionButton);

  // signals and slots connections
  //connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));
  connect(bRunTask, SIGNAL(clicked()), this, SLOT(runLyapTask()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));
  connect(outputDefinitionButton, SIGNAL(clicked()), this, SLOT(outputDefinitionClicked()));
  //connect(bExecutable, SIGNAL(clicked()), this, SLOT(EnableRunTask()));
  connect(ComboBox1, SIGNAL(activated(int)), this, SLOT(UpdateMethod()));
  //connect(ExportToFileButton, SIGNAL(clicked()), this, SLOT(ExportToFile()));

  //  connect(nStartTime, SIGNAL(edited()), this, SLOT(StartTimeSlot()));
  //connect(nDuration, SIGNAL(edited()), this, SLOT(DurationSlot()));
  //connect(nStepSize, SIGNAL(edited()), this, SLOT(StepsizeSlot()));
  //connect(nStepNumber, SIGNAL(edited()), this, SLOT(NumStepsSlot()));

  connect(mCheckBoxStartOutput, SIGNAL(toggled(bool)),
          mLineEditStartOutput, SLOT(setEnabled(bool)));
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQLyapWidget::~CQLyapWidget()
{
  //pdelete(mpProblem);
}

//**********************************************************

#define TSMAX 10000000

//this is left here for the case that I will enable the checkTimeseries later

/*void CQLyapWidget::NumStepsSlot()
{
  try
    {
      mpProblem->setStepNumber(nStepNumber->text().toULong());
    }
  catch (...)
    {
      QMessageBox::warning(this, QString("File Warning"),
                           FROM_UTF8(CCopasiMessage::getAllMessageText()),
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
    }
































  nStepSize->setText(QString::number(mpProblem->getStepSize()));
































  checkTimeSeries();
}*/

/*void CQLyapWidget::checkTimeSeries()
{
  //std::cout << "checkTimeSeries() " << nStepNumber->text().toLong() << " " << CCopasiDataModel::Global->getModel()->getIntMetab() << std::endl;
































  if (nStepNumber->text().toLong() * CCopasiDataModel::Global->getModel()->getNumVariableMetabs() > TSMAX)
    {
      bStoreTimeSeries->setChecked(false);
      bStoreTimeSeries->setEnabled(false);
    }
  else
    {
      bStoreTimeSeries->setEnabled(true);
    }
}*/

#undef TSMAX

//************************************************************

void CQLyapWidget::CancelChange()
{
  loadLyapTask();
}

void CQLyapWidget::CommitChange()
{
  //  loadLyapTask();
}

void CQLyapWidget::runLyapTask()
{
  bool success = true;
  CCopasiMessage::clearDeque();

  //checkTimeSeries();
  saveLyapTask();

  static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);

  CLyapTask* tt =
    dynamic_cast<CLyapTask *>(GlobalKeys.get(objKey));
  assert(tt);

  CCopasiMessage::clearDeque();

  try
    {
      success = tt->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);
    }
  catch (CCopasiException)
    {
      success = false;
    }

  if (!success &&
      CCopasiMessage::getHighestSeverity() > CCopasiMessage::WARNING)
    {
      QMessageBox::warning(this, "Simulation Error",
                           CCopasiMessage::getAllMessageText().c_str(),
                           QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);

      return;
    }

  CCopasiMessage::clearDeque();
  success = true;

  CLyapProblem* trajectoryproblem =
    dynamic_cast<CLyapProblem *>(tt->getProblem());
  assert(trajectoryproblem);

  if ((!tt->getReport().getStream())
      && (CCopasiDataModel::Global->getPlotDefinitionList()->size() == 0)
      /*&& (!trajectoryproblem->timeSeriesRequested())*/)
    {
      QMessageBox::information (NULL, "No output specified",
                                "No output would be generated from this simulation. \nSpecify a report, a plot, or activate the \"Store time series in memory\" checkbox.");
      //                                    QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
      return;
    }

  CLyapMethod* trajectorymethod =
    dynamic_cast<CLyapMethod *>(tt->getMethod());
  assert(trajectorymethod);

  setCursor(Qt::WaitCursor);
  CCopasiMessage::clearDeque();
  CProgressBar * tmpBar = new CProgressBar();
  tt->setCallBack(tmpBar);

  try
    {
      if (!tt->process(true))
        throw CCopasiException(CCopasiMessage::peekLastMessage());
    }

  catch (CCopasiException Exception)
    {
      success = false;

      if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
        {
          tmpBar->finish();
          QMessageBox::warning(this, "Simulation Error", CCopasiMessage::getAllMessageText().c_str(), QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }
    }

  tt->restore();

  tt->setCallBack(NULL);
  tmpBar->finish(); pdelete(tmpBar);
  CCopasiDataModel::Global->finish();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(false);

  protectedNotify(ListViews::STATE, ListViews::CHANGE,
                  CCopasiDataModel::Global->getModel()->getKey());

  loadLyapTask();
  unsetCursor();
}

void CQLyapWidget::ReportDefinitionClicked()
{
  CLyapTask* trajectoryTask =
    dynamic_cast< CLyapTask * >(GlobalKeys.get(objKey));
  assert(trajectoryTask);

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(pListView);
  pSelectDlg->setReport(&trajectoryTask->getReport());
  pSelectDlg->loadReportDefinitionVector();
  pSelectDlg->exec();

  delete pSelectDlg;
}

void CQLyapWidget::outputDefinitionClicked()
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

//**************************************************************************

void CQLyapWidget::loadLyapTask()
{
  CLyapTask* tt =
    dynamic_cast<CLyapTask *>(GlobalKeys.get(objKey));
  assert(tt);

  bExecutable->setChecked(tt->isScheduled());
  setInitialState->setChecked(tt->isUpdateModel());

  CLyapProblem* problem =
    dynamic_cast<CLyapProblem *>(tt->getProblem());
  assert(problem);

  CLyapMethod* method =
    dynamic_cast<CLyapMethod *>(tt->getMethod());
  assert(method);

  //numbers
  //nStepSize->setText(QString::number(trajectoryproblem->getStepSize()));
  //nStepNumber->setText(QString::number(trajectoryproblem->getStepNumber()));
  //  nStartTime->setText(QString::number(trajectoryproblem->getStartTime()));
  //nDuration->setText(QString::number(problem->getDuration()));

  lineNum->setText(QString::number(problem->getExponentNumber()));

  bool tmpflag (CCopasiDataModel::Global->getModel()->getInitialTime()
                == problem->getTransientTime());
  mCheckBoxStartOutput->setChecked(!tmpflag);
  mLineEditStartOutput->setEnabled(!tmpflag);
  mLineEditStartOutput->setText(QString::number(problem->getTransientTime()));

  //store time series checkbox
  //bStoreTimeSeries->setChecked(problem->timeSeriesRequested());
  //checkTimeSeries();

  //divergence
  bDivergence->setChecked(problem->divergenceRequested());

  //method parameters
  loadMethodParameters();

  //method subtype
  ComboBox1->clear ();
  unsigned C_INT32 i;
  for (i = 0; i < CLyapMethod::ValidSubTypes.size(); i++)
    ComboBox1->
    insertItem(FROM_UTF8(CCopasiMethod::SubTypeName[CLyapMethod::ValidSubTypes[i]]));

  ComboBox1->setCurrentText(FROM_UTF8(CCopasiMethod::SubTypeName[method->getSubType()]));
}

void CQLyapWidget::loadMethodParameters()
{
  CLyapTask* tt =
    dynamic_cast<CLyapTask *>(GlobalKeys.get(objKey));
  assert(tt);

  CLyapMethod* trajectorymethod =
    dynamic_cast<CLyapMethod *>(tt->getMethod());
  assert(trajectorymethod);

  QTableItem * pItem;
  QString value;
  QString strname;

  parameterTable->setNumRows(trajectorymethod->size());
  QHeader *rowHeader = parameterTable->verticalHeader();

  unsigned C_INT32 i;
  CCopasiParameter::Type Type;
  for (i = 0; i < trajectorymethod->size(); i++)
    {
      strname = FROM_UTF8((trajectorymethod->getName(i)));
      rowHeader->setLabel(i, tr(strname));

      value = getParameterValue(trajectorymethod, i, &Type);
      pItem = new QTableItem (parameterTable, QTableItem::Always, value);
      parameterTable->setItem(i, 0, pItem);
    }
}

void CQLyapWidget::saveLyapTask()
{
  CLyapTask* tt =
    dynamic_cast<CLyapTask *>(GlobalKeys.get(objKey));
  assert(tt);

  bool bScheduled = bExecutable->isChecked();
  tt->setScheduled(bScheduled);
  tt->setUpdateModel(setInitialState->isChecked());

  CLyapProblem* problem =
    dynamic_cast<CLyapProblem *>(tt->getProblem());
  assert(problem);

  CLyapMethod* method =
    dynamic_cast<CLyapMethod *>(tt->getMethod());
  assert(method);

  //numbers
  //if (trajectoryproblem->getStepSize() != nStepSize->text().toDouble())
  //  trajectoryproblem->setStepSize(nStepSize->text().toDouble());
  //else if (trajectoryproblem->getStepNumber() != nStepNumber->text().toULong())
  //  trajectoryproblem->setStepNumber(nStepNumber->text().toLong());
  //  trajectoryproblem->setStartTime(nStartTime->text().toDouble());
  //trajectoryproblem->setDuration(nDuration->text().toDouble());

  C_INT32 tmpint = lineNum->text().toInt();
  if (tmpint <= 0) tmpint = 1;
  problem->setExponentNumber(tmpint);

  if (mCheckBoxStartOutput->isChecked())
    problem->setTransientTime(mLineEditStartOutput->text().toDouble());
  else
    problem->setTransientTime(CCopasiDataModel::Global->getModel()->getInitialTime());

  //problem->setTimeSeriesRequested(bStoreTimeSeries->isChecked());

  problem->setDivergenceRequested(bDivergence->isChecked());

  //set initial state
  CCopasiDataModel::Global->getModel()->compileIfNecessary();
  //trajectoryproblem->setInitialState(CCopasiDataModel::Global->getModel()->getInitialState());

  //method
  if (CCopasiMethod::SubTypeName[method->getSubType()] !=
      (const char *)ComboBox1->currentText().utf8())
    UpdateMethod(false);

  QTableItem * pItem;
  QString value;
  QString strname;

  unsigned C_INT32 i;
  for (i = 0; i < method->size(); i++)
    {
      pItem = parameterTable->item(i, 0);
      value = pItem->text();
      setParameterValue(method, i, value);
    }

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();
}

//*********************************************************************

void CQLyapWidget::UpdateMethod(const bool & update)
{
  //if (!mLyapTask)
  //  return;
  CLyapTask* tt =
    dynamic_cast<CLyapTask *>(GlobalKeys.get(objKey));
  assert(tt);

  CLyapProblem* trajectoryproblem =
    dynamic_cast<CLyapProblem *>(tt->getProblem());
  assert(trajectoryproblem);

  CLyapMethod* trajectorymethod =
    dynamic_cast<CLyapMethod *>(tt->getMethod());
  assert(trajectorymethod);

  CCopasiMethod::SubType SubType =
    CCopasiMethod::TypeNameToEnum((const char *)ComboBox1->currentText().utf8());

  if (SubType != CCopasiMethod::unset)
    {
      tt->setMethodType(SubType);
      trajectorymethod = dynamic_cast<CLyapMethod *>(tt->getMethod());
      assert(trajectorymethod);
    }
  else
    {
      QMessageBox::warning(this, NULL,
                           "New method cannot be created by the parameters!",
                           QMessageBox::Ok, QMessageBox::Cancel);
    }

  if (update) loadMethodParameters();
}

//void CQLyapWidget::ExportToFile()
//{}

bool CQLyapWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
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

bool CQLyapWidget::leave()
{
  saveLyapTask();
  return true;
}

bool CQLyapWidget::enter(const std::string & key)
{
  if (!dynamic_cast< CLyapTask * >(GlobalKeys.get(key))) return false;

  objKey = key;

  loadLyapTask();

  return true;
}
