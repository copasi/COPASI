/****************************************************************************
 ** Form implementation generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Thu Feb 20 14:48:29 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
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

/*
 *  Constructs a TrajectoryWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TrajectoryWidget::TrajectoryWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("TrajectoryWidget");
  resize(719, 539);
  setCaption(trUtf8("TrajectoryWidget"));

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setGeometry(QRect(11, 11, 282, 19));
  taskNameLabel->setText(trUtf8("Task Name"));

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setGeometry(QRect(430, 10, 120, 16));
  bExecutable->setText(trUtf8("Task Executable "));

  commitChange = new QPushButton(this, "commitChange");
  commitChange->setGeometry(QRect(206, 501, 188, 23));
  commitChange->setText(trUtf8("Commit Change"));

  bRunTask = new QPushButton(this, "bRunTask");
  bRunTask->setGeometry(QRect(11, 501, 189, 23));
  bRunTask->setText(trUtf8("Run Task"));

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setGeometry(QRect(400, 501, 189, 23));
  cancelChange->setText(trUtf8("Cancel Change"));

  line8 = new QFrame(this, "line8");
  line8->setGeometry(QRect(11, 42, 568, 16));
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  line6 = new QFrame(this, "line6");
  line6->setGeometry(QRect(11, 468, 578, 16));
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setGeometry(QRect(14, 296, 80, 160));
  parameterValueLabel->setText(trUtf8("Parameter value"));

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setGeometry(QRect(100, 296, 484, 160));
  parameterTable->setNumRows(3);
  parameterTable->setNumCols(3);

  line7 = new QFrame(this, "line7");
  line7->setGeometry(QRect(10, 270, 568, 16));
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  line7->setFrameShape(QFrame::HLine);

  line7_2 = new QFrame(this, "line7_2");
  line7_2->setGeometry(QRect(20, 160, 568, 16));
  line7_2->setFrameShape(QFrame::HLine);
  line7_2->setFrameShadow(QFrame::Sunken);
  line7_2->setFrameShape(QFrame::HLine);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setGeometry(QRect(17, 71, 56, 20));
  TextLabel1->setText(trUtf8("Step Size"));

  TextLabel1_3 = new QLabel(this, "TextLabel1_3");
  TextLabel1_3->setGeometry(QRect(20, 117, 56, 20));
  TextLabel1_3->setText(trUtf8("Start Time"));

  taskName = new QLineEdit(this, "taskName");
  taskName->setGeometry(QRect(93, 10, 282, 19));

  TextLabel1_3_2 = new QLabel(this, "TextLabel1_3_2");
  TextLabel1_3_2->setGeometry(QRect(20, 211, 56, 20));
  TextLabel1_3_2->setText(trUtf8("Method"));

  nStartTime = new QLineEdit(this, "nStartTime");
  nStartTime->setGeometry(QRect(98, 117, 121, 21));
  nStartTime->setText(trUtf8(""));

  ComboBox1 = new QComboBox(FALSE, this, "ComboBox1");
  ComboBox1->insertItem(trUtf8("deterministic"));
  ComboBox1->insertItem(trUtf8("stochastic"));
  ComboBox1->insertItem(trUtf8("hybrid"));
  ComboBox1->setGeometry(QRect(101, 210, 281, 21));

  nStepSize = new QLineEdit(this, "nStepSize");
  nStepSize->setGeometry(QRect(97, 71, 121, 21));
  nStepSize->setText(trUtf8(""));

  TextLabel1_2_2 = new QLabel(this, "TextLabel1_2_2");
  TextLabel1_2_2->setGeometry(QRect(250, 117, 56, 20));
  TextLabel1_2_2->setText(trUtf8("End Time"));

  nEndTime = new QLineEdit(this, "nEndTime");
  nEndTime->setGeometry(QRect(347, 110, 121, 21));
  nEndTime->setText(trUtf8(""));

  nStepNumber = new QLineEdit(this, "nStepNumber");
  nStepNumber->setGeometry(QRect(347, 71, 121, 21));
  nStepNumber->setText(trUtf8(""));

  TextLabel1_2 = new QLabel(this, "TextLabel1_2");
  TextLabel1_2->setGeometry(QRect(247, 71, 80, 20));
  TextLabel1_2->setText(trUtf8("Step Number"));

  // signals and slots connections
  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));
  connect(bRunTask, SIGNAL(clicked()), this, SLOT(RunTask()));
  connect(bExecutable, SIGNAL(clicked()), this, SLOT(EnableRunTask()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
TrajectoryWidget::~TrajectoryWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void TrajectoryWidget::CancelChange()
{
  if (mTrajectoryTask == NULL)
    return;
  loadTrajectoryTask(mTrajectoryTask);
}

void TrajectoryWidget::CommitChange()
{
  if (mTrajectoryTask == NULL)
    return;
  CTrajectoryProblem * trajectoryproblem = mTrajectoryTask->getProblem();
  CTrajectoryMethod* trajectorymethod = mTrajectoryTask->getMethod();

  trajectoryproblem->setStepSize(nStepSize->text().toDouble());
  trajectoryproblem->setStepNumber(nStepNumber->text().toLong());
  trajectoryproblem->setStartTime(nStartTime->text().toDouble());
  trajectoryproblem->setEndTime(nEndTime->text().toDouble());

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
        case CMethodParameter::DOUBLE:
          trajectorymethod->setValue((const char *)strname.utf8(), substrate.toDouble());
          break;
        case CMethodParameter::INT:
          trajectorymethod->setValue((const char *)strname.utf8(), (C_INT32)substrate.toInt());
          break;
        case CMethodParameter::UINT:
          trajectorymethod->setValue((const char *)strname.utf8(), (unsigned C_INT32)substrate.toUInt());
          break;
        case CMethodParameter::BOOL:;
          trajectorymethod->setValue((const char *)strname.utf8(), bool(substrate.toUShort()));
          break;
        }
    }
  CTrajectoryMethod* ptrTmpMethod = trajectorymethod;
  trajectorymethod = CTrajectoryMethod::createTrajectoryMethod((CTrajectoryMethod::Type)ComboBox1->currentItem(), trajectoryproblem);
  if (trajectorymethod != NULL)
    {
      trajectorymethod -> setProblem(trajectoryproblem);
      mTrajectoryTask -> setMethod(trajectorymethod);
      pdelete(ptrTmpMethod);
    }
  else
    {
      trajectorymethod = ptrTmpMethod;
    }

  loadTrajectoryTask(mTrajectoryTask);
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
  if (mTrajectoryTask == NULL)
    return;
  mTrajectoryTask->process();
}

void TrajectoryWidget::loadTrajectoryTask(CTrajectoryTask *trajectorytask)
{
  if (trajectorytask == NULL)
    return;
  mTrajectoryTask = trajectorytask;
  CTrajectoryProblem* trajectoryproblem = trajectorytask->getProblem();
  CTrajectoryMethod* trajectorymethod = trajectorytask->getMethod();

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

  ComboBox1->setCurrentItem (trajectorymethod->getTypeEnum());

  if (!bExecutable->isChecked())
    bRunTask->setEnabled(false);
  else
    bRunTask->setEnabled(true);
}
