/****************************************************************************
 ** Form implementation generated from reading ui file '.\TrajectoryWidget.ui'
 **
 ** Created: Tue Feb 11 14:01:14 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "TrajectoryWidget.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qsplitter.h>
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
  if (!name)
    setName("TrajectoryWidget");
  resize(719, 589);
  setCaption(trUtf8("TrajectoryWidget"));

  QWidget* privateLayoutWidget = new QWidget(this, "layout15");
  privateLayoutWidget->setGeometry(QRect(10, 449, 580, 88));
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

  line8 = new QFrame(this, "line8");
  line8->setGeometry(QRect(11, 71, 568, 16));
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setGeometry(QRect(11, 11, 282, 19));
  taskNameLabel->setText(trUtf8("Task Name"));

  line7 = new QFrame(this, "line7");
  line7->setGeometry(QRect(11, 231, 568, 16));
  line7->setFrameShape(QFrame::HLine);
  line7->setFrameShadow(QFrame::Sunken);
  line7->setFrameShape(QFrame::HLine);

  splitter11 = new QSplitter(this, "splitter11");
  splitter11->setGeometry(QRect(14, 275, 570, 160));
  splitter11->setOrientation(QSplitter::Horizontal);

  parameterValueLabel = new QLabel(splitter11, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Parameter value"));

  parameterTable = new QTable(splitter11, "parameterTable");
  parameterTable->setNumRows(3);
  parameterTable->setNumCols(3);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setGeometry(QRect(30, 110, 56, 20));
  TextLabel1->setText(trUtf8("Step Size"));

  TextLabel1_3 = new QLabel(this, "TextLabel1_3");
  TextLabel1_3->setGeometry(QRect(33, 156, 56, 20));
  TextLabel1_3->setText(trUtf8("Start Time"));

  nStepSize = new QLineEdit(this, "nStepSize");
  nStepSize->setGeometry(QRect(100, 110, 121, 21));
  nStepSize->setText(trUtf8(""));

  taskName = new QLineEdit(this, "taskName");
  taskName->setGeometry(QRect(100, 10, 282, 19));

  nStepSize_2 = new QLineEdit(this, "nStepSize_2");
  nStepSize_2->setGeometry(QRect(101, 156, 121, 21));
  nStepSize_2->setText(trUtf8(""));

  TextLabel1_2 = new QLabel(this, "TextLabel1_2");
  TextLabel1_2->setGeometry(QRect(300, 110, 80, 20));
  TextLabel1_2->setText(trUtf8("Step Number"));

  TextLabel1_2_2 = new QLabel(this, "TextLabel1_2_2");
  TextLabel1_2_2->setGeometry(QRect(303, 156, 56, 20));
  TextLabel1_2_2->setText(trUtf8("End Time"));

  nStepNumber = new QLineEdit(this, "nStepNumber");
  nStepNumber->setGeometry(QRect(400, 110, 121, 21));
  nStepNumber->setText(trUtf8(""));

  nStepNumber_2 = new QLineEdit(this, "nStepNumber_2");
  nStepNumber_2->setGeometry(QRect(403, 156, 121, 21));
  nStepNumber_2->setText(trUtf8(""));

  // signals and slots connections
  connect(taskName, SIGNAL(textChanged(const QString&)), this, SLOT(taskNameChanged()));
  connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChange()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChange()));

  // tab order
  setTabOrder(taskName, parameterTable);
  setTabOrder(parameterTable, commitChange);
  setTabOrder(commitChange, cancelChange);
}

/*
 *  Destroys the object and frees any allocated resources
 */
TrajectoryWidget::~TrajectoryWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void TrajectoryWidget::taskNameChanged()
{
  qWarning("TrajectoryWidget::taskNameChanged(): Not implemented yet!");
}

void TrajectoryWidget::methodJacob()
{
  qWarning("TrajectoryWidget::methodJacob(): Not implemented yet!");
}

void TrajectoryWidget::methodStability()
{
  qWarning("TrajectoryWidget::methodStability(): Not implemented yet!");
}

void TrajectoryWidget::parameterValueChanged()
{
  qWarning("TrajectoryWidget::parameterValueChanged(): Not implemented yet!");
}

void TrajectoryWidget::CommitChange()
{
  qWarning("TrajectoryWidget::CommitChange(): Not implemented yet!");
}

void TrajectoryWidget::CancelChange()
{
  qWarning("TrajectoryWidget::CancelChange(): Not implemented yet!");
}
