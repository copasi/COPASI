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
#include <qtoolbutton.h>
#include "ScanWidget.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "model/CModel.h"
#include "listviews.h"
#include "ScanItemWidget.h"
#include "ObjectBrowser.h"
#include "ObjectBrowserItem.h"

#include "SteadyStateWidget.h"
#include "TrajectoryWidget.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"

/*
 *  Constructs a ScanWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ScanWidget::ScanWidget(QWidget* parent, const char* name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  if (!name)
    setName("ScanWidget");
  setCaption(trUtf8("ScanWidget"));
  ScanWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanWidgetLayout");

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Problem"));

  ScanWidgetLayout->addWidget(TextLabel1, 0, 0);

  taskName = new QLineEdit(this, "taskName");

  ScanWidgetLayout->addMultiCellWidget(taskName, 0, 0, 1, 3);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(Line1, 1, 1, 0, 4);

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(Line2, 10, 10, 0, 4);

  sExecutable = new QCheckBox(this, "sExecutable");
  sExecutable->setText(trUtf8("Scan Executable"));

  ScanWidgetLayout->addWidget(sExecutable, 0, 4);

  Layout2 = new QHBoxLayout(0, 0, 6, "Layout2");

  commitChange = new QPushButton(this, "commitChange");
  commitChange->setText(trUtf8("Scan"));
  Layout2->addWidget(commitChange);

  cancelChange = new QPushButton(this, "cancelChange");
  cancelChange->setText(trUtf8("Cancel"));
  Layout2->addWidget(cancelChange);

  ScanWidgetLayout->addMultiCellLayout(Layout2, 11, 11, 0, 4);

  Layout3 = new QHBoxLayout(0, 0, 6, "Layout3");

  steadyState = new QCheckBox(this, "steadyState");
  steadyState->setText(trUtf8("Steady State"));
  Layout3->addWidget(steadyState);

  eSteadyState = new QToolButton(this, "eSteadyState");
  eSteadyState->setText(trUtf8("Edit Steady"));
  Layout3->addWidget(eSteadyState);

  ScanWidgetLayout->addMultiCellLayout(Layout3, 2, 2, 0, 1);

  Layout4 = new QHBoxLayout(0, 0, 6, "Layout4");

  trajectory = new QCheckBox(this, "trajectory");
  trajectory->setText(trUtf8("Trajectory"));
  Layout4->addWidget(trajectory);

  eTrajectory = new QToolButton(this, "eTrajectory");
  eTrajectory->setText(trUtf8("Edit Trajectory"));
  Layout4->addWidget(eTrajectory);

  ScanWidgetLayout->addMultiCellLayout(Layout4, 2, 2, 3, 4);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8(""));

  ScanWidgetLayout->addWidget(TextLabel3, 2, 2);

  Line1_2 = new QFrame(this, "Line1_2");
  Line1_2->setFrameShape(QFrame::HLine);
  Line1_2->setFrameShadow(QFrame::Sunken);
  Line1_2->setFrameShape(QFrame::HLine);

  ScanWidgetLayout->addMultiCellWidget(Line1_2, 3, 3, 0, 4);

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Scan Items"));

  ScanWidgetLayout->addWidget(TextLabel2, 4, 0);

  downButton = new QPushButton(this, "downButton");
  downButton->setText(trUtf8("    (v) Down"));

  ScanWidgetLayout->addWidget(downButton, 9, 0);

  upButton = new QPushButton(this, "upButton");
  upButton->setText(trUtf8("(^) Up "));

  ScanWidgetLayout->addWidget(upButton, 8, 0);

  deleteButton = new QPushButton(this, "deleteButton");
  deleteButton->setText(trUtf8("   (-) Delete"));

  ScanWidgetLayout->addWidget(deleteButton, 7, 0);

  addButton = new QPushButton(this, "addButton");
  addButton->setText(trUtf8("(+) Add"));

  ScanWidgetLayout->addWidget(addButton, 6, 0);
  QSpacerItem* spacer = new QSpacerItem(61, 181, QSizePolicy::Minimum, QSizePolicy::Expanding);
  ScanWidgetLayout->addItem(spacer, 5, 0);

  scrollview = new QScrollView(this, 0, 0);
  vBox = new QVBox(this, 0);

  //Just for test
  for (int temp = 1; temp <= 6; temp++)
    addNewScanItem(NULL);

  scrollview->addChild(vBox);

  ScanWidgetLayout->addMultiCellWidget(scrollview, 4, 9, 1, 4);

  // tab order
  setTabOrder(taskName, sExecutable);
  setTabOrder(sExecutable, steadyState);
  setTabOrder(steadyState, trajectory);
  setTabOrder(trajectory, addButton);
  setTabOrder(addButton, deleteButton);
  setTabOrder(deleteButton, upButton);
  setTabOrder(upButton, downButton);
  setTabOrder(downButton, scrollview);
  setTabOrder(scrollview, commitChange);
  setTabOrder(commitChange, cancelChange);

  connect(this, SIGNAL(hide_me()), (ListViews*)parent, SLOT(slotHideWidget()));
  connect(this, SIGNAL(show_me()), (ListViews*)parent, SLOT(slotShowWidget()));

  connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
  connect(upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
  connect(downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));

  connect(commitChange, SIGNAL(clicked()), this, SLOT(CommitChangeButton()));
  connect(cancelChange, SIGNAL(clicked()), this, SLOT(CancelChangeButton()));

  connect(steadyState, SIGNAL(clicked()), this, SLOT(SteadyStateButtonClicked()));
  connect(trajectory, SIGNAL(clicked()), this, SLOT(TrajectoryButtonClicked()));
  connect(sExecutable, SIGNAL(clicked()), this, SLOT(ScanButtonClicked()));

  connect(eSteadyState, SIGNAL(clicked()), this, SLOT(SteadyStateEditing()));
  connect(eTrajectory, SIGNAL(clicked()), this, SLOT(TrajectoryEditing()));

  scanTask = NULL;

  pSteadyStateWidget = new SteadyStateWidget(NULL);
  pSteadyStateWidget->hide();
  pTrajectoryWidget = new TrajectoryWidget(NULL);
  pTrajectoryWidget->hide();

  pSteadyStateWidget->loadSteadyStateTask(new CSteadyStateTask());
  pTrajectoryWidget->loadTrajectoryTask(new CTrajectoryTask());

  eSteadyState->setEnabled(steadyState->isChecked());
  eTrajectory->setEnabled(trajectory->isChecked());
}

void ScanWidget::SteadyStateEditing()
{
  pSteadyStateWidget->show();
}

void ScanWidget::TrajectoryEditing()
{
  pTrajectoryWidget->show();
}

ScanWidget::~ScanWidget()
{
  delete scanTask;
  delete pTrajectoryWidget;
  delete pSteadyStateWidget;
  // no need to delete child widgets, Qt does it all for us
}

void ScanWidget::addButtonClicked()
{
  ObjectBrowser* pSelectedObjects = new ObjectBrowser();
  if (pSelectedObjects->exec () == QDialog::Rejected)
    return;
  ObjectList* pSelectedList = pSelectedObjects->outputList();

  if (pSelectedList == NULL)
    return;

  ObjectListItem* pListItem = pSelectedList->getRoot();
  for (; pListItem; pListItem = pListItem->pNext)
    if ((pListItem->pItem) && (pListItem->pItem->getObject()) && (pListItem->pItem->getObject()->pCopasiObject))
      break;

  if (pSelectedList->getRoot())
    addNewScanItem(pListItem->pItem->getObject()->pCopasiObject);

  delete pSelectedObjects;
  delete pSelectedList;
}

void ScanWidget::deleteButtonClicked()
{}

void ScanWidget::upButtonClicked()
{}

void ScanWidget::downButtonClicked()
{}

void ScanWidget::CancelChangeButton()
{}

void ScanWidget::CommitChangeButton()
{
  scanTask->process();
}

void ScanWidget::ScanButtonClicked()
{
  scanTask->setRequested(sExecutable->isChecked());
  commitChange->setEnabled(sExecutable->isChecked());
}

void ScanWidget::SteadyStateButtonClicked()
{
  CScanProblem *scanProblem = scanTask->getProblem();
  scanProblem->setProcessSteadyState(steadyState->isChecked());
  eSteadyState->setEnabled(steadyState->isChecked());
}

void ScanWidget::TrajectoryButtonClicked()
{
  CScanProblem *scanProblem = scanTask->getProblem();
  scanProblem->setProcessTrajectory(trajectory->isChecked());
  eTrajectory->setEnabled(trajectory->isChecked());
  if (trajectory->isChecked())
    {}}

void ScanWidget::loadScan(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      pSteadyStateWidget->setModel(mModel);
      pTrajectoryWidget->setModel(mModel);

      taskName->setText(tr("Scan"));
      scanTask = new CScanTask();
      CScanProblem *scanProblem = scanTask->getProblem();

      scanProblem->setModel(model);
      scanProblem->setSteadyStateTask(pSteadyStateWidget->mSteadyStateTask);
      scanProblem->setTrajectoryTask(pTrajectoryWidget->mTrajectoryTask);

      if (scanTask->isRequested() == true)
        sExecutable->setChecked(true);
      else
        sExecutable->setChecked(false);

      if (scanProblem->processTrajectory() == true)
        trajectory->setChecked(true);
      else
        trajectory->setChecked(false);

      if (scanProblem->processSteadyState() == true)
        steadyState->setChecked(true);
      else
        steadyState->setChecked(false);

      emit hide_me();
      //QMessageBox::information(this, "Metabolites Widget", QString::number(scanProblem->getListSize()));
      for (C_INT32 i = 0; i < scanProblem->getListSize(); i++)
        {
          /*
                    CMethodParameterList *itemList = scanProblem->getScanItem(i);
                    itemList->getName();
                    parameterTable = new QTable(scrollview, "parameterTable");
                    parameterTable->setNumCols(1);
                    parameterTable->setFocusPolicy(QWidget::WheelFocus);
                    parameterTable->horizontalHeader()->setLabel(0, "Value");
           
                    for (C_INT32 j = 0; j < itemList->size(); j++)
                      {
                        parameterTable->setNumRows(itemList->size());
                        //rowHeader->setLabel(j, itemList(j).c_str());
           
                        parameterTable->verticalHeader()->setLabel(j, itemList->getName(j).c_str());
                        parameterTable->setText(j, 0, QString::number(itemList->getValue(j)));
                      }
                    vBox->insertChild(parameterTable);
                    vBox->setSpacing(15);
          */
        }

      emit show_me();
      scrollview->addChild(vBox);
      ScanWidgetLayout->addMultiCellWidget(scrollview, 4, 9, 1, 4);
      scrollview->setVScrollBarMode(QScrollView::Auto);
    }
}

void ScanWidget::addNewScanItem(CCopasiObject* pObject)
{
  parameterTable = new ScanItemWidget(this, "parameterTable");
  parameterTable->setFixedWidth(parameterTable->minimumSizeHint().width());
  parameterTable->setFixedHeight(parameterTable->minimumSizeHint().height());
  vBox->insertChild(parameterTable);
  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setLineWidth (4);
  vBox->insertChild(Line1);
}
