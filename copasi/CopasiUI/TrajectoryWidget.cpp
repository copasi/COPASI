/****************************************************************************
 ** Form implementation generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Thu Feb 13 12:32:58 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "TrajectoryWidget.h"
#include "trajectory/trajectory.h"

#include <qvariant.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a TrajectoryWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
TrajectoryWidget::TrajectoryWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  mTrajectoryTask = NULL;
  if (!name)
    setName("TrajectoryWidget");
  resize(719, 539);
  setCaption(trUtf8("TrajectoryWidget"));

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setGeometry(QRect(11, 11, 282, 19));
  taskNameLabel->setText(trUtf8("Task Name"));

  line7 = new QFrame(this, "line7");
  line7->setGeometry(QRect(11, 222, 568, 16));
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  line7->setFrameShape(QFrame::HLine);

  nStepNumber_2 = new QLineEdit(this, "nStepNumber_2");
  nStepNumber_2->setGeometry(QRect(403, 147, 121, 21));
  nStepNumber_2->setText(trUtf8(""));

  parameterTable = new QTable(this, "parameterTable");
  parameterTable->setGeometry(QRect(100, 266, 484, 160));
  parameterTable->setNumRows(3);
  parameterTable->setNumCols(3);

  line8 = new QFrame(this, "line8");
  line8->setGeometry(QRect(11, 62, 568, 16));
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  TextLabel1_2 = new QLabel(this, "TextLabel1_2");
  TextLabel1_2->setGeometry(QRect(300, 101, 80, 20));
  TextLabel1_2->setText(trUtf8("Step Number"));

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setGeometry(QRect(14, 266, 80, 160));
  parameterValueLabel->setText(trUtf8("Parameter value"));

  TextLabel1_3 = new QLabel(this, "TextLabel1_3");
  TextLabel1_3->setGeometry(QRect(33, 147, 56, 20));
  TextLabel1_3->setText(trUtf8("Start Time"));

  TextLabel1_2_2 = new QLabel(this, "TextLabel1_2_2");
  TextLabel1_2_2->setGeometry(QRect(303, 147, 56, 20));
  TextLabel1_2_2->setText(trUtf8("End Time"));

  nStepSize = new QLineEdit(this, "nStepSize");
  nStepSize->setGeometry(QRect(100, 101, 121, 21));
  nStepSize->setText(trUtf8(""));

  nStepNumber = new QLineEdit(this, "nStepNumber");
  nStepNumber->setGeometry(QRect(400, 101, 121, 21));
  nStepNumber->setText(trUtf8(""));

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setGeometry(QRect(30, 101, 56, 20));
  TextLabel1->setText(trUtf8("Step Size"));

  nStepSize_2 = new QLineEdit(this, "nStepSize_2");
  nStepSize_2->setGeometry(QRect(101, 147, 121, 21));
  nStepSize_2->setText(trUtf8(""));

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setGeometry(QRect(430, 10, 120, 16));
  bExecutable->setText(trUtf8("Task Executable "));

  taskName = new QLineEdit(this, "taskName");
  taskName->setGeometry(QRect(100, 10, 282, 19));

  line6 = new QFrame(this, "line6");
  line6->setGeometry(QRect(11, 468, 578, 16));
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);

  QWidget* privateLayoutWidget = new QWidget(this, "Layout7");
  privateLayoutWidget->setGeometry(QRect(10, 500, 580, 25));
  Layout7 = new QHBoxLayout(privateLayoutWidget, 0, 6, "Layout7");

  bRunTask = new QPushButton(privateLayoutWidget, "bRunTask");
  bRunTask->setText(trUtf8("Run Task"));
  Layout7->addWidget(bRunTask);

  commitChange = new QPushButton(privateLayoutWidget, "commitChange");
  commitChange->setText(trUtf8("Commit Change"));
  Layout7->addWidget(commitChange);

  cancelChange = new QPushButton(privateLayoutWidget, "cancelChange");
  cancelChange->setText(trUtf8("Cancel Change"));
  Layout7->addWidget(cancelChange);

  // signals and slots connections
  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));
  connect(bRunTask, SIGNAL(clicked()), this, SLOT(RunTask()));
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
  qWarning("TrajectoryWidget::CancelChange(): Not implemented yet!");
}

void TrajectoryWidget::CommitChange()
{
  qWarning("TrajectoryWidget::CommitChange(): Not implemented yet!");
}

void TrajectoryWidget::RunTask()
{
  if (mTrajectoryTask == NULL)
    return;
  mTrajectoryTask->process();
}
