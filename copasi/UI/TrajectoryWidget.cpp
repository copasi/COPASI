/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/TrajectoryWidget.cpp,v $
   $Revision: 1.89 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/31 18:34:46 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 02/03 
Comment : TrajectoryWidget
Contact: Please contact lixu1@vt.edu.
 *********************************************************/
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

#include "TrajectoryWidget.h"
#include "qtUtilities.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "model/CModel.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "report/CKeyFactory.h"
#include "CReportDefinitionSelect.h"
#include "MyLineEdit.h"
#include "utilities/CCopasiException.h"
#include "CProgressBar.h"
#include "plot/CPlotSpec2Vector.h"

#include "copasiui3window.h"
#include "qmessagebox.h"
#include "qapplication.h" 
/*
 *  Constructs a TrajectoryWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TrajectoryWidget::TrajectoryWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    pParent(parent)
{
  if (!name)
    setName("TrajectoryWidget");
  setCaption(trUtf8("TrajectoryWidget"));
  TrajectoryWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "TrajectoryWidgetLayout");

  //Name
  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));
  taskNameLabel->setAlignment(int(QLabel::AlignVCenter
                                  | QLabel::AlignRight));
  TrajectoryWidgetLayout->addWidget(taskNameLabel, 0, 0);

  taskName = new QLineEdit(this, "taskName");
  TrajectoryWidgetLayout->addMultiCellWidget(taskName, 0, 0, 1, 2);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("Task Executable "));
  TrajectoryWidgetLayout->addWidget(bExecutable, 0, 3);

  line8 = new QFrame(this, "line8");
  line8->setFrameShape(QFrame::HLine);
  TrajectoryWidgetLayout->addMultiCellWidget(line8, 1, 1, 0, 3);

  //*****************************

  nStartTime = new MyLineEdit(this, "nStartTime");
  //nStartTime->setText(trUtf8(""));
  nStartTime->setValidator(new QDoubleValidator(nStartTime));
  TrajectoryWidgetLayout->addWidget(nStartTime, 2, 1);

  TextLabel1_3 = new QLabel(this, "TextLabel1_3");
  TextLabel1_3->setText(trUtf8("Start Time"));
  TextLabel1_3->setAlignment(int(QLabel::AlignVCenter
                                 | QLabel::AlignRight));
  TrajectoryWidgetLayout->addWidget(TextLabel1_3, 2, 0);

  //****
  nEndTime = new MyLineEdit(this, "nEndTime");
  //nEndTime->setText(trUtf8(""));
  nEndTime->setValidator(new QDoubleValidator(nEndTime));
  TrajectoryWidgetLayout->addWidget(nEndTime, 2, 3);

  TextLabel1_2_2 = new QLabel(this, "TextLabel1_2_2");
  TextLabel1_2_2->setText(trUtf8("End Time"));
  TrajectoryWidgetLayout->addWidget(TextLabel1_2_2, 2, 2);

  //****
  nStepSize = new MyLineEdit(this, "nStepSize");
  //nStepSize->setText(trUtf8(""));
  nStepSize->setValidator(new QDoubleValidator(nStepSize));
  TrajectoryWidgetLayout->addWidget(nStepSize, 3, 1);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Interval size"));
  TextLabel1->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  TrajectoryWidgetLayout->addWidget(TextLabel1, 3, 0);

  //****
  nStepNumber = new MyLineEdit(this, "nStepNumber");
  //nStepNumber->setText(trUtf8(""));
  nStepNumber->setValidator(new QIntValidator(1, 1000000000, nStepNumber));
  TrajectoryWidgetLayout->addWidget(nStepNumber, 3, 3);

  TextLabel1_2 = new QLabel(this, "TextLabel1_2");
  TextLabel1_2->setText(trUtf8("Intervals"));
  TrajectoryWidgetLayout->addWidget(TextLabel1_2, 3, 2);

  QHBox* tmpBox = new QHBox(this);

  mCheckBoxStartOutput = new QCheckBox(tmpBox);
  mCheckBoxStartOutput->setText(trUtf8("Start output after t="));
  //QLabel* tmpLable = new QLabel(tmpBox);
  //tmpLable->setText(trUtf8("Start output after t="));
  mLineEditStartOutput = new QLineEdit(tmpBox);
  TrajectoryWidgetLayout->addMultiCellWidget(tmpBox, 4, 4, 1, 2);

  //
  bStoreTimeSeries = new QCheckBox(this, "bStoreTimeSeries");
  bStoreTimeSeries->setText(trUtf8("store time series in memory "));
  TrajectoryWidgetLayout->addWidget(bStoreTimeSeries, 5, 1);

  //
  setInitialState = new QCheckBox(this, "setInitialState");
  setInitialState->setText(trUtf8("Use result as new initial state"));
  TrajectoryWidgetLayout->addWidget(setInitialState, 6, 1, Qt::AlignLeft);

  //****
  line7_2 = new QFrame(this, "line7_2");
  line7_2->setFrameShape(QFrame::HLine);
  line7_2->setFrameShadow(QFrame::Sunken);
  TrajectoryWidgetLayout->addMultiCellWidget(line7_2, 7, 7, 0, 3);

  //***** method *************************
  TextLabel1_3_2 = new QLabel(this, "TextLabel1_3_2");
  TextLabel1_3_2->setText(trUtf8("Method"));
  TextLabel1_3_2->setAlignment(int(QLabel::AlignVCenter
                                   | QLabel::AlignRight));
  TrajectoryWidgetLayout->addWidget(TextLabel1_3_2, 8, 0);

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");
  TrajectoryWidgetLayout->addMultiCellWidget(ComboBox1, 8, 8, 1, 2);

  /*line7 = new QFrame(this, "line7");
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  TrajectoryWidgetLayout->addMultiCellWidget(line7, 6, 6, 0, 3);*/

  //**********
  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Method parameters"));
  parameterValueLabel->setAlignment(int(QLabel::AlignVCenter
                                        | QLabel::AlignRight));
  TrajectoryWidgetLayout->addWidget(parameterValueLabel, 9, 0);

  QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TrajectoryWidgetLayout->addItem(spacer, 10, 0);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));
  parameterTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  TrajectoryWidgetLayout->addMultiCellWidget(parameterTable, 9, 10, 1, 3);

  QSpacerItem* spacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TrajectoryWidgetLayout->addMultiCell(spacer_3, 11, 11, 0, 2);

  //

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  TrajectoryWidgetLayout->addMultiCellWidget(line6, 12, 12, 0, 3);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  bRunTask = new QPushButton(this, "bRunTask");

  if (parent == NULL)
    bRunTask->setText(trUtf8("OK"));
  else
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
  reportDefinitionButton->setText(trUtf8("ReportDefinition"));
  Layout2->addWidget(reportDefinitionButton);

  TrajectoryWidgetLayout->addMultiCellLayout(Layout2, 13, 13, 0, 3);

  setTabOrder(taskName, bExecutable);
  setTabOrder(bExecutable, setInitialState);
  setTabOrder(setInitialState, nStartTime);
  setTabOrder(nStartTime, nEndTime);
  setTabOrder(nEndTime, nStepSize);
  setTabOrder(nStepSize, nStepNumber);
  setTabOrder(nStepNumber, ComboBox1);
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
  connect(bRunTask, SIGNAL(clicked()), this, SLOT(runTrajectoryTask()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));
  //connect(bExecutable, SIGNAL(clicked()), this, SLOT(EnableRunTask()));
  connect(ComboBox1, SIGNAL(activated(int)), this, SLOT(UpdateMethod()));
  //connect(ExportToFileButton, SIGNAL(clicked()), this, SLOT(ExportToFile()));

  connect(nStartTime, SIGNAL(edited()), this, SLOT(StartTimeSlot()));
  connect(nEndTime, SIGNAL(edited()), this, SLOT(EndTimeSlot()));
  connect(nStepSize, SIGNAL(edited()), this, SLOT(StepsizeSlot()));
  connect(nStepNumber, SIGNAL(edited()), this, SLOT(NumStepsSlot()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
TrajectoryWidget::~TrajectoryWidget()
{
  //  CTrajectoryTask* tt =
  //    dynamic_cast<CTrajectoryTask *>(GlobalKeys.get(objKey));
  //  pdelete(tt);
}

//**********************************************************

#define TSMAX 10000000

void TrajectoryWidget::StartTimeSlot()
{
  C_FLOAT64 start = nStartTime->text().toDouble();
  C_FLOAT64 end = nEndTime->text().toDouble();
  //C_FLOAT64 delta = nStepSize->text().toDouble();
  C_INT32 steps = nStepNumber->text().toInt();

  if (steps <= 0) return;
  if (end <= start)
    {
      nEndTime->setText(QString::number(start + 1.0));
      nStepSize->setText(QString::number(1.0 / (C_FLOAT64)steps));
    }
  else
    nStepSize->setText(QString::number((end - start) / steps));
}
void TrajectoryWidget::EndTimeSlot()
{
  C_FLOAT64 start = nStartTime->text().toDouble();
  C_FLOAT64 end = nEndTime->text().toDouble();
  //C_FLOAT64 delta = nStepSize->text().toDouble();
  C_INT32 steps = nStepNumber->text().toInt();

  if (steps <= 0) return;
  if (end <= start)
    {
      nStartTime->setText(QString::number(end - 1.0));
      nStepSize->setText(QString::number(1.0 / (C_FLOAT64)steps));
    }
  else
    nStepSize->setText(QString::number((end - start) / steps));
}
void TrajectoryWidget::StepsizeSlot()
{
  C_FLOAT64 start = nStartTime->text().toDouble();
  //C_FLOAT64 end = nEndTime->text().toDouble();
  C_FLOAT64 delta = nStepSize->text().toDouble();
  C_INT32 steps = nStepNumber->text().toInt();

  nEndTime->setText(QString::number(start + steps*delta));
}
void TrajectoryWidget::NumStepsSlot()
{
  C_FLOAT64 start = nStartTime->text().toDouble();
  C_FLOAT64 end = nEndTime->text().toDouble();
  //C_FLOAT64 delta = nStepSize->text().toDouble();
  C_INT32 steps = nStepNumber->text().toInt();

  if (steps <= 0) return;
  nStepSize->setText(QString::number((end - start) / (C_FLOAT64)steps));

  checkTimeSeries();
}

//void TrajectoryWidget::storeSlot()
//{
//  C_INT32 steps = nStepNumber->text().toInt();
//}

void TrajectoryWidget::checkTimeSeries()
{
  //std::cout << "checkTimeSeries() " << nStepNumber->text().toLong() << " " << dataModel->getModel()->getIntMetab() << std::endl;

  if (nStepNumber->text().toLong() * dataModel->getModel()->getNumVariableMetabs() > TSMAX)
    {
      bStoreTimeSeries->setChecked(false);
      bStoreTimeSeries->setEnabled(false);
    }
  else
    {
      bStoreTimeSeries->setEnabled(true);
    }
}

#undef TSMAX

//************************************************************

void TrajectoryWidget::CancelChange()
{
  loadTrajectoryTask();
}

void TrajectoryWidget::CommitChange()
{
  //  loadTrajectoryTask();
}

void TrajectoryWidget::runTrajectoryTask()
{
  if (dataModel->isChanged())
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
  checkTimeSeries();
  saveTrajectoryTask();

  if (bRunTask->text() != "Run")
    {
      hide();
      return;
    }

  CTrajectoryTask* tt =
    dynamic_cast<CTrajectoryTask *>(GlobalKeys.get(objKey));
  assert(tt);

  tt->initialize();

  CTrajectoryProblem* trajectoryproblem =
    dynamic_cast<CTrajectoryProblem *>(tt->getProblem());
  assert(trajectoryproblem);

  if ((!tt->getReport().getStream())
      && (dataModel->getPlotSpecVectorAddr()->size() == 0)
      && (!trajectoryproblem->timeSeriesRequested())
)
    {
      QMessageBox::information (NULL, "No output specified",
                                "No output would be generated from this simulation. \nSpecify a report, a plot, or activate the \"Store time series in memory\" checkbox.");
      //                                    QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
      return;
    }

  CTrajectoryMethod* trajectorymethod =
    dynamic_cast<CTrajectoryMethod *>(tt->getMethod());
  assert(trajectorymethod);
  if (trajectorymethod->getSubType() != CCopasiMethod::deterministic)
    {
      std::string message = dataModel->getModel()->suitableForStochasticSimulation();
      if (message != "")
        {
          QMessageBox::information (NULL, "Stochastic simulation not possible",
                                    FROM_UTF8(message));
          return;
        }
    }

  setCursor(Qt::WaitCursor);
  CProgressBar* tmpBar = new CProgressBar(dataModel);
  tt->setProgressHandler(tmpBar);

  try
    {
      tt->process();
      if (setInitialState->isChecked())
        {
          const CState *currentState = tt->getState();
          if (currentState)
            (dataModel->getModel())->setInitialState(currentState);
        }
    }
  catch (CCopasiException Exception)
    {
      std::cout << std::endl << "exception in trajectory task" << std::endl;
      //TODO: message box
    }

  tt->restore();

  tmpBar->finish(); pdelete(tmpBar);

  protectedNotify(ListViews::STATE, ListViews::CHANGE,
                  dataModel->getModel()->getKey());

  unsetCursor();
}

void TrajectoryWidget::ReportDefinitionClicked()
{
  CTrajectoryTask* trajectoryTask =
    dynamic_cast< CTrajectoryTask * >(GlobalKeys.get(objKey));
  assert(trajectoryTask);

  CReportDefinitionSelect * pSelectDlg = new CReportDefinitionSelect(pParent);
  pSelectDlg->setReport(&trajectoryTask->getReport());
  pSelectDlg->loadReportDefinitionVector();
  pSelectDlg->exec();

  delete pSelectDlg;
}

//**************************************************************************

void TrajectoryWidget::loadTrajectoryTask()
{
  CTrajectoryTask* tt =
    dynamic_cast<CTrajectoryTask *>(GlobalKeys.get(objKey));
  assert(tt);

  CTrajectoryProblem* trajectoryproblem =
    dynamic_cast<CTrajectoryProblem *>(tt->getProblem());
  assert(trajectoryproblem);

  CTrajectoryMethod* trajectorymethod =
    dynamic_cast<CTrajectoryMethod *>(tt->getMethod());
  assert(trajectorymethod);

  //name
  taskName->setText(tr("Trajectory Task"));
  taskName->setEnabled(false);

  //numbers
  nStepSize->setText(QString::number(trajectoryproblem->getStepSize()));
  nStepNumber->setText(QString::number(trajectoryproblem->getStepNumber()));
  nStartTime->setText(QString::number(trajectoryproblem->getStartTime()));
  nEndTime->setText(QString::number(trajectoryproblem->getEndTime()));

  //store time series checkbox
  bStoreTimeSeries->setChecked(trajectoryproblem->timeSeriesRequested());
  checkTimeSeries();

  //method parameters
  loadMethodParameters();

  //method subtype
  ComboBox1->clear ();
  unsigned C_INT32 i;
  for (i = 0; i < CTrajectoryMethod::ValidSubTypes.size(); i++)
    ComboBox1->
    insertItem(FROM_UTF8(CCopasiMethod::SubTypeName[CTrajectoryMethod::ValidSubTypes[i]]));

  ComboBox1->setCurrentText(FROM_UTF8(CCopasiMethod::SubTypeName[trajectorymethod->getSubType()]));
}

void TrajectoryWidget::loadMethodParameters()
{
  CTrajectoryTask* tt =
    dynamic_cast<CTrajectoryTask *>(GlobalKeys.get(objKey));
  assert(tt);

  CTrajectoryMethod* trajectorymethod =
    dynamic_cast<CTrajectoryMethod *>(tt->getMethod());
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

void TrajectoryWidget::saveTrajectoryTask()
{
  CTrajectoryTask* tt =
    dynamic_cast<CTrajectoryTask *>(GlobalKeys.get(objKey));

  assert(tt);

  CTrajectoryProblem* trajectoryproblem =
    dynamic_cast<CTrajectoryProblem *>(tt->getProblem());
  assert(trajectoryproblem);

  CTrajectoryMethod* trajectorymethod =
    dynamic_cast<CTrajectoryMethod *>(tt->getMethod());
  assert(trajectorymethod);

  //numbers
  if (trajectoryproblem->getStepSize() != nStepSize->text().toDouble())
    trajectoryproblem->setStepSize(nStepSize->text().toDouble());
  else if (trajectoryproblem->getStepNumber() != nStepNumber->text().toLong())
    trajectoryproblem->setStepNumber(nStepNumber->text().toLong());
  trajectoryproblem->setStartTime(nStartTime->text().toDouble());
  trajectoryproblem->setEndTime(nEndTime->text().toDouble());

  trajectoryproblem->setTimeSeriesRequested(bStoreTimeSeries->isChecked());

  //set initial state
  trajectoryproblem->setInitialState(dataModel->getModel()->getInitialState());

  //method
  if (CCopasiMethod::SubTypeName[trajectorymethod->getSubType()] !=
      (const char *)ComboBox1->currentText().utf8())
    UpdateMethod(false);

  QTableItem * pItem;
  QString value;
  QString strname;

  unsigned C_INT32 i;
  for (i = 0; i < trajectorymethod->size(); i++)
    {
      pItem = parameterTable->item(i, 0);
      value = pItem->text();
      setParameterValue(trajectorymethod, i, value);
    }
}

//*********************************************************************

void TrajectoryWidget::UpdateMethod(const bool & update)
{
  //if (!mTrajectoryTask)
  //  return;
  CTrajectoryTask* tt =
    dynamic_cast<CTrajectoryTask *>(GlobalKeys.get(objKey));
  assert(tt);

  CTrajectoryProblem* trajectoryproblem =
    dynamic_cast<CTrajectoryProblem *>(tt->getProblem());
  assert(trajectoryproblem);

  CTrajectoryMethod* trajectorymethod =
    dynamic_cast<CTrajectoryMethod *>(tt->getMethod());
  assert(trajectorymethod);

  CCopasiMethod::SubType SubType =
    CCopasiMethod::TypeNameToEnum((const char *)ComboBox1->currentText().utf8());

  if (SubType != CCopasiMethod::unset)
    {
      tt->setMethodType(SubType);
      trajectorymethod = dynamic_cast<CTrajectoryMethod *>(tt->getMethod());
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

//void TrajectoryWidget::ExportToFile()
//{}

bool TrajectoryWidget::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
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

bool TrajectoryWidget::leave()
{
  saveTrajectoryTask();
  return true;
}

bool TrajectoryWidget::enter(const std::string & key)
{
  if (!dynamic_cast< CTrajectoryTask * >(GlobalKeys.get(key))) return false;

  objKey = key;

  loadTrajectoryTask();

  return true;
}
