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

#include "TrajectoryWidget.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "model/CModel.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "CReportDefinitionSelect.h"

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

  line8 = new QFrame(this, "line8");
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  TrajectoryWidgetLayout->addMultiCellWidget(line8, 1, 1, 0, 3);

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setNumRows(0);
  parameterTable->setNumCols(1);
  QHeader *colHeader = parameterTable->horizontalHeader();
  colHeader->setLabel(0, tr("Value"));

  TrajectoryWidgetLayout->addMultiCellWidget(parameterTable, 7, 8, 1, 3);

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));

  TrajectoryWidgetLayout->addWidget(taskNameLabel, 0, 0);

  line7 = new QFrame(this, "line7");
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  line7->setFrameShape(QFrame::HLine);

  TrajectoryWidgetLayout->addMultiCellWidget(line7, 6, 6, 0, 3);

  line7_2 = new QFrame(this, "line7_2");
  line7_2->setFrameShape(QFrame::HLine);
  line7_2->setFrameShadow(QFrame::Sunken);
  line7_2->setFrameShape(QFrame::HLine);

  TrajectoryWidgetLayout->addMultiCellWidget(line7_2, 4, 4, 0, 3);

  taskName = new QLineEdit(this, "taskName");

  TrajectoryWidgetLayout->addMultiCellWidget(taskName, 0, 0, 1, 2);

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");

  TrajectoryWidgetLayout->addMultiCellWidget(ComboBox1, 5, 5, 1, 2);

  nStartTime = new QLineEdit(this, "nStartTime");
  nStartTime->setText(trUtf8(""));

  TrajectoryWidgetLayout->addWidget(nStartTime, 3, 1);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("Task Executable "));

  bExecutable->setEnabled(parent != NULL);
  bExecutable->setChecked(parent == NULL);

  TrajectoryWidgetLayout->addWidget(bExecutable, 0, 3);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Step Size"));

  TrajectoryWidgetLayout->addWidget(TextLabel1, 2, 0);

  TextLabel1_3 = new QLabel(this, "TextLabel1_3");
  TextLabel1_3->setText(trUtf8("Start Time"));

  TrajectoryWidgetLayout->addWidget(TextLabel1_3, 3, 0);

  TextLabel1_3_2 = new QLabel(this, "TextLabel1_3_2");
  TextLabel1_3_2->setText(trUtf8("Method"));

  TrajectoryWidgetLayout->addWidget(TextLabel1_3_2, 5, 0);

  nStepSize = new QLineEdit(this, "nStepSize");
  nStepSize->setText(trUtf8(""));

  TrajectoryWidgetLayout->addWidget(nStepSize, 2, 1);

  TextLabel1_2_2 = new QLabel(this, "TextLabel1_2_2");
  TextLabel1_2_2->setText(trUtf8("End Time"));

  TrajectoryWidgetLayout->addWidget(TextLabel1_2_2, 3, 2);

  nEndTime = new QLineEdit(this, "nEndTime");
  nEndTime->setText(trUtf8(""));

  TrajectoryWidgetLayout->addWidget(nEndTime, 3, 3);

  nStepNumber = new QLineEdit(this, "nStepNumber");
  nStepNumber->setText(trUtf8(""));

  TrajectoryWidgetLayout->addWidget(nStepNumber, 2, 3);

  TextLabel1_2 = new QLabel(this, "TextLabel1_2");
  TextLabel1_2->setText(trUtf8("Step Number"));

  TrajectoryWidgetLayout->addWidget(TextLabel1_2, 2, 2);

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);

  TrajectoryWidgetLayout->addMultiCellWidget(line6, 9, 9, 0, 3);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  bRunTask = new QPushButton(this, "bRunTask");

  if (parent == NULL)
    bRunTask->setText(trUtf8("OK"));
  else
    bRunTask->setText(trUtf8("Run"));

  bRunTask->setEnabled(parent == NULL);
  Layout2->addWidget(bRunTask);

  //  commitChange = new QPushButton(this, "commitChange");
  //  commitChange->setText(trUtf8("Commit"));
  //  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Cancel"));
  Layout2->addWidget(cancelChange);

  ExportToFileButton = new QPushButton(this, "ExportToFileButton");
  ExportToFileButton->setText(trUtf8("Export To File"));
  Layout2->addWidget(ExportToFileButton);

  reportDefinitionButton = new QPushButton(this, "ReportDefinition");
  reportDefinitionButton->setText(trUtf8("ReportDefinition"));
  Layout2->addWidget(reportDefinitionButton);

  TrajectoryWidgetLayout->addMultiCellLayout(Layout2, 10, 10, 0, 3);
  QSpacerItem* spacer = new QSpacerItem(71, 330, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TrajectoryWidgetLayout->addItem(spacer, 8, 0);

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Parameter value"));

  TrajectoryWidgetLayout->addWidget(parameterValueLabel, 7, 0);

  setTabOrder(taskName, bExecutable);
  setTabOrder(bExecutable, nStepSize);
  setTabOrder(nStepSize, nStepNumber);
  setTabOrder(nStepNumber, nStartTime);
  setTabOrder(nStartTime, nEndTime);
  setTabOrder(nEndTime, ComboBox1);
  setTabOrder(ComboBox1, parameterTable);
  setTabOrder(parameterTable, bRunTask);
  //  setTabOrder(bRunTask, commitChange);
  //  setTabOrder(commitChange, cancelChange);
  setTabOrder(bRunTask, cancelChange);
  setTabOrder(cancelChange, ExportToFileButton);
  setTabOrder(ExportToFileButton, reportDefinitionButton);

  // signals and slots connections
  //  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));
  connect(bRunTask, SIGNAL(clicked()), this, SLOT(RunTask()));
  connect(bExecutable, SIGNAL(clicked()), this, SLOT(EnableRunTask()));
  connect(ComboBox1, SIGNAL(activated(int)), this, SLOT(UpdateMethod()));
  connect(ExportToFileButton, SIGNAL(clicked()), this, SLOT(ExportToFile()));
  connect(reportDefinitionButton, SIGNAL(clicked()), this, SLOT(ReportDefinitionClicked()));

  //mTrajectoryTask = NULL;
}

/*
 *  Destroys the object and frees any allocated resources
 */
TrajectoryWidget::~TrajectoryWidget()
{
  // no need to delete child widgets, Qt does it all for us
  if (!CKeyFactory::get(objKey)) return;
  CTrajectoryTask* tt = (CTrajectoryTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  pdelete(tt);
}

void TrajectoryWidget::CancelChange()
{
  loadTrajectoryTask();
}

//void TrajectoryWidget::setModel(CModel* newModel)
//{
//if (mTrajectoryTask == NULL)
//  return;
//  CTrajectoryProblem * trajectoryproblem = dataModel->getTrajectoryTask()->getProblem();
//  trajectoryproblem->setModel(dataModel->getModel());
//}

void TrajectoryWidget::CommitChange()
{
  CTrajectoryTask* tt = (CTrajectoryTask*)(CCopasiContainer*)CKeyFactory::get(objKey);

  CTrajectoryProblem * trajectoryproblem = tt->getProblem();
  CTrajectoryMethod * trajectorymethod = tt->getMethod();

  if (trajectoryproblem->getStepSize() != nStepSize->text().toDouble())
    trajectoryproblem->setStepSize(nStepSize->text().toDouble());
  else if (trajectoryproblem->getStepNumber() != nStepNumber->text().toLong())
    trajectoryproblem->setStepNumber(nStepNumber->text().toLong());
  trajectoryproblem->setStartTime(nStartTime->text().toDouble());
  trajectoryproblem->setEndTime(nEndTime->text().toDouble());

  if (trajectorymethod->getTypeEnum() != (CTrajectoryMethod::Type)ComboBox1->currentItem())
    {
      CTrajectoryMethod* ptrTmpMethod = trajectorymethod;
      trajectorymethod = CTrajectoryMethod::createTrajectoryMethod((CTrajectoryMethod::Type)ComboBox1->currentItem(), trajectoryproblem);
      if (trajectorymethod != NULL)
        {
          trajectorymethod -> setProblem(trajectoryproblem);
          tt -> setMethod(trajectorymethod);
          pdelete(ptrTmpMethod);
        }
      else
        {
          QMessageBox::warning(this, NULL, "New method cannot be created by the paramters!", QMessageBox::Ok, QMessageBox::Cancel);
          trajectorymethod = ptrTmpMethod;
        }
    }

  QTableItem * pItem;
  QString substrate;
  QString strname;
  unsigned C_INT32 i;
  for (i = 0; i < trajectorymethod->size(); i++)
    {
      pItem = parameterTable->item(i, 0);
      substrate = pItem->text();
      strname = (trajectorymethod->getName(i)).c_str();
      switch (trajectorymethod->getType((const char *)strname.utf8()))
        {
        case CParameter::DOUBLE:
          trajectorymethod->setValue((const char *)strname.utf8(),
                                     substrate.toDouble());
          break;
        case CParameter::INT:
          trajectorymethod->setValue((const char *)strname.utf8(),
                                     (C_INT32)substrate.toInt());
          break;
        case CParameter::UINT:
          trajectorymethod->setValue((const char *)strname.utf8(),
                                     (unsigned C_INT32)substrate.toUInt());
          break;
        case CParameter::BOOL:;
          trajectorymethod->setValue((const char *)strname.utf8(),
                                     bool(substrate.toUShort()));
          break;
        }
    }

  loadTrajectoryTask();
}

void TrajectoryWidget::EnableRunTask()
{
  if (!bExecutable->isChecked())
    bRunTask->setEnabled(false);
  else
    bRunTask->setEnabled(true);
}

void TrajectoryWidget::RunTask()
{
  CommitChange();

  if (bRunTask->text() != "Run")
    {
      hide();
      return;
    }

  setCursor(Qt::WaitCursor);

  CTrajectoryTask* tt = (CTrajectoryTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  tt->getProblem()->getModel()->compile();
  tt->getProblem()->setInitialState(tt->getProblem()->
                                    getModel()->getInitialState());
  tt->getProblem()->
  setStartTime(tt->getProblem()->getStartTime());

  std::ofstream output("trajectory.txt");
  output << "# "; // Hack for gnuplot
  tt->initializeReporting(output);

  tt->process();

  ((ListViews*)pParent)->notify(ListViews::STATE, ListViews::CHANGE, dataModel->getModel()->getKey());

  //emit runFinished(dataModel->getTrajectoryTask()->getProblem()->getModel());

  unsetCursor();
}

void TrajectoryWidget::loadTrajectoryTask()
{
  CTrajectoryTask* tt = (CTrajectoryTask*)(CCopasiContainer*)CKeyFactory::get(objKey);

  CTrajectoryProblem* trajectoryproblem = tt->getProblem();
  CTrajectoryMethod* trajectorymethod = tt->getMethod();

  taskName->setText(tr("Trajectory Task"));
  taskName->setEnabled(false);

  nStepSize->setText(QString::number(trajectoryproblem->getStepSize()));
  nStepNumber->setText(QString::number(trajectoryproblem->getStepNumber()));
  nStartTime->setText(QString::number(trajectoryproblem->getStartTime()));
  nEndTime->setText(QString::number(trajectoryproblem->getEndTime()));

  QTableItem * pItem;
  QString substrate;
  QString strname;

  parameterTable->setNumRows(trajectorymethod->size());
  QHeader *rowHeader = parameterTable->verticalHeader();

  unsigned C_INT32 i;
  for (i = 0; i < trajectorymethod->size(); i++)
    {
      strname = (trajectorymethod->getName(i)).c_str();
      rowHeader->setLabel(i, tr(strname));
    }

  for (i = 0; i < trajectorymethod->size(); i++)
    {
      strname = (trajectorymethod->getName(i)).c_str();
      substrate = QString::number(trajectorymethod->getValue((const char *)strname.utf8()));
      pItem = new QTableItem (parameterTable, QTableItem::Always, substrate);
      parameterTable->setItem(i, 0, pItem);
    }

  ComboBox1->clear ();
  //disable Hybrid By Force
  for (i = 0; (strlen(trajectorymethod->TypeName[i].c_str()) > 0) && (QString::compare(trajectorymethod->TypeName[i].c_str(), "hybrid") != 0); i++)
    ComboBox1->insertItem(trUtf8(trajectorymethod->TypeName[i].c_str()));

  ComboBox1->setCurrentItem (trajectorymethod->getTypeEnum());

  if (!bExecutable->isChecked())
    bRunTask->setEnabled(false);
  else
    bRunTask->setEnabled(true);
}

void TrajectoryWidget::UpdateMethod()
{
  //if (!mTrajectoryTask)
  //  return;
  CTrajectoryTask* tt = (CTrajectoryTask*)(CCopasiContainer*)CKeyFactory::get(objKey);
  CTrajectoryProblem* trajectoryproblem = tt->getProblem();
  CTrajectoryMethod* trajectorymethod = tt->getMethod();

  CTrajectoryMethod* ptrTmpMethod = trajectorymethod;
  trajectorymethod = CTrajectoryMethod::createTrajectoryMethod((CTrajectoryMethod::Type)ComboBox1->currentItem(), trajectoryproblem);
  if (trajectorymethod != NULL)
    {
      trajectorymethod -> setProblem(trajectoryproblem);
      tt -> setMethod(trajectorymethod);
      pdelete(ptrTmpMethod);
    }
  else
    {
      QMessageBox::warning(this, NULL, "New method cannot be created by the paramters!", QMessageBox::Ok, QMessageBox::Cancel);
      trajectorymethod = ptrTmpMethod;
    }

  loadTrajectoryTask();
}

void TrajectoryWidget::ExportToFile()
{
  QString textFile = QFileDialog::getSaveFileName(
                       QString::null, "TEXT Files (*.txt)",
                       this, "save file dialog",
                       "Choose a file");

  if (/*mTrajectoryTask &&*/ textFile)
    {
      textFile += ".txt";
      CWriteConfig outbuf((const char *)textFile.utf8());
      ((CTrajectoryTask*)(CCopasiContainer*)CKeyFactory::get(objKey))->save(outbuf);
    }
}

bool TrajectoryWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
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
  //let the user confirm?
  return true;
}

bool TrajectoryWidget::enter(const std::string & key)
{
  if (!CKeyFactory::get(key)) return false;

  objKey = key;

  loadTrajectoryTask();

  return true;
}

void TrajectoryWidget::ReportDefinitionClicked()
{
  CReportDefinitionSelect* pSelectDlg = new CReportDefinitionSelect(pParent);
  if (pSelectDlg->exec () == QDialog::Rejected)
    {
      return;
    }
}
