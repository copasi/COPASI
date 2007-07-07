// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ScanWidget.cpp,v $
//   $Revision: 1.202 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/07/07 21:13:51 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//***  In this file I have put "//+++" in all places where something has to be added
//***  if a new scan item is introduced.

#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qcombobox.h>
#include <qlineedit.h>

#include "copasi.h"

#include "ScanWidget.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "scan/CScanMethod.h"
#include "CopasiDataModel/CCopasiDataModel.h"

#include "CQTaskHeaderWidget.h"
#include "CQTaskBtnWidget.h"

#include "report/CKeyFactory.h"
#include "qtUtilities.h"
#include "CScanContainerWidget.h"
#include "utilities/CopasiTime.h"

//+++
//#include "CScanWidgetBreak.h"
#include "CScanWidgetRandom.h"
#include "CScanWidgetRepeat.h"
#include "CScanWidgetScan.h"
#include "CScanWidgetTask.h"

#include "./icons/scanwidgetbuttonicon.xpm"

ScanWidget::ScanWidget(QWidget* parent, const char* name, WFlags f)
    : TaskWidget(parent, name, f)
{
  if (!name)
    setName("ScanWidget");

  setCaption(trUtf8("ScanWidget"));
  ScanWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ScanWidgetLayout");

  mpHeaderWidget->setTaskName("Parameter Scan");

  ScanWidgetLayout->addWidget(mpHeaderWidget, 0, 0);
  ScanWidgetLayout->addWidget(mpBtnWidget, 3, 0);

  //*****************

  QHBoxLayout* tmpLayout = new QHBoxLayout();

  QSpacerItem* tmpSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  tmpLayout->addItem(tmpSpacer);

  QLabel* tmpLabel = new QLabel(this);
  tmpLabel->setText("New scan item: ");
  tmpLayout->addWidget(tmpLabel);

  comboType = new QComboBox(this);
  //+++
  comboType->insertItem("Parameter Scan");
  comboType->insertItem("Repeat");
  comboType->insertItem("Random distribution");
  //comboType->insertItem("Output separator");
  tmpLayout->addWidget(comboType);

  buttonNewItem = new QPushButton(this, "buttonNewItem");
  buttonNewItem->setText("... Create!");
  //ScanWidgetLayout->addWidget(buttonNewItem, 1, 2);
  tmpLayout->addWidget(buttonNewItem);

  ScanWidgetLayout->addLayout(tmpLayout, 1, 0);

  //*****************************

  Layout24 = new QHBoxLayout(0, 0, 6, "Layout24");

  scrollview = new CScanContainerWidget(this);
  Layout24->addWidget(scrollview);

  ScanWidgetLayout->addLayout(Layout24, 2, 0);

  // tab order
  /*setTabOrder(taskName, sExecutable);
  setTabOrder(sExecutable, steadyState);*/

  connect(buttonNewItem, SIGNAL(clicked()), this, SLOT(slotAddItem()));
}

ScanWidget::~ScanWidget()
{}

bool ScanWidget::runTask()
{
  if (!commonBeforeRunTask()) return false;

  bool success = true;
  if (!commonRunTask()) success = false;

  if (!commonAfterRunTask()) success = false;

  //   StateWidget *pResult = dynamic_cast< StateWidget * >(pListView->findWidgetFromId(211));
  //   if (pResult) pResult->loadFromBackend();
  //
  //   if (success && isShown()) pListView->switchToOtherWidget(211, ""); //change to the results window

  //TODO: is this necessary?
  //scanTask->restore();

  return success;
}

// void ScanWidget::runScanTask()
// {
//   CScanTask* scanTask =
//     dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
//   if (!scanTask) return;
//
//   //******** this is from commonBeforeRunTask() ************
//
//   // save the state of the widget
//   if (!saveScan()) //+++
//     {
//       CQMessageBox::critical(this, "Simulation Error",
//                              CCopasiMessage::getAllMessageText().c_str(),
//                              QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
//       return ;//false;
//}
//
//   if (!scanTask) return;// false; //+++
//
//   //set mouse cursor
//   setCursor(Qt::WaitCursor);
//
//   //handle autosave feature
//   static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
//   static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);
//
//   //create progress bar
//   CProgressBar * tmpBar = new CProgressBar();
//   scanTask->setCallBack(tmpBar);
//
//   CCopasiMessage::clearDeque();
//   //return true;
//
//   //********** this is from commonRunTask() **************
//
//   bool success = true;
//
//   // Initialize the task
//   try
//     {
//       if (!scanTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL))
//         throw CCopasiException(CCopasiMessage::peekLastMessage());
//}
//
//   catch (CCopasiException Exception)
//     {
//       if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
//         {
//           tmpBar->finish();
//           CQMessageBox::critical(this, "Initialization Error",
//                                  CCopasiMessage::getAllMessageText().c_str(),
//                                  QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
//
//           success = false;
//           goto finish;
//}
//}
//
//   if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::ERROR)
//     {
//       tmpBar->finish();
//       CQMessageBox::critical(this, "Initialization Error",
//                              CCopasiMessage::getAllMessageText().c_str(),
//                              QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
//
//       success = false;
//       goto finish;
//}
//
//   if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
//     {
//       C_INT Result =
//         CQMessageBox::question(this, "Initialization Warning",
//                                CCopasiMessage::getAllMessageText().c_str(),
//                                QMessageBox::Ignore | QMessageBox::Default,
//                                QMessageBox::Abort | QMessageBox::Escape);
//
//       if (Result == 1)
//         {
//           success = false;
//           goto finish;
//}
//}
//
//   CCopasiMessage::clearDeque();
//
//   // Execute the task
//   try
//     {
//       if (!scanTask->process(true))
//         throw CCopasiException(CCopasiMessage::peekLastMessage());
//}
//
//   catch (CCopasiException Exception)
//     {
//       if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
//         {
//           tmpBar->finish();
//           CQMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(),
//                                  QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
//}
//
//       success = false;
//       goto finish;
//}
//
//   if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
//     {
//       CQMessageBox::information(this, "Calculation Warning",
//                                 CCopasiMessage::getAllMessageText().c_str(),
//                                 QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
//}
//
// finish:
//
//   CCopasiMessage::clearDeque();
//
//   try {scanTask->restore();}
//
//   catch (CCopasiException Exception)
//     {
//       if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
//         {
//           tmpBar->finish();
//           CQMessageBox::critical(this, "Calculation Error", CCopasiMessage::getAllMessageText().c_str(),
//                                  QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
//           CCopasiMessage::clearDeque();
//}
//}
//
//   catch (...) {}
//
//   if (CCopasiMessage::getHighestSeverity() > CCopasiMessage::COMMANDLINE)
//     {
//       C_INT Result =
//         CQMessageBox::information(this, "Calculation Warning",
//                                   CCopasiMessage::getAllMessageText().c_str(),
//                                   QMessageBox::Ok | QMessageBox::Default, QMessageBox::NoButton);
//}
//
//   CCopasiMessage::clearDeque();
//
//   //return success;
//
//   // this is from commonAfterRunTask()
//
//   if (!scanTask) return;// false;
//
//   if (tmpBar)
//     {
//       tmpBar->finish();
//       pdelete(tmpBar);
//}
//   scanTask->setCallBack(NULL);
//
//   CCopasiMessage::clearDeque();
//
//   CCopasiDataModel::Global->finish();
//   protectedNotify(ListViews::STATE, ListViews::CHANGE, CCopasiDataModel::Global->getModel()->getKey());
//   unsetCursor();
//   static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(false);
//
//   //return
//   loadScan();
//
//
//}

#ifdef XXXX

void ScanWidget::runScanTask()
{
  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(scanTaskKey));
  if (!scanTask) return;

  //((CScanProblem*)(scanTask->getProblem()))->createDebugScan(dataModel->getModel());

  // save the state of the widget
  saveScan();

  static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);

  scanTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);

  setCursor(Qt::WaitCursor);
  CProgressBar * tmpBar = new CProgressBar();
  scanTask->setCallBack(tmpBar);

  CCopasiTimeVariable time = CCopasiTimeVariable::getCurrentWallTime();

  try
    {
      scanTask->process(true);
    }
  catch (CCopasiException Exception)
    {
      //std::cout << std::endl << "exception in scan task" << std::endl;
      //TODO: message box
    }

  //std::cout << "*************** The scan took "
  //<< (CCopasiTimeVariable::getCurrentWallTime() - time).isoFormat()
  //<< " ***************" << std::endl;

  //should be renamed?
  scanTask->restore();

  tmpBar->finish(); pdelete(tmpBar);
  CCopasiDataModel::Global->finish();

  CCopasiMessage::clearDeque();
  CCopasiDataModel::Global->finish();
  protectedNotify(ListViews::STATE, ListViews::CHANGE,
                  CCopasiDataModel::Global->getModel()->getKey());

  unsetCursor();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(false);

  return;
}

#endif

bool ScanWidget::loadTask()
{
  loadCommon();

  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(mObjectKey));
  if (!scanTask) return false;

  CScanProblem *scanProblem = dynamic_cast<CScanProblem *>(scanTask->getProblem());
  if (!scanProblem) return false;

  scrollview->clearWidgetList();

  //std::vector<QWidget*> & widgetList = scrollview->getWidgetList();

  //+++
  CScanWidgetScan* tmp1;
  CScanWidgetRepeat* tmp2;
  CScanWidgetRandom* tmp3;
  //CScanWidgetBreak* tmp4;

  // the scan items
  unsigned C_INT32 i, imax = scanProblem->getNumberOfScanItems();
  for (i = 0; i < imax; ++i)
    {
      void* pTmp;
      if (!(pTmp = scanProblem->getScanItem(i)->getValue("Type").pVOID)) return false;
      CScanProblem::Type type = *(CScanProblem::Type*)pTmp;

      switch (type)
        {
          //+++
        case CScanProblem::SCAN_LINEAR:
          tmp1 = new CScanWidgetScan(scrollview);
          tmp1->initFromScanItem(scanProblem->getScanItem(i), CCopasiDataModel::Global->getModel());
          scrollview->addWidget(tmp1);
          break;

        case CScanProblem::SCAN_REPEAT:
          tmp2 = new CScanWidgetRepeat(scrollview);
          tmp2->initFromScanItem(scanProblem->getScanItem(i));
          scrollview->addWidget(tmp2);
          break;

        case CScanProblem::SCAN_RANDOM:
          tmp3 = new CScanWidgetRandom(scrollview);
          tmp3->initFromScanItem(scanProblem->getScanItem(i), CCopasiDataModel::Global->getModel());
          scrollview->addWidget(tmp3);
          break;

          /*case CScanProblem::SCAN_BREAK:
            tmp4 = new CScanWidgetBreak(scrollview);
            tmp4->initFromScanItem(scanProblem->getScanItem(i));
            scrollview->addWidget(tmp4);
            break;*/

        default:
;
        }
    }

  // the widget for the subtask
  CScanWidgetTask* tmpT = new CScanWidgetTask(scrollview);
  tmpT->initFromScanProblem(scanProblem, CCopasiDataModel::Global->getModel());
  scrollview->addWidget(tmpT, false); //false: no control buttons (up/down/del)

  //scrollview->updateFromWidgetList();
  return true;
}

bool ScanWidget::slotAddItem()
{
  int totalRows = -1;
  //+++
  CScanWidgetScan* tmp1;
  CScanWidgetRepeat* tmp2;
  CScanWidgetRandom* tmp3;
  //CScanWidgetBreak* tmp4;

  int intType = comboType->currentItem();
  CScanProblem::Type type;
  switch (intType)
    {
      //+++
    case 0:
      type = CScanProblem::SCAN_LINEAR;
      break;
    case 1:
      type = CScanProblem::SCAN_REPEAT;
      break;
    case 2:
      type = CScanProblem::SCAN_RANDOM;
      break;
      /*case 3:
        type = CScanProblem::SCAN_BREAK;
        break;*/
    default:
      type = CScanProblem::SCAN_LINEAR;
    }

  //create item to get the default values
  CScanProblem* tmpProblem = new CScanProblem();
  CCopasiParameterGroup* tmpItem = tmpProblem->createScanItem(type, 10);

  switch (type)
    {
      //+++
    case CScanProblem::SCAN_LINEAR:
      tmp1 = new CScanWidgetScan(scrollview);
      tmp1->initFromScanItem(tmpItem, CCopasiDataModel::Global->getModel());
      scrollview->insertWidget(tmp1);
      totalRows = scrollview->numRows();
      scrollview->ensureCellVisible(totalRows - 1, 0);
      tmp1->lineEditMin->setFocus();
      break;

    case CScanProblem::SCAN_REPEAT:
      tmp2 = new CScanWidgetRepeat(scrollview);
      tmp2->initFromScanItem(tmpItem);
      scrollview->insertWidget(tmp2);
      totalRows = scrollview->numRows();
      scrollview->ensureCellVisible(totalRows - 1, 0);
      tmp2->lineEditNumber->setFocus();
      break;

    case CScanProblem::SCAN_RANDOM:
      tmp3 = new CScanWidgetRandom(scrollview);
      tmp3->initFromScanItem(tmpItem, CCopasiDataModel::Global->getModel());
      scrollview->insertWidget(tmp3);
      totalRows = scrollview->numRows();
      scrollview->ensureCellVisible(totalRows - 1, 0);
      tmp3->lineEditMin->setFocus();
      break;

      /*case CScanProblem::SCAN_BREAK:
        tmp4 = new CScanWidgetBreak(scrollview);
        tmp4->initFromScanItem(tmpItem);
        scrollview->insertWidget(tmp4);
        break;*/

    default:
;
    }

  if (tmpProblem) delete tmpProblem;

  return true;
}

bool ScanWidget::saveTask()
{
  saveCommon();

  CScanTask* scanTask =
    dynamic_cast< CScanTask * >(GlobalKeys.get(mObjectKey));
  if (!scanTask) return false;

  CScanProblem *scanProblem = dynamic_cast<CScanProblem *>(scanTask->getProblem());
  if (!scanProblem) return false;

  scanProblem->clearScanItems();

  const std::vector<QWidget*> & widgetList = scrollview->getWidgetList();

  unsigned C_INT32 i, imax = widgetList.size();
  for (i = 0; i < imax; ++i)
    {
      //+++

      // item: scan parameter
      const CScanWidgetScan* tmp1 = dynamic_cast<CScanWidgetScan*>(widgetList[i]);
      if (tmp1) {tmp1->saveToScanItem(scanProblem); continue;}

      // item: repeat
      const CScanWidgetRepeat* tmp2 = dynamic_cast<CScanWidgetRepeat*>(widgetList[i]);
      if (tmp2) {tmp2->saveToScanItem(scanProblem); continue;}

      // item: random
      const CScanWidgetRandom* tmp3 = dynamic_cast<CScanWidgetRandom*>(widgetList[i]);
      if (tmp3) {tmp3->saveToScanItem(scanProblem); continue;}

      // item: break
      /*const CScanWidgetBreak* tmp4 = dynamic_cast<CScanWidgetBreak*>(widgetList[i]);
      if (tmp4) {tmp4->saveToScanItem(scanProblem); continue;}*/

      // the subtask
      const CScanWidgetTask* tmpT = dynamic_cast<CScanWidgetTask*>(widgetList[i]);
      if (tmpT) {tmpT->saveToScanProblem(scanProblem); continue;}

      return false;
    }

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();

  return true;
}
