/*******************************************************************
 **  $ CopasiUI/ScanWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Scan Widget
 ********************************************************************/
#include <qfiledialog.h>
#include <qvbox.h>
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
#include <qscrollview.h>
#include "ScanWidget.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "model/CModel.h"
#include "listviews.h"

/*
 *  Constructs a ScanWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ScanWidget::ScanWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  if (!name)
    setName("ScanWidget");
  resize(626, 588);
  setMinimumSize(QSize(0, 0));
  setCaption(trUtf8("ScanWidget"));
  ScanWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanWidgetLayout");

  taskNameLabel = new QLabel(this, "taskNameLabel");
  taskNameLabel->setText(trUtf8("Task Name"));

  ScanWidgetLayout->addWidget(taskNameLabel, 0, 0);
  QSpacerItem* spacer = new QSpacerItem(91, 400, QSizePolicy::Minimum, QSizePolicy::Expanding);
  ScanWidgetLayout->addItem(spacer, 5, 0);

  parameterValueLabel = new QLabel(this, "parameterValueLabel");
  parameterValueLabel->setText(trUtf8("Scan Item"));

  ScanWidgetLayout->addWidget(parameterValueLabel, 4, 0);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  /*bRunButton = new QPushButton(this, "bRunButton");
  bRunButton->setText(trUtf8("Run"));
  bRunButton->setEnabled(false);
  Layout2->addWidget(bRunButton);*/

  commitChange = new QPushButton(this, "commitChange");
  commitChange->setText(trUtf8("Commit"));
  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Cancel"));
  Layout2->addWidget(cancelChange);

  /*ExportFileButton = new QPushButton(this, "ExportFileButton");
   ExportFileButton->setText(trUtf8("Export To File"));
   Layout2->addWidget(ExportFileButton);*/

  ScanWidgetLayout->addMultiCellLayout(Layout2, 7, 7, 0, 2);

  line6 = new QFrame(this, "line6");
  line6->setFrameShape(QFrame::HLine);
  line6->setFrameShadow(QFrame::Sunken);
  line6->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(line6, 6, 6, 0, 2);

  taskName = new QLineEdit(this, "taskName");
  taskName->setFrameShape(QLineEdit::LineEditPanel);
  taskName->setFrameShadow(QLineEdit::Sunken);

  ScanWidgetLayout->addWidget(taskName, 0, 1);

  bExecutable = new QCheckBox(this, "bExecutable");
  bExecutable->setText(trUtf8("Scan Executable"));

  ScanWidgetLayout->addWidget(bExecutable, 0, 2);

  line8 = new QFrame(this, "line8");
  line8->setFrameShape(QFrame::HLine);
  line8->setFrameShadow(QFrame::Sunken);
  line8->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(line8, 1, 1, 0, 2);

  scrollview = new QScrollView(this, 0, 0);
  vBox = new QVBox(this, 0);
  /*for (int temp = 1; temp <= 7; temp++)
     {
       parameterTable = new QTable(this, "parameterTable");
       parameterTable->setNumRows(5);
       parameterTable->setNumCols(5);
     parameterTable->setFocusPolicy(QWidget::WheelFocus);
       QHeader *colHeader = parameterTable->horizontalHeader();
       colHeader->setLabel(0, tr("Value"));
       vBox->insertChild(parameterTable);
       vBox->setSpacing(25);
   }
  */

  scrollview->addChild(vBox);
  ScanWidgetLayout->addMultiCellWidget(scrollview, 4, 5, 1, 2);

  taskStability = new QCheckBox(this, "taskStability");
  taskStability->setText(trUtf8("Trajectory"));

  ScanWidgetLayout->addWidget(taskStability, 2, 2);

  taskDescriptionLabel = new QLabel(this, "taskDescriptionLabel");
  taskDescriptionLabel->setText(trUtf8("Problem"));

  ScanWidgetLayout->addWidget(taskDescriptionLabel, 2, 0);

  taskJacobian = new QCheckBox(this, "taskJacobian");
  taskJacobian->setText(trUtf8("Steady State"));

  ScanWidgetLayout->addWidget(taskJacobian, 2, 1);

  /*// tab order
  setTabOrder(taskName, bExecutable);
  setTabOrder(bExecutable, taskJacobian);
  setTabOrder(taskJacobian, taskStability);
  setTabOrder(taskStability, parameterTable);
  setTabOrder(commitChange, cancelChange);*/
}

ScanWidget::~ScanWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void ScanWidget::loadScan(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      taskName->setText(tr("Scan"));
      CScanTask *scanTask = new CScanTask();
      CScanProblem *scanProblem = scanTask->getProblem();
      scanProblem->setModel(model);
      //      hide();
      //QMessageBox::information(this, "Metabolites Widget", QString::number(scanProblem->getListSize()));
      for (C_INT32 i = 0; i < scanProblem->getListSize(); i++)
        {
          //CMethodParameterList *itemList=scanProblem->getScanItem(i);
          //itemList->getName();
          parameterTable = new QTable(scrollview, "parameterTable");
          parameterTable->setNumRows(5);
          parameterTable->setNumCols(5);
          parameterTable->setFocusPolicy(QWidget::WheelFocus);
          QHeader *colHeader = parameterTable->horizontalHeader();
          colHeader->setLabel(0, tr("Value"));
          vBox->insertChild(parameterTable);
          vBox->setSpacing(25);
        }
      //      show();
      scrollview->addChild(vBox);
      ScanWidgetLayout->addMultiCellWidget(scrollview, 4, 5, 1, 2);
    }
}
